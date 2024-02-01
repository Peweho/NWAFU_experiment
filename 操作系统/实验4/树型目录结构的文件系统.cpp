#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define len 10 //Ŀ¼���ļ������� 

struct file
{
	char name[len];// �ļ��� 
	char content[len*len];//�ļ����� 
	file* next; 
	int protect;//�ļ��������� 
};

struct directory
{
	char name[len];//Ŀ¼�� 
	file* dir;//Ŀ¼�µ��ļ�ָ�룬ָ���Ŀ¼�µĵ�һ���ļ� 
	int num;//��Ŀ¼�� 
	directory* child;//����Ŀ¼ ��ָ����ļ��µĵ�һ����Ŀ¼ 
	directory* next;//�ֵ�Ŀ¼ ��ָ��ͬһĿ¼�µ�Ŀ¼ 
}*root;//��Ŀ¼ 

void init(directory* r)//��ʼ��Ŀ¼ 
{
	r->child = NULL;
	r->next = NULL;
	r->dir = NULL;
	r->num = 0;
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


directory* cha(char* dirName,directory* r)//�����Ʋ���Ŀ¼ 
{
	directory* pr = r;
	directory* target = NULL;
	while(pr != NULL)
	{
		if(!eqname(pr->name,dirName))
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

int creatDirectory()//����Ŀ¼ 
{
	printf("����Ҫ���Ǹ�Ŀ¼�´���\n>>");
	char dirName[len];
	scanf("%s",&dirName);
	getchar();
	
	directory* target = cha(dirName,root);
	printf("��ǰĿ¼��%s\n",target->name);
	
	if(target == NULL)
	{
		printf("û�и�Ŀ¼\n");
		return 0;
	}
	
	printf("����Ҫ������Ŀ¼����\n>>");
	char Name[len];
	scanf("%s",&Name);
	getchar();
		
	if(target->num == 0)//��Ϊ��Ŀ¼�µĵ�һ��Ŀ¼������childָ����Ŀ¼������������child���� 
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

void show()//��Ŀ¼���Ʋ鿴Ŀ¼�µ��ļ���Ŀ¼ 
{
	printf("������Ҫ�鿴��Ŀ¼\n>>");
	char dir[len];
	scanf("%s",dir); 
	getchar();
	directory* r = cha(dir,root);
	if(r == NULL)
		printf("û�и�Ŀ¼");
	else
	{
		if(r->child != NULL)
		{
			directory* child = r->child;
			printf("%s�µ�Ŀ¼��",dir); 
			while(child != NULL)
			{
				printf("%s ",child->name);
				child = child->next;
			}
			printf("\n");
		}
		else
		{
			printf("%s��û��Ŀ¼\n",dir);
		}
		
		if(r->dir != NULL)
		{
			file* child = r->dir;
			printf("%s�µ��ļ���",dir);
			while(child != NULL)
			{
				printf("%s ",child->name);
				child = child->next;
			}
			printf("\n");
		}
		else
		{
			printf("%s��û���ļ�\n",dir);
		}
	} 
}

int createFile()//�����ļ� 
{	
	printf("������Ҫ�������Ǹ�Ŀ¼\n>>");
	char dir[len];
	scanf("%s",dir);
	
	directory* d = cha(dir,root);
	if(d == NULL)
	{
		printf("û�����Ŀ¼\n");
		return 0;
	}
	file* fp = new file(); 
	printf("������Ҫ�������ļ�����\n>>");
	scanf("%s",fp->name);
	getchar();
	
	getchar();
	printf("�������ļ�����\n>>");
	scanf("%s",fp->content);
	getchar();
	
	printf("�������ļ���������(1-10)\n>>");
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
��������ļ�ϵͳ
������  1����ɾ��Ŀ¼�µ��ļ�
		2���ݹ�ɾ����Ŀ¼ 
*/ 
void clear(directory* r) 
{
	directory* pr = r;
	directory* del = pr;
	if(pr != NULL)
	{
		if(pr->dir != NULL)// ��Ŀ¼�µ��ļ�
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
				clear(q);
			} 
		}
		
		delete pr;
	}
}

file* chaFile(char fileName[],directory* r)//�����Ʋ����ļ�������ÿһ��Ŀ¼������ͬcha() 
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

void watchFile()// �����Ʋ鿴�ļ� 
{
	printf("������Ҫ�鿴���ļ���\n>>");
	char fileName[len];
	scanf("%s",fileName);
	
	file* f = chaFile(fileName,root);
	if(f != NULL)
	{
		printf("�ļ�����%s\n",f->name);
		printf("�ļ����ݣ�%s\n",f->content);
		printf("�ļ���������%d\n",f->protect);
	} 
	else 
	 	printf("û�и��ļ�\n");
	
	
}

void gaiFilelname()// �����ļ����� 
{
	printf("������Ҫ�ı���ļ���\n>>");
	char fileName[len];
	scanf("%s",fileName);
	
	file* f = chaFile(fileName,root);
	if(f != NULL)
	{
		printf("��������ĺ���ļ���\n>>");
		scanf("%s",f->name);
		printf("�ļ������ĳɹ�\n"); 
	} 
	else 
	 	printf("û�и��ļ�\n");
	
}

void gaiFilelprotect()// �����ļ������� 
{
	printf("������Ҫ�ı���ļ���\n>>");
	char fileName[len];
	scanf("%s",fileName);
	
	file* f = chaFile(fileName,root);
	if(f != NULL)
	{
		printf("��������ĺ�ĵ��ļ�������\n>>");
		scanf("%d",f->protect);
		printf("�ļ������ĳɹ�\n");
	} 
	else 
	 	printf("û�и��ļ�\n");
	
}


void function(char k)
{
	switch(k)
	{
		case '0':clear(root);printf("�Ѿ��˳�ϵͳ");break;
		case '1':creatDirectory();break;
		case '2':show();break;
		case '3':createFile();break; 
		case '4':watchFile();break;
		case '5':gaiFilelname();break;
		case '6':gaiFilelprotect();break;
		default:printf("��������ȷ������������ȷ�����Ȱ��س���\n>>");break;
	}
}

void mean()
{
	printf("\n\n\n");
	printf("*****************************************\n");
	printf("\t\t\t����Ŀ¼�ļ�ϵͳ\n");
	printf("\t\t\t1 ����Ŀ¼\n");
	printf("\t\t\t2 �鿴Ŀ¼\n");
	printf("\t\t\t3 �����ļ�\n");
	printf("\t\t\t4 �鿴�ļ�\n");
	printf("\t\t\t5 �����ļ���\n");
	printf("\t\t\t6 �����ļ�������\n");
	printf("\t\t\t0 �˳�ϵͳ\n");
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
