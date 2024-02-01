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

struct jcb//作业控制块
{
	char name[10];// 控制块名字
	int reachtime;//作业到达时间
	int starttime;//作业开始运行时间
	int needtime;//作业运行需要时间
	int finishtime;//作业完成时间
	float cycletime;//作业周转时间
	float cltime;//作业带权周转时间
	char state;//作业状态
	struct jcb *next;//结构体指针
	double Rp;
}*ready=NULL,*run=NULL,*runTail = NULL,*p,*q;
typedef struct jcb JCB; //作用：对作业的各项信息进行封装，方便对作业操作和管理

void inital()//建立作业控制块队列,先将其排成先来先服务的模式队列
{
	printf("\n输入系统最多容纳作业数量:");
	scanf("%d",&Mutiple); 
	int i;
	printf("\n输入作业数:");
	scanf("%d", &n);
	for (i = 0; i<n; i++)
	{
		p = getpch(JCB);
		printf("\n输入作业名:");
		scanf("%s", p->name);
		getchar();
		p->reachtime = i;
		printf("作业默认到达时间:%d", i);
		printf("\n输入作业要运行的时间:");
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
	if(j == ready)//先将要运行的作业从队列中分离出来
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

	printf("作业运行情况 | \n作业名 | \t开始时间 | \t需要时间 | \t已经运行时间\t\n"); 
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
			printf("作业[ %s ]已经完成\n",r->name);
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
    //暂停以更好观察
    JCB *temp;
    // 将作业按照HRN加入队列
      for(i=0; i<n; i++)
    {
        ptr = temp=ready;
        iden=1;
        //找到响应比最大的可运行的作业
        do
        {
            if(ptr->state=='W'&&ptr->reachtime<=times && runLength()<Mutiple)
            {
				ptr->Rp =(double)(times - ptr->reachtime + ptr->needtime)/ptr->needtime;
            	
                if(iden)
                {
                    temp=ptr;
                    iden=0;//找到后置0
                }
                else if(ptr->Rp > temp->Rp)
                  temp=ptr;
            }
            ptr=ptr -> next;
        }
        while (ptr != NULL);//利用链表遍历找到队列中非空队首

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
        	printf("作业[ %s ]调入内存\n",temp->name);
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
