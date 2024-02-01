#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define getpch(type) (type*)malloc(sizeof(type))
int n;//作业数//the num of jobs
float T1 = 0, T2 = 0;
int times = 0; //记录时间
void swap ( int *a, int *b );
//作业控制块
struct jcb
{
    char name[10]; //用户名称
    int reachtime;//作业抵达时间
    int starttime;//作业开始时间
    int needtime;//作业运行所需时间
    int endtime;//作业完成时间
    float cycletime;//作业周转时间
    float cltime;//带权周转时间
    char state;//作业状态
    struct jcb *next;//结构体指针
    double Rp;//响应比 = 响应时间/要求服务时间
}*ready = NULL, *p, *q;
typedef struct jcb JCB;

void inital() //建立作业控制块队列,先将其排成先来先服务(FCFS)的模式队列
{
    int i;
    printf ( "\n输入作业数:" );
    scanf ( "%d", &n );
    for ( i = 0; i < n; i++ )
    {
        p = getpch ( JCB );
        printf ( "\n输入作业名:" );
        scanf ( "%s", p->name );
        getchar();
        p->reachtime = i;
        printf ( "作业默认到达时间:%d", i );
        printf ( "\n输入作业要运行的时间:" );
        scanf ( "%d", &p->needtime );
        p->state = 'W';
        p->next = NULL;
        if ( ready == NULL )
            ready = q = p;
        else
        {
            q->next = p;
            q = p;
        }
    }
}

void disp ( JCB*q, int m ) //显示作业运行后的周转时间及带权周转时间等
{
    printf ( "\n作业%s正在运行，估计其运行情况：\n", q->name );
    printf ( "开始运行时刻：%d\n", q->starttime );
    printf ( "完成时刻：%d\n", q->endtime );
    printf ( "周转时间：%f\n", q->cycletime );
    printf ( "带权周转时间：%f\n", q->cltime );
    getchar();
}

void running ( JCB *p, int m ) //运行作业
{
    if ( p == ready )   //先将要运行的作业从队列中分离出来
    {
        ready = p->next;
        p->next = NULL;
    }else{
        q = ready;
        while ( q->next != p )  q = q->next;
        q->next = p->next;
    }
    p->starttime = times;//计算作业运行后的完成时间,周转时间等等
    p->state = 'R';
    p->endtime = p->starttime + p->needtime;
    p->cycletime = ( float ) ( p->endtime - p->reachtime );
    p->cltime = ( float ) ( p->cycletime / p->needtime );
    T1 += p->cycletime;
    T2 += p->cltime;
    disp ( p, m ); //调用disp()函数,显示作业运行情况
    times += p->needtime;
    p->state = 'F';
    printf ( "\n%s has been finished!\n", p->name );
    free ( p ); //释放运行后的作业
    getchar();
}

void final() //最后打印作业的平均周转时间,平均带权周转时间
{
    float s, t;
    t = T1 / n;
    s = T2 / n;
    getchar();
    printf ( "\n\n作业已经全部完成!\n" );
    printf ( "\n%d个作业的平均周转时间是：%f", n, t );
    printf ( "\n%d个作业的平均带权周转时间是%f：\n\n\n", n, s );
}

void sjf ( int m ) //最短作业优先算法(Short Job First,SJF)
{
    JCB *min;//定义作业控制块
    int i, iden;
    //暂停以更好观察
    system ( "cls" );
    inital();// 将作业按照sjf加入队列
    for ( i = 0; i < n; i++ ){
        p = min = ready;//分别初始化p、min、ready
        iden = 1;
        do{
            if ( p->state == 'W' && p->reachtime <= times ) //判断是否满足到达时间等于总时间和作业状态为‘w’
                if ( iden ){
                    min = p;
                    iden = 0;
                }
                else if ( p->needtime < min->needtime )
                    min = p;
            p = p->next;
            // 1 根据上下文，空格处填写一条指令
        }
        while ( p != NULL );
        
        if ( iden ) //如果没有满足条件的作业则总时间增加
        {
            i--;
            times++;
            if ( times > 100 )
            {
                printf ( "\nruntime is too long … error" );
                getchar();
            }
        }
        else{
            running ( min, m );//如果有则运行队列中的作业
        }
    }
    final();//更新系统时间
}

void fcfs ( int m )  //先来先服务算法
{

    int i, iden;
    system ( "cls" );
    inital();// 将作业按照FCFS加入队列
    for ( i = 0; i < n; i++ ){
        p = ready;
        iden = 1;
        do{
            if ( p->state == 'W' && p->reachtime <= times )
                iden = 0;//找到后置0
            if ( iden )
                p = p->next;
        }
        while ( p != NULL && iden );//利用链表遍历找到队列中非空队首

        if ( iden ) //如果没有满足条件的作业则等待
        {
            i--;
            printf ( "\n没有满足要求的进程,需等待" );
            times++;
            if ( times > 100 )
            {
                printf ( "\n时间过长" );
                getchar();
            }
        }
        else//如果有则运行作业
        {
            running ( p, m );
        }
    }
    final();//更新系统时间
}
//参照fcfs算法写出相应比高者优先算法
void HRN ( int m )
{
    int i,iden;
    //暂停以更好观察
    JCB *temp;
    system ( "cls" );
    inital();// 将作业按照HRN加入队列
      for(i=0; i<n; i++)
    {
        p=temp=ready;
        iden=1;
        //找到响应比最大的可运行的作业
        do
        {
            if(p->state=='W'&&p->reachtime<=times)
            {
            	p->Rp =(double)(times - p->reachtime + p->needtime)/p->needtime;
                if(iden)
                {
                    temp=p;
                    iden=0;//找到后置0
                }
                else if(p->Rp > temp->Rp)
                  temp=p;
            }
            p=p -> next;
        }
        while (p != NULL);//利用链表遍历找到队列中非空队首

        if(iden)
        {
            i--;
            times++;
            if (times>100)
            {
                printf("\n时间过长");
                getchar();
            }
        }
        else
        {
            running(temp, m);
        }
    }
    final();//更新系统时间
}

void menu()
{
	int m;
    system ( "cls" );
    printf ( "\n\n\t\t*********************************************\t\t\n" );
    printf ( "\t\t\t\t作业调度演示\n" );
    printf ( "\t\t*********************************************\t\t\n" );
    printf ( "\n\n\n\t\t\t1.先来先服务算法." );
    printf ( "\n\t\t\t2.最短作业优先算法." );
    printf ( "\n\t\t\t3.高响应比优先调度算法." );
    printf ( "\n\t\t\t0.退出程序." );
    printf ( "\n\n\t\t\t\t选择所要操作:" );
    scanf ( "%d", &m );//菜单
    switch ( m )
    {
    case 1:
        fcfs ( m );//利用FCFS算法运行作业
        getchar();
        system ( "cls" );
        break;
    case 2:
        sjf ( m );//利用SJF算法运行作业
        getchar();
        system ( "cls" );
        break;
    case 3:
        HRN(m);
        getchar();
        system("cls");
        break;
    case 0:
        system ( "cls" );
        break;
    }
}

int main()
{
    menu();
    system ( "pause" );
    return 0;
}
