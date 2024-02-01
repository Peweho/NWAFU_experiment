#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define getpch(type) (type*)malloc(sizeof(type))
int n;
float T1=0,T2=0;
int times=0;
int Mutiple = 0;
const int numSource = 3;

struct Source
{
	const int s[numSource] = {16,6,9};
	int useda[numSource] = {0,0,0};
};

Source source = Source();

struct jcb//��ҵ���ƿ�
{
	char name[10];// ���ƿ�����
	int reachtime;//��ҵ����ʱ��
	int starttime;//��ҵ��ʼ����ʱ��
	int needtime;//��ҵ������Ҫʱ��
	int finishtime;//��ҵ���ʱ��
	float cycletime;//��ҵ��תʱ��
	float cltime;//��ҵ��Ȩ��תʱ��
	char state;//��ҵ״̬
	struct jcb *next;//�ṹ��ָ��
	int source[numSource];
}*ready=NULL,*run=NULL,*runTail = NULL,*p,*q;
typedef struct jcb JCB; //���ã�����ҵ�ĸ�����Ϣ���з�װ���������ҵ�����͹���

void inital()//������ҵ���ƿ����,�Ƚ����ų������ȷ����ģʽ����
{
	printf("\n����ϵͳ���������ҵ����:");
	scanf("%d",&Mutiple); 
	for(int j=0;j<numSource;++j)
	{
		printf("\n��Դ%c������%d",j+65,source.s[j]);
	}
	int i;
	printf("\n������ҵ��:");
	scanf("%d", &n);
	for (i = 0; i<n; i++)
	{
		p = getpch(JCB);
		printf("\n������ҵ��:");
		scanf("%s", p->name);
		getchar();
		p->reachtime = i;
		printf("��ҵĬ�ϵ���ʱ��:%d", i);
		printf("\n������ҵҪ���е�ʱ��:");
		scanf("%d", &p->needtime);
		for(int j=0;j<numSource;++j)
		{
			printf("\n������ҵ����Դ%c������:",j+65);
			scanf("%d",&p->source[j]);
			
			while(p->source[j] > source.s[j])
			{
				printf("\n������������ҵ����Դ%c������:",j+65);
				scanf("%d",&p->source[j]);
			}
		}
		p->state ='W';
		p->next = NULL;
		if(ready == NULL)
			ready = q = p;
		else
		{
			q->next = p;
			q = p;
		}
	}
}


void runList(JCB *j)
{
	if(j == ready)//�Ƚ�Ҫ���е���ҵ�Ӷ����з������
	{
		ready = j->next;
		j->next = NULL;
	}
	else
	{
		q = ready;
		while(q->next != j) 
			q = q->next;
		q->next = j->next;
	}
	
	if(run == NULL)
	{
		run = j;
		runTail = j;
	}
	else
	{
		runTail->next = j;
		runTail = j;		
	}
	
	for(int l=0;l<numSource;++l)
		source.useda[l] += j->source[l];
}

int isrun()
{
	for(int j=0;j<numSource;++j)
	{
		if(p->source[j] > source.s[j] - source.useda[j])
			return 0;
	}
	return 1;
}

void runIofo()
{

	printf("��ҵ������� | \n��ҵ�� | \t��ʼʱ�� | \t��Ҫʱ�� | \t�Ѿ�����ʱ��\t\n"); 
	JCB *r = run;
	while(r != NULL)
	{
		if(r->needtime != times - r->starttime)
			printf("%s\t\t%d\t\t%d\t\t%d\t\n",r->name,r->starttime,r->needtime,times - r->starttime);
		r = r->next;
	}
}

void running()
{
	times++;
	runIofo();
	JCB *r = run;
	JCB *pr = NULL;
	while(r != NULL)
	{
		if(r->needtime == times - r->starttime)
		{
			printf("��ҵ[ %s ]�Ѿ����\n",r->name);
			for(int j=0;j<numSource;++j)
				source.useda[j] -= r->source[j];
			if(pr == NULL)
			{
				run = r->next;
				r->next = NULL;
				free(r);
				r = run;
			}
			else
			{
				pr->next = r->next;
				r->next = NULL;
				free(r);
				r = pr->next;
			}
		}
		else
		{
			pr = r; 
			r = r->next;
		}	
	}
}

int runLength()
{
	int count = 0;
	JCB *r = run;
	while(r != NULL)
	{
		++count;
		r = r->next;
	}
	
	return count;
}

int main()
{
	inital();
	JCB *ptr = ready;
	while(ready != NULL)
	{
		if(ptr->state =='W' && ptr->reachtime <= times && isrun() && runLength() < Mutiple) 
		{
			ptr->starttime = times;
			ptr->state ='R';
			ptr->cycletime = (float)(ptr->finishtime - ptr->reachtime);
			ptr->cltime = (float)(ptr->cycletime / ptr->needtime);
			T1 += ptr->cycletime;
			T2 += ptr->cltime;
			runList(ptr);
			printf("��ҵ[ %s ]�����ڴ�\n",ptr->name);
			ptr = ready;
		}
		getchar(); 
		running();
		printf("*****************************************\n");
	}
	while(run != NULL)
	{
		getchar(); 
		running();
	}
	return 0;
}

