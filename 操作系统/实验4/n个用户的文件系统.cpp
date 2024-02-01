#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define len 10 //Ŀ¼���ļ������� 
#define n 10 //�û����� 
#define m 2 //ÿ���û����ļ������� 

int state = 0;//״̬λ��0��ʾδ��¼��1��ʾ�ѵ�¼ 
int num = 0;//�û��� 

struct user
{
	char name[len];// �û���
	char pwd[len];// ���� 
	int num;//�ļ���Ŀ 
	user* next;
}*first = NULL,*tail=NULL,*current = NULL; //first�ļ�ͷָ�� �� tail�ļ�ͷβָ�룬ָ��ǰ��¼�û�current 

struct file
{
	char name[len];// �ļ��� 
	char content[len*len];//�ļ����� 
	file* next; 
	int protect;//�ļ��������� 
	user* master;//�ļ��� 
}*fp= NULL,*ft = NULL;//fp�ļ�ͷָ�� �� ft�ļ�βָ��


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
	printf("\t\t\tn���û����ļ�ϵͳ\n");
	printf("\t\t\t1 ��¼\n");
	printf("\t\t\t2 ע��\n");
	printf("\t\t\t0 �˳�\n");
	printf("******************************************\n");
	printf("\n\n\n>>");
}

void mean2()
{
	printf("\n\n\n");
	printf("*****************************************\n");
	printf("\t\t\tn���û����ļ�ϵͳ\n");
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
	
	printf("�������û���\n>>");
	char userName[len];
	scanf("%s",userName);
	
	printf("����������\n>>");
	char userPwd[len];
	scanf("%s",userPwd);
	
	
	user* use = searchUser(userName);
	if(use != NULL)
	{
		if(eqname(use->pwd,userPwd))
		{
			current = use; 
			printf("��¼�ɹ�\n");
			state = 1; 
			return 1;
		}
		else
		{
			printf("�û������������\n");
			return 0;
		}
		
	}
	else 
	{
		printf("�û������������\n");
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
		printf("�û�����\n");
		return;
	}
	printf("�������û���\n>>");
	char userName[len];
	scanf("%s",userName);
	char userPwd1[len];
	char userPwd2[len];
	
	do{
		printf("����������\n>>");
		scanf("%s",userPwd1);
		
		printf("���ٴ���������\n>>");
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
	printf("ע��ɹ�!!!\n");
}

void createFile()
{
	if(current->num >= m)
	{
		printf("��ǰ�����ļ��Ѵ�����");
		return;
	}
	
	char fileName[len];
	printf("������Ҫ�������ļ�����\n>>");
	scanf("%s",fileName);
	getchar();
	
	if(searchFile(fileName) != NULL)
	{
		printf("���ļ��Ѵ���\n");
		return; 
	}
		
	
	file* fe = new file(); 
	strcpy(fe->name,fileName);
	getchar();
	printf("�������ļ�����\n>>");
	scanf("%s",fe->content);
	getchar();
	
	printf("�������ļ���������(1-3)\n");
	printf("1 ���������˶�д\n");
	printf("2 ���������˶�\n");
	printf("3 ֻ�����Լ���д\n>>");
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
	printf("�ļ������ɹ�\n");
}

void deleteFile()
{
	printf("������Ҫɾ�����ļ�\n");
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
			printf("��û��Ȩ��ɾ������ļ�\n");
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
					printf("��û��Ȩ��ɾ������ļ�\n");
			}
			fe = fe->next;
		}	
		printf("û������ļ�");
	}
}

void open()
{
	printf("������Ҫ�򿪵��ļ�����\n>>");
	char fileName[len]; 
	scanf("%s",fileName);
	getchar();
	
	file* fe = searchFile(fileName); 
	if(fe == NULL)
	{
		printf("û������ļ�\n");
		return; 
	}
	
	if(current == fe->master || fe->protect < 3)
	{
		printf("�ļ�����%s\n",fe->name);
		printf("�ļ������û�����%s\n",fe->master);
		printf("�ļ������ȼ���%d\n",fe->protect);
		printf("�ļ����ݣ�%s\n",fe->content);
	}
	else
	{
		printf("��û��Ȩ�޴�����ļ�\n");
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
	printf("������Ҫ�����ļ�����\n>>");
	char fileName[len]; 
	scanf("%s",fileName);
	getchar();
	
	file* fe = searchFile(fileName); 
	if(fe == NULL)
	{
		printf("û������ļ�\n");
		return; 
	}
	
	if(current == fe->master || fe->protect < 3)
	{
		printf("�ļ����ݣ�%s\n",fe->content);
	}
	else
	{
		printf("��û��Ȩ�޶�����ļ�\n");
	}
}

void write()
{
	printf("������Ҫд���ļ�����\n>>");
	char fileName[len]; 
	scanf("%s",fileName);
	getchar();
	
	file* fe = searchFile(fileName); 
	if(fe == NULL)
	{
		printf("û������ļ�\n");
		return; 
	}
	
	if(current == fe->master || fe->protect < 2)
	{
		printf("����������\n>>");
		scanf("%s",fe->content);
		getchar();
		printf("д��ɹ�\n");
	}
	else
	{
		printf("��û��д����ļ���Ȩ��\n");
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
	printf("�˳��ɹ�\n");
}

void exit2()
{
	state = 0;
	current = NULL;
	printf("�˳���¼�ɹ�\n");
}

int eqname(char* n1,char* n2)//�ж����������Ƿ���� 
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
		default:printf("��������ȷ������������ȷ�����Ȱ��س���\n>>");break;
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
		default:printf("��������ȷ������������ȷ�����Ȱ��س���\n>>");break;
	}
}
