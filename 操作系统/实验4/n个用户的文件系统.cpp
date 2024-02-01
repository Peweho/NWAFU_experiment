#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define len 10 //目录或文件名长度 
#define n 10 //用户数量 
#define m 2 //每个用户的文件数上限 

int state = 0;//状态位：0表示未登录，1表示已登录 
int num = 0;//用户数 

struct user
{
	char name[len];// 用户名
	char pwd[len];// 密码 
	int num;//文件数目 
	user* next;
}*first = NULL,*tail=NULL,*current = NULL; //first文件头指针 ， tail文件头尾指针，指向当前登录用户current 

struct file
{
	char name[len];// 文件名 
	char content[len*len];//文件内容 
	file* next; 
	int protect;//文件保护级别 
	user* master;//文件主 
}*fp= NULL,*ft = NULL;//fp文件头指针 ， ft文件尾指针


int login();
user* searchUser(char userName[]);
int searchPwd(user* use,char userPwd[]);
void makeUser();
void createFile();
void deleteFile();
void open();
file* searchFile(char fileName[]);
void read();
void write();
file* chaFile(char fileName[]);
user* chaUser(char userName[]);
void exit1();
void exit2();
int eqname(char* n1,char* n2);
void function1(char key);
void function2(char key);


void mean1()
{
	printf("\n\n\n");
	printf("*****************************************\n");
	printf("\t\t\tn个用户的文件系统\n");
	printf("\t\t\t1 登录\n");
	printf("\t\t\t2 注册\n");
	printf("\t\t\t0 退出\n");
	printf("******************************************\n");
	printf("\n\n\n>>");
}

void mean2()
{
	printf("\n\n\n");
	printf("*****************************************\n");
	printf("\t\t\tn个用户的文件系统\n");
	printf("\t\t\t1  creat\n");
	printf("\t\t\t2  delete\n");
	printf("\t\t\t3  open\n");
	printf("\t\t\t4  read\n");
	printf("\t\t\t5  write\n");
	printf("\t\t\t6  exit\n");
	printf("******************************************\n");
	printf("\n\n\n>>");
} 

int main()
{
	char key = '0';
	
	do{
		if(state == 0)
		{
			mean1();
			scanf("%c",&key);
			getchar();
			function1(key);
		}
		else
		{
			mean2();
			scanf("%c",&key);
			getchar();
			function2(key);
		}
	}while(key != '0');
	
	return 0;
}

int login()
{
	
	printf("请输入用户名\n>>");
	char userName[len];
	scanf("%s",userName);
	
	printf("请输入密码\n>>");
	char userPwd[len];
	scanf("%s",userPwd);
	
	
	user* use = searchUser(userName);
	if(use != NULL)
	{
		if(eqname(use->pwd,userPwd))
		{
			current = use; 
			printf("登录成功\n");
			state = 1; 
			return 1;
		}
		else
		{
			printf("用户名或密码错误\n");
			return 0;
		}
		
	}
	else 
	{
		printf("用户名或密码错误\n");
		return 0; 
	}
}

user* searchUser(char userName[])
{
	if(num == 0)
		return NULL;
		
	user* p = first;
	while(p != NULL)
	{
		if(eqname(p->name,userName))
		{
			return p;
		}
		p = p->next;
	}
}

void makeUser()
{
	if(num >= n)
	{
		printf("用户已满\n");
		return;
	}
	printf("请输入用户名\n>>");
	char userName[len];
	scanf("%s",userName);
	char userPwd1[len];
	char userPwd2[len];
	
	do{
		printf("请输入密码\n>>");
		scanf("%s",userPwd1);
		
		printf("请再次输入密码\n>>");
		scanf("%s",userPwd2);
	}while(!eqname(userPwd1,userPwd2));
	
	user* newUser = new user();
	strcpy(newUser->name,userName); 
	newUser->next = NULL;
	++num;
	
	if(num == 1)
	{
		first = newUser;
		tail = newUser;
	}
	else
	{
		tail->next = newUser;
		tail = tail->next;
	}
	printf("注册成功!!!\n");
}

void createFile()
{
	if(current->num >= m)
	{
		printf("当前创建文件已达上限");
		return;
	}
	
	char fileName[len];
	printf("请输入要创建的文件名称\n>>");
	scanf("%s",fileName);
	getchar();
	
	if(searchFile(fileName) != NULL)
	{
		printf("该文件已创建\n");
		return; 
	}
		
	
	file* fe = new file(); 
	strcpy(fe->name,fileName);
	getchar();
	printf("请输入文件内容\n>>");
	scanf("%s",fe->content);
	getchar();
	
	printf("请输入文件保护级别(1-3)\n");
	printf("1 允许所有人读写\n");
	printf("2 允许所有人读\n");
	printf("3 只允许自己读写\n>>");
	scanf("%d",&fe->protect);
	getchar();
	
	if(fp == NULL)
	{
		fp = fe;
		ft = fe;
	}
	else
	{
		fe = ft->next;
		ft = ft->next;
	}
	
	fe->master = current; 
	printf("文件创建成功\n");
}

void deleteFile()
{
	printf("请输入要删除的文件\n");
	char fileName[len];
	scanf("%s",fileName);
	getchar();
	file* fe = fp;
	
	if(eqname(fp->name,fileName))
	{
		if(fp->master == current)
		{
			fp = fp->next;
			delete fe;
			return;
		}
		else 
			printf("你没有权限删除这个文件\n");
	}
	else
	{
		while(fe->next != NULL)
		{
			if(eqname(fe->next->name,fileName))
			{
				if(fe->next->master == current)
				{
					delete fe->next;
					return;
				}
				else 
					printf("你没有权限删除这个文件\n");
			}
			fe = fe->next;
		}	
		printf("没有这个文件");
	}
}

void open()
{
	printf("请输入要打开的文件名称\n>>");
	char fileName[len]; 
	scanf("%s",fileName);
	getchar();
	
	file* fe = searchFile(fileName); 
	if(fe == NULL)
	{
		printf("没有这个文件\n");
		return; 
	}
	
	if(current == fe->master || fe->protect < 3)
	{
		printf("文件名：%s\n",fe->name);
		printf("文件主的用户名：%s\n",fe->master);
		printf("文件保护等级：%d\n",fe->protect);
		printf("文件内容：%s\n",fe->content);
	}
	else
	{
		printf("你没有权限打开这个文件\n");
	}
}

file* searchFile(char fileName[])
{
	file* fe = fp;
	while(fe != NULL)
	{
		if(eqname(fe->name,fileName))
		{
			return fe;
		}
		fe = fe->next;
	}
	return NULL;
}

void read()
{
	printf("请输入要读的文件名称\n>>");
	char fileName[len]; 
	scanf("%s",fileName);
	getchar();
	
	file* fe = searchFile(fileName); 
	if(fe == NULL)
	{
		printf("没有这个文件\n");
		return; 
	}
	
	if(current == fe->master || fe->protect < 3)
	{
		printf("文件内容：%s\n",fe->content);
	}
	else
	{
		printf("你没有权限读这个文件\n");
	}
}

void write()
{
	printf("请输入要写的文件名称\n>>");
	char fileName[len]; 
	scanf("%s",fileName);
	getchar();
	
	file* fe = searchFile(fileName); 
	if(fe == NULL)
	{
		printf("没有这个文件\n");
		return; 
	}
	
	if(current == fe->master || fe->protect < 2)
	{
		printf("请输入内容\n>>");
		scanf("%s",fe->content);
		getchar();
		printf("写入成功\n");
	}
	else
	{
		printf("你没有写这个文件的权限\n");
	}
}

void exit1()
{
	while(fp != NULL)
	{
		ft = fp;
		fp = fp->next;
		delete ft;
	}
	
	while(first != NULL)
	{
		tail = first;
		first = first->next;
		delete tail;
	}
	printf("退出成功\n");
}

void exit2()
{
	state = 0;
	current = NULL;
	printf("退出登录成功\n");
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

void function1(char key)
{
	switch(key)
	{
		case '1':login();break;
		case '2':makeUser();break;
		case '0':exit1();break;
		default:printf("请输入正确命令（如果命令正确，请先按回车）\n>>");break;
	}
}

void function2(char key)
{
	switch(key)
	{
		case '1':createFile();break;
		case '2':deleteFile();break;
		case '3':open();break;
		case '4':read();break;
		case '5':write();break;
		case '6':exit2();break;
		default:printf("请输入正确命令（如果命令正确，请先按回车）\n>>");break;
	}
}
