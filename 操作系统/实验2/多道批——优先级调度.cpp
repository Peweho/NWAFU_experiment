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
	double Rp;
}*ready=NULL,*run=NULL,*runTail = NULL,*p,*q;
typedef struct jcb JCB; //���ã�����ҵ�ĸ�����Ϣ���з�װ���������ҵ�����͹���

void inital()//������ҵ���ƿ����,�Ƚ����ų������ȷ����ģʽ����
{
	printf("\n����ϵͳ���������ҵ����:");
	scanf("%d",&Mutiple); 
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


void HRN ( JCB *ptr )
{
    int i,iden;
    //��ͣ�Ը��ù۲�
    JCB *temp;
    // ����ҵ����HRN�������
      for(i=0; i<n; i++)
    {
        ptr = temp=ready;
        iden=1;
        //�ҵ���Ӧ�����Ŀ����е���ҵ
        do
        {
            if(ptr->state=='W'&&ptr->reachtime<=times && runLength()<Mutiple)
            {
				ptr->Rp =(double)(times - ptr->reachtime + ptr->needtime)/ptr->needtime;
            	
                if(iden)
                {
                    temp=ptr;
                    iden=0;//�ҵ�����0
                }
                else if(ptr->Rp > temp->Rp)
                  temp=ptr;
            }
            ptr=ptr -> next;
        }
        while (ptr != NULL);//������������ҵ������зǿն���

        if(iden)
        {
            return;
        }
        else
        {
        	temp->starttime = times;
			temp->state ='R';
			temp->cycletime = (float)(temp->finishtime -temp->reachtime);
			temp->cltime = (float)(temp->cycletime / temp->needtime);
			T1 += temp->cycletime;
			T2 += temp->cltime;
        	printf("��ҵ[ %s ]�����ڴ�\n",temp->name);
            runList(temp);
            n--;
        }
    }
}

int main()
{
	inital();
	JCB *ptr = ready;
	while(ready != NULL)
	{
		HRN(ptr);
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
/*
2
4
w1
5
w2
8
w3
6
w4
3
*/
