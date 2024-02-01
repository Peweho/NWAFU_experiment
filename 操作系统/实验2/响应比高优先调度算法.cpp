#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define getpch(type) (type*)malloc(sizeof(type))
int n;//��ҵ��//the num of jobs
float T1 = 0, T2 = 0;
int times = 0; //��¼ʱ��
void swap ( int *a, int *b );
//��ҵ���ƿ�
struct jcb
{
    char name[10]; //�û�����
    int reachtime;//��ҵ�ִ�ʱ��
    int starttime;//��ҵ��ʼʱ��
    int needtime;//��ҵ��������ʱ��
    int endtime;//��ҵ���ʱ��
    float cycletime;//��ҵ��תʱ��
    float cltime;//��Ȩ��תʱ��
    char state;//��ҵ״̬
    struct jcb *next;//�ṹ��ָ��
    double Rp;//��Ӧ�� = ��Ӧʱ��/Ҫ�����ʱ��
}*ready = NULL, *p, *q;
typedef struct jcb JCB;

void inital() //������ҵ���ƿ����,�Ƚ����ų������ȷ���(FCFS)��ģʽ����
{
    int i;
    printf ( "\n������ҵ��:" );
    scanf ( "%d", &n );
    for ( i = 0; i < n; i++ )
    {
        p = getpch ( JCB );
        printf ( "\n������ҵ��:" );
        scanf ( "%s", p->name );
        getchar();
        p->reachtime = i;
        printf ( "��ҵĬ�ϵ���ʱ��:%d", i );
        printf ( "\n������ҵҪ���е�ʱ��:" );
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

void disp ( JCB*q, int m ) //��ʾ��ҵ���к����תʱ�估��Ȩ��תʱ���
{
    printf ( "\n��ҵ%s�������У����������������\n", q->name );
    printf ( "��ʼ����ʱ�̣�%d\n", q->starttime );
    printf ( "���ʱ�̣�%d\n", q->endtime );
    printf ( "��תʱ�䣺%f\n", q->cycletime );
    printf ( "��Ȩ��תʱ�䣺%f\n", q->cltime );
    getchar();
}

void running ( JCB *p, int m ) //������ҵ
{
    if ( p == ready )   //�Ƚ�Ҫ���е���ҵ�Ӷ����з������
    {
        ready = p->next;
        p->next = NULL;
    }else{
        q = ready;
        while ( q->next != p )  q = q->next;
        q->next = p->next;
    }
    p->starttime = times;//������ҵ���к�����ʱ��,��תʱ��ȵ�
    p->state = 'R';
    p->endtime = p->starttime + p->needtime;
    p->cycletime = ( float ) ( p->endtime - p->reachtime );
    p->cltime = ( float ) ( p->cycletime / p->needtime );
    T1 += p->cycletime;
    T2 += p->cltime;
    disp ( p, m ); //����disp()����,��ʾ��ҵ�������
    times += p->needtime;
    p->state = 'F';
    printf ( "\n%s has been finished!\n", p->name );
    free ( p ); //�ͷ����к����ҵ
    getchar();
}

void final() //����ӡ��ҵ��ƽ����תʱ��,ƽ����Ȩ��תʱ��
{
    float s, t;
    t = T1 / n;
    s = T2 / n;
    getchar();
    printf ( "\n\n��ҵ�Ѿ�ȫ�����!\n" );
    printf ( "\n%d����ҵ��ƽ����תʱ���ǣ�%f", n, t );
    printf ( "\n%d����ҵ��ƽ����Ȩ��תʱ����%f��\n\n\n", n, s );
}

void sjf ( int m ) //�����ҵ�����㷨(Short Job First,SJF)
{
    JCB *min;//������ҵ���ƿ�
    int i, iden;
    //��ͣ�Ը��ù۲�
    system ( "cls" );
    inital();// ����ҵ����sjf�������
    for ( i = 0; i < n; i++ ){
        p = min = ready;//�ֱ��ʼ��p��min��ready
        iden = 1;
        do{
            if ( p->state == 'W' && p->reachtime <= times ) //�ж��Ƿ����㵽��ʱ�������ʱ�����ҵ״̬Ϊ��w��
                if ( iden ){
                    min = p;
                    iden = 0;
                }
                else if ( p->needtime < min->needtime )
                    min = p;
            p = p->next;
            // 1 ���������ģ��ո���дһ��ָ��
        }
        while ( p != NULL );
        
        if ( iden ) //���û��������������ҵ����ʱ������
        {
            i--;
            times++;
            if ( times > 100 )
            {
                printf ( "\nruntime is too long �� error" );
                getchar();
            }
        }
        else{
            running ( min, m );//����������ж����е���ҵ
        }
    }
    final();//����ϵͳʱ��
}

void fcfs ( int m )  //�����ȷ����㷨
{

    int i, iden;
    system ( "cls" );
    inital();// ����ҵ����FCFS�������
    for ( i = 0; i < n; i++ ){
        p = ready;
        iden = 1;
        do{
            if ( p->state == 'W' && p->reachtime <= times )
                iden = 0;//�ҵ�����0
            if ( iden )
                p = p->next;
        }
        while ( p != NULL && iden );//������������ҵ������зǿն���

        if ( iden ) //���û��������������ҵ��ȴ�
        {
            i--;
            printf ( "\nû������Ҫ��Ľ���,��ȴ�" );
            times++;
            if ( times > 100 )
            {
                printf ( "\nʱ�����" );
                getchar();
            }
        }
        else//�������������ҵ
        {
            running ( p, m );
        }
    }
    final();//����ϵͳʱ��
}
//����fcfs�㷨д����Ӧ�ȸ��������㷨
void HRN ( int m )
{
    int i,iden;
    //��ͣ�Ը��ù۲�
    JCB *temp;
    system ( "cls" );
    inital();// ����ҵ����HRN�������
      for(i=0; i<n; i++)
    {
        p=temp=ready;
        iden=1;
        //�ҵ���Ӧ�����Ŀ����е���ҵ
        do
        {
            if(p->state=='W'&&p->reachtime<=times)
            {
            	p->Rp =(double)(times - p->reachtime + p->needtime)/p->needtime;
                if(iden)
                {
                    temp=p;
                    iden=0;//�ҵ�����0
                }
                else if(p->Rp > temp->Rp)
                  temp=p;
            }
            p=p -> next;
        }
        while (p != NULL);//������������ҵ������зǿն���

        if(iden)
        {
            i--;
            times++;
            if (times>100)
            {
                printf("\nʱ�����");
                getchar();
            }
        }
        else
        {
            running(temp, m);
        }
    }
    final();//����ϵͳʱ��
}

void menu()
{
	int m;
    system ( "cls" );
    printf ( "\n\n\t\t*********************************************\t\t\n" );
    printf ( "\t\t\t\t��ҵ������ʾ\n" );
    printf ( "\t\t*********************************************\t\t\n" );
    printf ( "\n\n\n\t\t\t1.�����ȷ����㷨." );
    printf ( "\n\t\t\t2.�����ҵ�����㷨." );
    printf ( "\n\t\t\t3.����Ӧ�����ȵ����㷨." );
    printf ( "\n\t\t\t0.�˳�����." );
    printf ( "\n\n\t\t\t\tѡ����Ҫ����:" );
    scanf ( "%d", &m );//�˵�
    switch ( m )
    {
    case 1:
        fcfs ( m );//����FCFS�㷨������ҵ
        getchar();
        system ( "cls" );
        break;
    case 2:
        sjf ( m );//����SJF�㷨������ҵ
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
