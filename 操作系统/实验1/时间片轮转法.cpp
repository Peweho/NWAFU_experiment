#include "stdio.h"
#include <stdlib.h>
#include <conio.h>
#define getpch(type) (type *)malloc(sizeof(type))

struct pcb
{ /* ������̿��ƿ�PCB */
    char name[10];
    char state;
    int super;
    int ntime;
    int rtime;
    struct pcb *link;
} *ready = NULL, *p;
typedef struct pcb PCB;

void sort() /* �����Խ��̽������ȼ����к���*/
{
    PCB *first, *second;
    int insert = 0;
    if ((ready == NULL) || ((p->super) > (ready->super))) /*���ȼ������,�������*/
    {
        p->link = ready;
        ready = p;
    }
    else /* ���̱Ƚ����ȼ�,�����ʵ���λ����*/
    {
        first = ready;
        second = first->link;
        while (second != NULL)
        {
            if ((p->super) > (second->super)) /*��������̱ȵ�ǰ������������,*/
            {                                 /*���뵽��ǰ����ǰ��*/
                p->link = second;
                first->link = p;
                second = NULL;
                insert = 1;
            }
            else /* ����������������,����뵽��β*/
            {
                first = first->link;
                second = second->link;
            }
        }
        if (insert == 0)
            first->link = p;
    }
}

void clrscr()
{
    system("cls");
}

void input() /* �������̿��ƿ麯��*/
{
    int i, num;
    clrscr(); /*����*/
    printf("\n ��������̸���?");
    scanf("%d", &num);
    for (i = 0; i < num; i++)
    {
        printf("\n ���̺�No.%d:\n", i + 1);
        p = getpch(PCB);
        printf("\n ���������:");
        scanf("%s", p->name);
        printf("\n �������������:");
        scanf("%d", &p->super);
        printf("\n �����������ʱ��:");
        scanf("%d", &p->ntime);
        printf("\n");
        p->rtime = 0;
        p->state = 'w';
        p->link = NULL;
        sort(); /* ����sort����*/
    }
}

int space()
{
    int l = 0;
    PCB *pr = ready;
    while (pr != NULL)
    {
        l++;
        pr = pr->link;
    }
    return (l);
}

void disp(PCB *pr) /*����������ʾ����,������ʾ��ǰ����*/
{
    printf("\n qname \t state \t super \t ndtime \t runtime \n");
    printf("|%s\t", pr->name);
    printf("|%c\t", pr->state);
    printf("|%d\t", pr->super);
    printf("|%d\t", pr->ntime);
    printf("|%d\t", pr->rtime);
    printf("\n");
}

int check(int t) /* �������̲鿴���� */
{
	int b = 0;
    PCB *pr;
    printf("\n **** ��ǰ�������еĽ�����:%s", p->name); /*��ʾ��ǰ���н���*/
    disp(p);
    if(p->ntime - p->rtime <= t)
    	b = 1;
    	
    pr = ready;
    printf("\n ****��ǰ��������״̬Ϊ:\n"); /*��ʾ��������״̬*/
    while (pr != NULL)
    {
        disp(pr);
        pr = pr->link;
    }
    
    return b;
}

void destroy() /*�������̳�������(�������н���,��������)*/
{
    printf("\n ���� [%s] �����.\n", p->name);
    free(p);
}

int runningDisposable()
{
	(p->rtime)++;
	(p->super)--;
    if (p->rtime == p->ntime)
    {
		destroy();
		return 0;
	}
	check(0);
	return 1;
}

void running() /* �������̾�������(��������ʱ�䵽,�þ���״̬*/
{
    (p->rtime)++;
    if (p->rtime == p->ntime)
        destroy(); /* ����destroy����*/
    else
    {
        (p->super)--;
        p->state = 'w';
        sort(); /*����sort����*/
    }
}

int main() /*������*/
{
	int time = 0;
	int bc = 0;
	printf("����ʱ��Ƭ�仯��ֵ,��ҵʣ��ʱ�䲻���ڸ�ֵʱֱ�����\n"); 
	scanf("%d",&time);
    int len, h = 0;
    char ch;
    input();
    len = space();
    while ((len != 0) && (ready != NULL))
    {
        ch = getchar();
        h++;
        printf("\n The execute number:%d \n", h);
        p = ready;
        ready = p->link;
        p->link = NULL;
        p->state = 'R';
        bc = check(time);
        if(bc)
        	while(runningDisposable()){}
        else
        	running();
        printf("\n ����һ������......");
        ch = getchar();
    }
    printf("\n\n �����Ѿ����.\n");
    ch = getchar();

    return 0;
}
