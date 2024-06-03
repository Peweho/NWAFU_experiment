#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <sstream>
#include <string>

#define len 11 //root�³�ʼĿ¼��

using namespace std;

class file;

class directory
{
public:
	string name;//Ŀ¼��
	string path;//Ŀ¼��ַ 
	file* dir;//Ŀ¼�µ��ļ�ָ�룬ָ���Ŀ¼�µĵ�һ���ļ� 
	int num;//��Ŀ¼�� 
	directory* child;//����Ŀ¼ ��ָ����ļ��µĵ�һ����Ŀ¼ 
	directory* next;//�ֵ�Ŀ¼ ��ָ��ͬһĿ¼�µ�Ŀ¼ 
	directory* fu;//��Ŀ¼ 
	
	directory();//��ʼ��Ŀ¼ 
	directory(directory* f);//��ʼ��Ŀ¼�����Ҹ�Ŀ¼ָ����Ŀ¼ 
	void creatDirectory();//����Ŀ¼ 
	directory* initPath(string path,directory* r);//����Ŀ¼·�� 
	void viewDirectory();//�鿴Ŀ¼ 
	void createFile();//�ڵ�ǰĿ¼�´����ļ� 
	void printStruct(directory* d,int floor);//���Ŀ¼�ṹ 
	void deldir();//�޸�����ɾ��Ŀ¼ 
	void clear();//ɾ��Ŀ¼ 
};

directory *root;//��Ŀ¼ 

class file
{
public:
	string name;// �ļ��� 
	directory* d;//�ļ�����Ŀ¼ 
	string content;//�ļ����� 
	file* next;
	string creatTime;//�ļ�����ʱ�� 
	
	file();
	void viewFile();//�鿴�ļ� 
	void modifyFile();//�޸��ļ� 
	void delFile();//ɾ���ļ� 
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

directory::directory(directory* f)//��ʼ��Ŀ¼�����Ҹ�Ŀ¼ָ����Ŀ¼ 
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
				target = initPath(path,pr->child);//���Ȳ�����Ŀ¼���ٲ����ֵ�Ŀ¼ 
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
	cout << "������Ҫ�������ļ�����\n>>";
	string name;
	cin >> name;
	file* fd = this->dir;
	while(fd != NULL)
	{
		if(fd->name == name)
		{
			cout << "�ļ��Ѵ���" << endl;
			return;
		}
		fd = fd->next;
	}
	
	file* fp = new file(); 
	fp->d = this;
	fp->name = name;
	
	getchar();
	cout << "�������ļ�����\n>>";
	cin >> fp->content;
	getchar();
	
	time_t timep;
    time(&timep); //��ȡ��1970������˶����룬����time_t���͵�timep
    struct tm *creatTime = localtime(&timep);//��localtime������ת��Ϊstruct tm�ṹ��
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
	cout << "�ļ������ɹ�" << endl;; 
}

void directory::creatDirectory()//����Ŀ¼ 
{
		cout << "��ǰĿ¼��" << this->path << this->name << endl;
		cout << "����Ҫ������Ŀ¼����\n>>";
		string Name;
		cin >> Name;
		getchar();
		
		directory* child = this->child;
		while(child != NULL)
		{
			if(child->name == Name)
			{
				cout << "Ŀ¼�Ѵ��ڣ�����" << endl; 
				return;
			}
			child = child->next;
		}
			
		if(this->num == 0)//��Ϊ��Ŀ¼�µĵ�һ��Ŀ¼������childָ����Ŀ¼������������child���� 
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
		cout << "Ŀ¼�����ɹ�" << endl;
}

void directory::viewDirectory()//��Ŀ¼���Ʋ鿴Ŀ¼�µ��ļ���Ŀ¼ 
{
		cout << "��ǰĿ¼��" << this->path << this->name << endl;
		
		if(this->child != NULL)
		{
			directory* child = this->child;
			cout << this->name << "�µ�Ŀ¼��"; 
			while(child != NULL)
			{
				cout << child->name << ' ';
				child = child->next;
			}
			cout << endl;;
		}
		else
		{
			cout << this->name << "��û��Ŀ¼" << endl;;
		}
		
		if(this->dir != NULL)
		{
			file* child = this->dir;
			cout << this->name << "�µ��ļ���";
			while(child != NULL)
			{
				cout << child->name << ' ';
				child = child->next;
			}
			cout << endl;
		}
		else
		{
			cout << this->name << "��û���ļ�" << endl;
		}
}

void directory::printStruct(directory* d,int floor)//��ӡĿ¼�ṹ 
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
		cout<< "Ŀ¼��ɾ��" << endl;
}

/*
ɾ��Ŀ¼ 
������  1����ɾ��Ŀ¼�µ��ļ�
		2���ݹ�ɾ����Ŀ¼ 
*/ 
void directory::clear() 
{
	directory* pr = this;
	if(pr != NULL)
	{
		if(pr->dir != NULL)// ɾ��Ŀ¼�µ��ļ�
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
		
		if(pr->child != NULL)//�ݹ�ɾ����Ŀ¼ 
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
	cout << "�ļ�·����" << this->d->path << this->d->name << endl; 
	cout << "�ļ�����" << this->name << endl;
	cout << "�ļ����ݣ�" << this->content << endl;
	cout << "�ļ�����ʱ�䣺" << this->creatTime;
	//printf("%d/%d/%d %02d:%02d:%02d\n", 1900 + this->creatTime->tm_year, 1+ this->creatTime->tm_mon, this->creatTime->tm_mday,this->creatTime->tm_hour, this->creatTime->tm_min, this->creatTime->tm_sec);

}

void file::modifyFile()
{
		cout << "�Ƿ�����ļ���(yes/no)\n>>";
		string com;
		cin >> com;
		if(com == "yes")
		{
			cout << "��������ĺ���ļ���\n>>";
			cin >> this->name;
			cout << "�ļ������ĳɹ�" << endl; 
			
		}
		
		cout << "�Ƿ�����ļ�����(yes/no)\n>>";
		cin >> com; 
		if(com == "yes")
		{		
			while(1)
			{
				cout << "ѡ�� ׷��(a) / ����(b)\n>>";
				cin >> com; 
				if(com == "a")
				{
					string c2; 
					cout << "������׷�Ӻ���ļ�����\n>>";
					cin >> c2;
					this->content += c2;
					cout << "׷�����ݳɹ�" << endl;
					break; 
				}
				else if(com == "b")
					{
						cout << "�����븲�Ǻ���ļ�����\n>>";
						cin >> this->content;
						cout << "�������ݳɹ�" << endl;
						break;
					}
				else
					cout << "������ȷ����\n>>"; 
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
		cout << "ɾ���ļ��ɹ�" << endl; 
}

void Stringsplit(string str, const char split,vector<string>& res);//�ָ��ַ���������·������

directory* cha(string dirName,directory* r);//��ָ��Ŀ¼�µݹ����Ŀ¼ 
directory* pathcha(string dirName,directory* r);//��·������Ŀ¼ 
void creatDirectory();//����Ŀ¼�����ո�Ŀ¼���� 
void viewDirectory();//�鿴Ŀ¼������Ŀ��Ŀ¼����

file* chaFile(string fileName,directory* r);//��ָ��Ŀ¼�²����ļ�
file* pathchaFile(string dirName,directory* r);////��·�������ļ� 
void viewFile();//�鿴�Ļ�������Ŀ���ļ����� 
void createFile();//�����ļ�������Ŀ¼���� 
void modifyFile();//�޸��ļ�������Ŀ���ļ����� 

void function(char k);//ָ������ 
void mainInit();//��ʼ��rootĿ¼ 
void mean();//ָ��˵� 

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

directory* pathcha(string dirName,directory* r)//��·������Ŀ¼
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

void creatDirectory()//����Ŀ¼ 
{
	cout << "����Ҫ���Ǹ�Ŀ¼�´���\n>>";
	string dirName;
	cin >> dirName;
	getchar();
	
	directory* target = pathcha(dirName,root);
	if(target == NULL)
	{
		cout << "û�и�Ŀ¼" << endl;
		return;
	}
	target->creatDirectory();
}

void Stringsplit(string str, const char split,vector<string>& res)//�ָ��ַ��� 
{
	istringstream iss(str);	// ������
	string token;			// ���ջ�����
	while (getline(iss, token, split))	// ��splitΪ�ָ���
	{
		res.push_back(token);
	}
}

directory* cha(string dirName,directory* r)//�����Ʋ���Ŀ¼ 
{
	directory* pr = r;
	directory* target = NULL;
	while(pr != NULL)
	{
		if(pr->name != dirName)
		{
			if(pr->child != NULL)
			{
				target = cha(dirName,pr->child);//���Ȳ�����Ŀ¼���ٲ����ֵ�Ŀ¼ 
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
	cout << "������Ҫ�鿴��Ŀ¼\n>>";
	string dir;
	cin >> dir; 
	getchar();
	directory* r = pathcha(dir,root);
	if(r == NULL)
		cout << "û�и�Ŀ¼";
	else
		r->viewDirectory();
}

void createFile()//�����ļ� 
{	
	cout << "������Ҫ�������Ǹ�Ŀ¼\n>>";
	string dir;
	cin >> dir;
	
	directory* d = pathcha(dir,root);
	if(d == NULL)
		cout << "û�����Ŀ¼" << endl;
	else
	{
		d->createFile();
	}
		
}

file* chaFile(string fileName,directory* r)//�����Ʋ����ļ�������ÿһ��Ŀ¼������ͬcha() 
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

file* pathchaFile(string filePath)//��·�������ļ� 
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

void viewFile()// �����Ʋ鿴�ļ� 
{
	cout << "������Ҫ�鿴���ļ���\n>>";
	string fileName;
	cin >> fileName;
	
	file* f = pathchaFile(fileName);
	if(f != NULL)
	{
		f->viewFile();
	}
	else 
	 	cout << "û�и��ļ�" << endl;
	
	
}

void modifyFile()// �����ļ�
{
	cout << "������Ҫ���ĵ��ļ�����·��\n>>";
	string fileName;
	cin >> fileName;
	
	file* f = pathchaFile(fileName);
	if(f != NULL)
		f->modifyFile(); 
	else 
	 	cout << "û�и��ļ�" << endl;;
	
}

void deldir()//ɾ��Ŀ¼ 
{
	cout << "������Ҫɾ����Ŀ¼����·��\n>>";
	string dirName;
	cin >> dirName;
	directory* d = pathcha(dirName,root);

	if(d != NULL)
		d->deldir();
	else
		cout << "Ŀ¼������" << endl;
}

void delFile()//ɾ���ļ� 
{
	cout << "������Ҫɾ�����ļ�����·��\n>>";
	string fileName;
	cin >> fileName;
	file* f = pathchaFile(fileName);
	if(f != NULL)
		f->delFile();
	else
		cout << "���ļ�������" << endl; 
} 

void mean()
{
	cout <<"\n\n\n";
	cout <<"*****************************************" << endl;
	cout <<"\t\t\t����Ŀ¼�ļ�ϵͳ" << endl;
	cout <<"\t\t\t1 ����Ŀ¼" << endl;
	cout <<"\t\t\t2 �鿴Ŀ¼" << endl;
	cout <<"\t\t\t3 �����ļ�" << endl;
	cout <<"\t\t\t4 �鿴�ļ�" << endl;
	cout <<"\t\t\t5 �����ļ�" << endl;
	cout <<"\t\t\t6 �鿴�˵�" << endl;
	cout <<"\t\t\t7 ɾ���ļ�" << endl;
	cout <<"\t\t\t8 �鿴Ŀ¼�ṹ" << endl;
	cout <<"\t\t\t9 ɾ��Ŀ¼" << endl;
	cout <<"\t\t\t0 �˳�ϵͳ" << endl;
	cout <<"******************************************" << endl;
	cout <<"\n\n\n";
}

void seeStruct()//�鿴Ŀ¼�ṹ 
{
	cout << "����Ҫ�鿴��Ŀ¼\n>>";
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
		cout << "��Ŀ¼������" << endl;
	}
	
}

void function(char k)
{
	switch(k)
	{
		case '0':root->clear();cout << "�Ѿ��˳�ϵͳ";break;
		case '1':creatDirectory();break;
		case '2':viewDirectory();break;
		case '3':createFile();break; 
		case '4':viewFile();break;
		case '5':modifyFile();break;
		case '6':mean();break;
		case '7':delFile();break;
		case '8':seeStruct();break;
		case '9':deldir();break;
		default: cout << "��������ȷ������������ȷ�����Ȱ��س���\n";break;
	}
}

void mainInit()//����ʼʱ����root�´���һЩĿ¼ 
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
