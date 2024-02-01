#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define len 10 //目录或文件名长度 

struct file
{
	char name[len];// 文件名 
	char content[len*len];//文件内容 
	file* next; 
	int protect;//文件保护级别 
};

struct directory
{
	char name[len];//目录名 
	file* dir;//目录下的文件指针，指向该目录下的第一个文件 
	int num;//子目录数 
	directory* child;//长子目录 ，指向该文件下的第一个子目录 
	directory* next;//兄弟目录 ，指向同一目录下的目录 
}*root;//根目录 

void init(directory* r)//初始化目录 
{
	r->child = NULL;
	r->next = NULL;
	r->dir = NULL;
	r->num = 0;
}

int eqname(char* n1,char* n2)//判断两个名称是否相等 
{
	for(int i=0;i<len;i++)
	{
		if(n1[i] == '\0' || n2[i] == '\0')
			return 1;
		if(n1[i] != n2[i])
			return 0;
	}
	return 1;
}


directory* cha(char* dirName,directory* r)//按名称查找目录 
{
	directory* pr = r;
	directory* target = NULL;
	while(pr != NULL)
	{
		if(!eqname(pr->name,dirName))
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

int creatDirectory()//创建目录 
{
	printf("输入要在那个目录下创建\n>>");
	char dirName[len];
	scanf("%s",&dirName);
	getchar();
	
	directory* target = cha(dirName,root);
	printf("当前目录：%s\n",target->name);
	
	if(target == NULL)
	{
		printf("没有该目录\n");
		return 0;
	}
	
	printf("输入要创建的目录名称\n>>");
	char Name[len];
	scanf("%s",&Name);
	getchar();
		
	if(target->num == 0)//若为该目录下的第一个目录。则用child指向新目录，否则连接在child后面 
	{
		target->child = new directory();
		strcpy(target->child->name,Name);
		init(target->child);
	}
	else
	{
		directory* pr = target->child;
		while(pr->next != NULL)
		{
			pr = pr->next;
		}
		pr->next = new directory();
		init(pr->next);
		strcpy(pr->next->name,Name);
	}
	++target->num;
	return 1;
}

void show()//按目录名称查看目录下的文件和目录 
{
	printf("请输入要查看的目录\n>>");
	char dir[len];
	scanf("%s",dir); 
	getchar();
	directory* r = cha(dir,root);
	if(r == NULL)
		printf("没有该目录");
	else
	{
		if(r->child != NULL)
		{
			directory* child = r->child;
			printf("%s下的目录：",dir); 
			while(child != NULL)
			{
				printf("%s ",child->name);
				child = child->next;
			}
			printf("\n");
		}
		else
		{
			printf("%s下没有目录\n",dir);
		}
		
		if(r->dir != NULL)
		{
			file* child = r->dir;
			printf("%s下的文件：",dir);
			while(child != NULL)
			{
				printf("%s ",child->name);
				child = child->next;
			}
			printf("\n");
		}
		else
		{
			printf("%s下没有文件\n",dir);
		}
	} 
}

int createFile()//创建文件 
{	
	printf("请输入要创建在那个目录\n>>");
	char dir[len];
	scanf("%s",dir);
	
	directory* d = cha(dir,root);
	if(d == NULL)
	{
		printf("没有这个目录\n");
		return 0;
	}
	file* fp = new file(); 
	printf("请输入要创建的文件名称\n>>");
	scanf("%s",fp->name);
	getchar();
	
	getchar();
	printf("请输入文件内容\n>>");
	scanf("%s",fp->content);
	getchar();
	
	printf("请输入文件保护级别(1-10)\n>>");
	scanf("%d",&fp->protect);
	getchar();
	
	if(d->dir != NULL)
	{
		file* p = d->dir;
		while(p->next != NULL)
		{
			p = p->next;
		}
		p->next = fp;
	}
	else
	{
		d->dir = fp;
	}
	
	return 1;
}

/*
清楚整个文件系统
方法：  1、先删除目录下的文件
		2、递归删除子目录 
*/ 
void clear(directory* r) 
{
	directory* pr = r;
	directory* del = pr;
	if(pr != NULL)
	{
		if(pr->dir != NULL)// 除目录下的文件
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
				clear(q);
			} 
		}
		
		delete pr;
	}
}

file* chaFile(char fileName[],directory* r)//按名称查找文件，遍历每一个目录，方法同cha() 
{
	directory* pr = r;
	file* target = NULL;
	
	if(pr->dir != NULL)
	{
		file* f = pr->dir;
		while(f != NULL)
		{
			if(eqname(f->name,fileName))
			{
				return f;
			}
			f = f->next;
		}
	}
	
	while(pr != NULL)
	{
		if(pr->child != NULL)
		{
			target = chaFile(fileName,pr->child);
			if(target != NULL)
				return target;
		}
		pr = pr->next;

	}
	return NULL;
}

void watchFile()// 按名称查看文件 
{
	printf("请输入要查看的文件名\n>>");
	char fileName[len];
	scanf("%s",fileName);
	
	file* f = chaFile(fileName,root);
	if(f != NULL)
	{
		printf("文件名：%s\n",f->name);
		printf("文件内容：%s\n",f->content);
		printf("文件保护级别：%d\n",f->protect);
	} 
	else 
	 	printf("没有该文件\n");
	
	
}

void gaiFilelname()// 更改文件名称 
{
	printf("请输入要改变的文件名\n>>");
	char fileName[len];
	scanf("%s",fileName);
	
	file* f = chaFile(fileName,root);
	if(f != NULL)
	{
		printf("请输入更改后的文件名\n>>");
		scanf("%s",f->name);
		printf("文件名更改成功\n"); 
	} 
	else 
	 	printf("没有该文件\n");
	
}

void gaiFilelprotect()// 更改文件保护级 
{
	printf("请输入要改变的文件名\n>>");
	char fileName[len];
	scanf("%s",fileName);
	
	file* f = chaFile(fileName,root);
	if(f != NULL)
	{
		printf("请输入更改后的的文件保护级\n>>");
		scanf("%d",f->protect);
		printf("文件名更改成功\n");
	} 
	else 
	 	printf("没有该文件\n");
	
}


void function(char k)
{
	switch(k)
	{
		case '0':clear(root);printf("已经退出系统");break;
		case '1':creatDirectory();break;
		case '2':show();break;
		case '3':createFile();break; 
		case '4':watchFile();break;
		case '5':gaiFilelname();break;
		case '6':gaiFilelprotect();break;
		default:printf("请输入正确命令（如果命令正确，请先按回车）\n>>");break;
	}
}

void mean()
{
	printf("\n\n\n");
	printf("*****************************************\n");
	printf("\t\t\t树形目录文件系统\n");
	printf("\t\t\t1 创建目录\n");
	printf("\t\t\t2 查看目录\n");
	printf("\t\t\t3 创建文件\n");
	printf("\t\t\t4 查看文件\n");
	printf("\t\t\t5 更改文件名\n");
	printf("\t\t\t6 更改文件保护级\n");
	printf("\t\t\t0 退出系统\n");
	printf("*******************s**********************\n");
	printf("\n\n\n>>");
}



int main(){
	root = new directory();
	strcpy(root->name,"root");
	init(root);
	
	char key = 0;
	do{
		mean();
		scanf("%c",&key);
		getchar();
		function(key);
	}while(key != '0');

	return 0;
}
