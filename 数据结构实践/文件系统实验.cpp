#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <sstream>
#include <string>

#define len 11 //root下初始目录数

using namespace std;

class file;

class directory
{
public:
	string name;//目录名
	string path;//目录地址 
	file* dir;//目录下的文件指针，指向该目录下的第一个文件 
	int num;//子目录数 
	directory* child;//长子目录 ，指向该文件下的第一个子目录 
	directory* next;//兄弟目录 ，指向同一目录下的目录 
	directory* fu;//父目录 
	
	directory();//初始化目录 
	directory(directory* f);//初始化目录，并且给目录指定父目录 
	void creatDirectory();//创建目录 
	directory* initPath(string path,directory* r);//建立目录路径 
	void viewDirectory();//查看目录 
	void createFile();//在当前目录下创建文件 
	void printStruct(directory* d,int floor);//输出目录结构 
	void deldir();//修改链表，删除目录 
	void clear();//删除目录 
};

directory *root;//根目录 

class file
{
public:
	string name;// 文件名 
	directory* d;//文件所在目录 
	string content;//文件内容 
	file* next;
	string creatTime;//文件创建时间 
	
	file();
	void viewFile();//查看文件 
	void modifyFile();//修改文件 
	void delFile();//删除文件 
};

directory::directory()
{
	this->child = NULL;
	this->next = NULL;
	this->dir = NULL;
	this->num = 0;
	this->fu = NULL;
	this->path = "";
} 

directory::directory(directory* f)//初始化目录，并且给目录指定父目录 
{
	this->child = NULL;
	this->next = NULL;
	this->dir = NULL;
	this->num = 0;
	this->path = ""; 
	this->fu = f;
}

directory* directory::initPath(string path,directory* r=root)
{
	directory* pr = r;
	directory* target = NULL;
	while(pr != NULL)
	{
		if(pr != this)
		{
			if(pr->child != NULL)
			{
				path += pr->name;
				path += "/"; 
				target = initPath(path,pr->child);//优先查找子目录，再查找兄弟目录 
				if(target != NULL)
					return target;
			}
			pr = pr->next;
		}
		else
		{
			pr->path = path;
			return pr;
		}
	}
	return NULL;
}

void directory::createFile()
{
	cout << "请输入要创建的文件名称\n>>";
	string name;
	cin >> name;
	file* fd = this->dir;
	while(fd != NULL)
	{
		if(fd->name == name)
		{
			cout << "文件已存在" << endl;
			return;
		}
		fd = fd->next;
	}
	
	file* fp = new file(); 
	fp->d = this;
	fp->name = name;
	
	getchar();
	cout << "请输入文件内容\n>>";
	cin >> fp->content;
	getchar();
	
	time_t timep;
    time(&timep); //获取从1970至今过了多少秒，存入time_t类型的timep
    struct tm *creatTime = localtime(&timep);//用localtime将秒数转化为struct tm结构体
    char ch[40];
    snprintf(ch,40,"%d/%d/%d %02d:%02d:%02d\n", 1900 + creatTime->tm_year, 1+ creatTime->tm_mon, creatTime->tm_mday,creatTime->tm_hour, creatTime->tm_min,creatTime->tm_sec);
	fp->creatTime = ch;
	getchar();
	
	if(this->dir != NULL)
	{
		file* p = this->dir;
		while(p->next != NULL)
		{
			p = p->next;
		}
		p->next = fp;
	}
	else
	{
		this->dir = fp;
	}
	cout << "文件创建成功" << endl;; 
}

void directory::creatDirectory()//创建目录 
{
		cout << "当前目录：" << this->path << this->name << endl;
		cout << "输入要创建的目录名称\n>>";
		string Name;
		cin >> Name;
		getchar();
		
		directory* child = this->child;
		while(child != NULL)
		{
			if(child->name == Name)
			{
				cout << "目录已存在！！！" << endl; 
				return;
			}
			child = child->next;
		}
			
		if(this->num == 0)//若为该目录下的第一个目录。则用child指向新目录，否则连接在child后面 
		{
			this->child = new directory(this);
			this->child->initPath("/");
			this->child->name = Name;
		}
		else
		{
			directory* pr = this->child;
			while(pr->next != NULL)
			{
				pr = pr->next;
			}
			pr->next = new directory();
			pr->next->initPath("/");
			pr->next->name = Name;
			pr->next->fu = this;
		}
		
		++this->num;
		cout << "目录创建成功" << endl;
}

void directory::viewDirectory()//按目录名称查看目录下的文件和目录 
{
		cout << "当前目录：" << this->path << this->name << endl;
		
		if(this->child != NULL)
		{
			directory* child = this->child;
			cout << this->name << "下的目录："; 
			while(child != NULL)
			{
				cout << child->name << ' ';
				child = child->next;
			}
			cout << endl;;
		}
		else
		{
			cout << this->name << "下没有目录" << endl;;
		}
		
		if(this->dir != NULL)
		{
			file* child = this->dir;
			cout << this->name << "下的文件：";
			while(child != NULL)
			{
				cout << child->name << ' ';
				child = child->next;
			}
			cout << endl;
		}
		else
		{
			cout << this->name << "下没有文件" << endl;
		}
}

void directory::printStruct(directory* d,int floor)//打印目录结构 
{
	for(int i=0;i<floor;++i)
			cout << '\t';
 	cout << '-' << d->name << endl;
 	
	directory* child = d->child;
	while(child != NULL)
	{
		printStruct(child,floor+1);
		child = child->next;
	}
	
	file* fp = d->dir;
	while(fp != NULL)
	{
		for(int i=0;i<floor+1;++i)
			cout << '\t';
		cout << fp->name << endl;
		fp = fp->next;
	}
}

void directory::deldir()
{
	directory* p = this->fu->child;
	if(p != this)
		{
			while(p->next != this)
			{
				
				p = p->next;
			}
					
			p->next = this->next;
		}
		else
			this->fu->child = this->next;
		
		this->clear();
		cout<< "目录已删除" << endl;
}

/*
删除目录 
方法：  1、先删除目录下的文件
		2、递归删除子目录 
*/ 
void directory::clear() 
{
	directory* pr = this;
	if(pr != NULL)
	{
		if(pr->dir != NULL)// 删除目录下的文件
		{
			file* f = pr->dir;
			file* fp = f;
			while(fp != NULL)
			{
				f = fp->next;
				delete fp;
				fp = f;	
			}
		}
		
		if(pr->child != NULL)//递归删除子目录 
		{
			directory* q;	
			while(pr->child != NULL)
			{
				q = pr->child;
				pr->child = q->next; 
				q->clear();
			} 
		}
		delete pr;
	}
}

file::file()
{
	this->next = NULL;
}

void file::viewFile()
{
	cout << "文件路径：" << this->d->path << this->d->name << endl; 
	cout << "文件名：" << this->name << endl;
	cout << "文件内容：" << this->content << endl;
	cout << "文件创建时间：" << this->creatTime;
	//printf("%d/%d/%d %02d:%02d:%02d\n", 1900 + this->creatTime->tm_year, 1+ this->creatTime->tm_mon, this->creatTime->tm_mday,this->creatTime->tm_hour, this->creatTime->tm_min, this->creatTime->tm_sec);

}

void file::modifyFile()
{
		cout << "是否更改文件名(yes/no)\n>>";
		string com;
		cin >> com;
		if(com == "yes")
		{
			cout << "请输入更改后的文件名\n>>";
			cin >> this->name;
			cout << "文件名更改成功" << endl; 
			
		}
		
		cout << "是否更改文件内容(yes/no)\n>>";
		cin >> com; 
		if(com == "yes")
		{		
			while(1)
			{
				cout << "选择 追加(a) / 覆盖(b)\n>>";
				cin >> com; 
				if(com == "a")
				{
					string c2; 
					cout << "请输入追加后的文件内容\n>>";
					cin >> c2;
					this->content += c2;
					cout << "追加内容成功" << endl;
					break; 
				}
				else if(com == "b")
					{
						cout << "请输入覆盖后的文件内容\n>>";
						cin >> this->content;
						cout << "覆盖内容成功" << endl;
						break;
					}
				else
					cout << "输入正确命令\n>>"; 
			}
		}
}

void file::delFile()
{
	file* fp = this->d->dir;
		if(fp == this)
		{
			this->d->dir = NULL;
			delete this;
		}
		else
		{
			while(fp->next != this)
				fp = fp->next;
			
			fp->next = this->next;
			delete this;
		}
		cout << "删除文件成功" << endl; 
}

void Stringsplit(string str, const char split,vector<string>& res);//分割字符串，用于路径查找

directory* cha(string dirName,directory* r);//在指定目录下递归查找目录 
directory* pathcha(string dirName,directory* r);//按路径查找目录 
void creatDirectory();//创建目录，接收父目录参数 
void viewDirectory();//查看目录，接收目标目录参数

file* chaFile(string fileName,directory* r);//在指定目录下查找文件
file* pathchaFile(string dirName,directory* r);////按路径查找文件 
void viewFile();//查看文化，接收目标文件参数 
void createFile();//创建文件，接收目录参数 
void modifyFile();//修改文件，接收目标文件参数 

void function(char k);//指令树立 
void mainInit();//初始化root目录 
void mean();//指令菜单 

int main()
{
	root = new directory();
	root->name = "root";
	mainInit();
	mean();
	char key = 0;
	do{
		cout << ">>";
		cin >> key; 
		getchar();
		function(key);
	}while(key != '0');

	return 0;
}

directory* pathcha(string dirName,directory* r)//按路径查找目录
{
	vector<string> vstr;
	Stringsplit(dirName,'/',vstr);
	directory* d = r;
	
	if(vstr.size() != 1)
		for(int i=1;i<vstr.size();++i)
		{
			d = cha(vstr[i],d);
			if(d == NULL)
				break;			
		}
	else
		d = cha(vstr[0],r);
	return d;
}

void creatDirectory()//创建目录 
{
	cout << "输入要在那个目录下创建\n>>";
	string dirName;
	cin >> dirName;
	getchar();
	
	directory* target = pathcha(dirName,root);
	if(target == NULL)
	{
		cout << "没有该目录" << endl;
		return;
	}
	target->creatDirectory();
}

void Stringsplit(string str, const char split,vector<string>& res)//分割字符串 
{
	istringstream iss(str);	// 输入流
	string token;			// 接收缓冲区
	while (getline(iss, token, split))	// 以split为分隔符
	{
		res.push_back(token);
	}
}

directory* cha(string dirName,directory* r)//按名称查找目录 
{
	directory* pr = r;
	directory* target = NULL;
	while(pr != NULL)
	{
		if(pr->name != dirName)
		{
			if(pr->child != NULL)
			{
				target = cha(dirName,pr->child);//优先查找子目录，再查找兄弟目录 
				if(target != NULL)
					return target;
			}
			pr = pr->next;
		}
		else
			return pr;
	}
	return NULL;
}

void viewDirectory()
{
	cout << "请输入要查看的目录\n>>";
	string dir;
	cin >> dir; 
	getchar();
	directory* r = pathcha(dir,root);
	if(r == NULL)
		cout << "没有该目录";
	else
		r->viewDirectory();
}

void createFile()//创建文件 
{	
	cout << "请输入要创建在那个目录\n>>";
	string dir;
	cin >> dir;
	
	directory* d = pathcha(dir,root);
	if(d == NULL)
		cout << "没有这个目录" << endl;
	else
	{
		d->createFile();
	}
		
}

file* chaFile(string fileName,directory* r)//按名称查找文件，遍历每一个目录，方法同cha() 
{
	directory* pr = r;
	file* target = NULL;
	
	if(pr->dir != NULL)
	{
		file* f = pr->dir;
		while(f != NULL)
		{
			if(f->name == fileName)
			{
				return f;
			}
			f = f->next;
		}
	}
	
	directory* q = pr->child;
	while(q != NULL)
	{
		target = chaFile(fileName,q);
		if(target != NULL)
			return target;
		q = q->next;
	}
	return NULL;
}

file* pathchaFile(string filePath)//按路径查找文件 
{
	vector<string> vstr;
	Stringsplit(filePath,'/',vstr);
	directory* d = root;
	file* f;
	
	if(vstr.size() != 1)	
	{
		for(int i=1;i<vstr.size()-1;++i)
		{
			d = cha(vstr[i],d);
			if(d == NULL)
				return NULL;			
		}
		f = chaFile(vstr[vstr.size()-1],d);
	}
	else
		f = chaFile(vstr[0],d);
		
	return f;
}

void viewFile()// 按名称查看文件 
{
	cout << "请输入要查看的文件名\n>>";
	string fileName;
	cin >> fileName;
	
	file* f = pathchaFile(fileName);
	if(f != NULL)
	{
		f->viewFile();
	}
	else 
	 	cout << "没有该文件" << endl;
	
	
}

void modifyFile()// 更改文件
{
	cout << "请输入要更改的文件名或路径\n>>";
	string fileName;
	cin >> fileName;
	
	file* f = pathchaFile(fileName);
	if(f != NULL)
		f->modifyFile(); 
	else 
	 	cout << "没有该文件" << endl;;
	
}

void deldir()//删除目录 
{
	cout << "请输入要删除的目录名或路径\n>>";
	string dirName;
	cin >> dirName;
	directory* d = pathcha(dirName,root);

	if(d != NULL)
		d->deldir();
	else
		cout << "目录不存在" << endl;
}

void delFile()//删除文件 
{
	cout << "请输入要删除的文件名或路径\n>>";
	string fileName;
	cin >> fileName;
	file* f = pathchaFile(fileName);
	if(f != NULL)
		f->delFile();
	else
		cout << "该文件不存在" << endl; 
} 

void mean()
{
	cout <<"\n\n\n";
	cout <<"*****************************************" << endl;
	cout <<"\t\t\t树形目录文件系统" << endl;
	cout <<"\t\t\t1 创建目录" << endl;
	cout <<"\t\t\t2 查看目录" << endl;
	cout <<"\t\t\t3 创建文件" << endl;
	cout <<"\t\t\t4 查看文件" << endl;
	cout <<"\t\t\t5 更改文件" << endl;
	cout <<"\t\t\t6 查看菜单" << endl;
	cout <<"\t\t\t7 删除文件" << endl;
	cout <<"\t\t\t8 查看目录结构" << endl;
	cout <<"\t\t\t9 删除目录" << endl;
	cout <<"\t\t\t0 退出系统" << endl;
	cout <<"******************************************" << endl;
	cout <<"\n\n\n";
}

void seeStruct()//查看目录结构 
{
	cout << "输入要查看的目录\n>>";
	string path;
	cin >> path;
	vector<string> vstr;
	Stringsplit(path,'/',vstr);
	directory* dir = root;
	
	if(vstr.size() != 1)
	{
		for(int i=1;i<vstr.size();++i)
		{
			dir = cha(vstr[i],dir);
			if(dir == NULL)
				break;
		}
	}
	else
	{
		if(vstr[0] != "root")
			dir = cha(vstr[0],dir);
	}
	
	if(dir != NULL)
	{
		dir->printStruct(dir,1);
	}
	else
	{
		cout << "该目录不存在" << endl;
	}
	
}

void function(char k)
{
	switch(k)
	{
		case '0':root->clear();cout << "已经退出系统";break;
		case '1':creatDirectory();break;
		case '2':viewDirectory();break;
		case '3':createFile();break; 
		case '4':viewFile();break;
		case '5':modifyFile();break;
		case '6':mean();break;
		case '7':delFile();break;
		case '8':seeStruct();break;
		case '9':deldir();break;
		default: cout << "请输入正确命令（如果命令正确，请先按回车）\n";break;
	}
}

void mainInit()//程序开始时先在root下创建一些目录 
{
	string sn[len] = {"bin","boot","dev","usr","sbin","home","lib","temp","var","etc","proc"};
	int pos = 0;
	root->child = new directory(root);
	root->child->name = sn[pos++];
	
	directory* d = root->child;
	
	for(int i=2;i<=len;i++)
	{
		d->next = new directory(root);
		d->initPath("/");
		d->next->name = sn[pos++];
		d = d->next;
	}
	root->num = len;
}
