#include<stdio.h>
#include <dos.h>
#include<stdlib.h>
#include<conio.h>
//#include<iostream.h>
#define n 10  /*�ٶ�ϵͳ����������ҵ��Ϊn���ٶ�ģ��ʵ����nֵΪ10*/
#define m 10  /*�ٶ�ϵͳ����Ŀ����������Ϊm���ٶ�ģ��ʵ����mֵΪ10*/
#define minisize 100 /*���з���������ʱ����������ʣ��Ŀռ�С��minisize���򽫸ÿ��з���ȫ�����䣬������minisize�����и����*/
struct
{
    float address;  /*�ѷ��������ʼ��ַ*/
    float length;  /*�ѷ���������ȣ���λΪ�ֽ�*/
    int flag;   /*�ѷ�������Ǽ�����־����"0"��ʾ����Ŀ*/
} used_table[n]; /*�ѷ�������*/

struct
{
    float address;  /*��������ʼ��ַ*/
    float length;  /*���������ȣ���λΪ�ֽ�*/
    int flag;   /*��������Ǽ�����־����"0"��ʾ����Ŀ����"1"��ʾδ����*/
} free_table[m]; /*��������*/

void allocate(char J,float xk) /*��J��ҵ��������ѷ����㷨����xk��С�Ŀռ�*/
{
    int i,k;
    float ad;
    k=-1;
    for(i=0; i<m; i++) /*1�������з������ҵ����ÿ�����                               */
        if(free_table[i].length >= xk && free_table[i].flag == 1)
        {
        	k = i; 
        	break;
		}
		
    if(k==-1)/*δ�ҵ����ÿ�����������*/
    {
        printf("�޿��ÿ�����\n");
        return;
    }
    /*�ҵ����ÿ���������ʼ���䣺����������С��Ҫ�����Ŀռ��С��minisize��С���������ȫ�����䣻����������С��Ҫ�����Ŀռ�����minisize��С����ӿ���������һ���ַ���*/
    if(free_table[k].length-xk <= minisize)
    {
        free_table[k].flag=0;
        ad=free_table[k].address;
        xk=free_table[k].length;
    }
    else
    {
        free_table[k].length=free_table[k].length-xk;
        ad=free_table[k].address+free_table[k].length;
    }

    /*�޸��ѷ�������*/
    i=0;
    while(used_table[i].flag != 0 && i<n) /*2�����ѷ��������ҵ��ձ�*/
        i++;
    if(i>=n) /*�ޱ�Ŀ����д�ѷ������*/
    {
        printf("�ޱ�Ŀ��д�ѷַ���������\n");
        /*������������*/
        if(free_table[k].flag==0)
            /*ǰ���ҵ������������з���*/
            free_table[k].flag=1;
        else
        {
            /*ǰ���ҵ�����ĳ�����з�����һ����*/
            free_table[k].length=free_table[k].length+xk;
            return;
        }
    }
    else
    {
        /*�޸��ѷ����*/
        used_table[i].address=ad;
        used_table[i].length=xk;
        used_table[i].flag=J;
    }
    return;

}/*������亯������*/

void reclaim(char J)
/*������ҵ��ΪJ����ҵ��ռ����ռ�*/
{
    int i,k,j,s,t;
    float S,L;
    /*Ѱ���ѷ�����ж�Ӧ�Ǽ���*/
    s=0;
    while((used_table[s].flag!=J||used_table[s].flag==0)&&s<n)
        s++;
    if(s>=n)/*���ѷ�������Ҳ�������ΪJ����ҵ*/
    {
        printf("�Ҳ�������ҵ\n");
        return;
    }
    /*�޸��ѷ����*/
    used_table[s].flag=0;
    /*ȡ�ù黹��������ʼ��ַS�ͳ���L*/
    S=used_table[s].address;
    L=used_table[s].length;
    j=-1;
    k=-1;
    i=0;
    /*Ѱ�һ��շ����Ŀ��������ڣ����ڱ�Ŀk�����ڱ�Ŀj*/
    while(i<m&&(j==-1||k==-1))
    {
        if(free_table[i].flag==1)
        {
            if(free_table[i].address+free_table[i].length==S)k=i;/*�ҵ�����*/
            if(free_table[i].address==S+L)j=i;/*�ҵ�����*/
        }
        i++;
    }
    if(k!=-1)
        if(j!=-1)
            /* 3                                                 */
        {
            free_table[k].length=free_table[j].length+free_table[k].length+L;
            free_table[j].flag=0;
        }
        else
            /*���ڿ����������ڷǿ������������ںϲ�*/
            free_table[k].length=free_table[k].length+L;
    else if(j!=-1)
        /*���ڷǿ�����������Ϊ�������������ںϲ�*/
    {
        free_table[j].address=S;
        free_table[j].length=free_table[j].length+L;
    }
    else
        /*�����ھ�Ϊ�ǿ���������������ֱ������*/
    {
        /*�ڿ���������Ѱ�ҿ���Ŀ*/
        t=0;
        while(free_table[t].flag==1&&t<m)
            t++;
        if(t>=m)/*����������,���տռ�ʧ��,���ѷ����ԭ*/
        {
            printf("������б�û�пռ�,���տռ�ʧ��\n");
            used_table[s].flag=J;
            return;
        }
        free_table[t].address=S;
        free_table[t].length=L;
        free_table[t].flag=1;
    }
    return;
}/*������պ�������*/

int main( )
{
    int i,a;
    float xk;
    char J;
    /*���з������ʼ����*/
    free_table[0].address=10240; /*��ʼ��ַ�ٶ�Ϊ10240*/
    free_table[0].length=10240;  /*���ȼٶ�Ϊ10240����10k*/
    free_table[0].flag=1;   /*��ʼ������Ϊһ�����������*/

    for(i=1; i<m; i++)
        free_table[i].flag=0;  /*������з�������δ��ʹ��*/
    /*�ѷ�����ʼ����*/
    for(i=0; i<n; i++)
        used_table[i].flag=0;  /*��ʼʱ��δ����*/
    while(1)
    {
        printf("*********************************************");
        printf("\n\t\tѡ������\n");
        printf("*********************************************");
        printf("\n\n\t\t0-�˳�");
        printf("\n\t\t1-��������");
        printf("\n\t\t2-��������");
        printf("\n\t\t3-��ʾ����");
        printf("\n\n\t\t\t\tѡ������(0~3) :\n");
        scanf("%d",&a);
        switch(a)
        {
        case 0:
            exit(0);  /*a=0�������*/
        case 1:     /*a=1��������ռ�*/
            printf("������ҵ��J����ҵ���賤��xk: \n");
            scanf("%*c%c%f",&J,&xk);
            allocate(J,xk);  /*��������ռ�*/
            break;
        case 2:     /*a=2��������ռ�*/
            printf("����Ҫ���շ�������ҵ��");
            scanf("%*c%c",&J);
            reclaim(J);  /*��������ռ�*/
            break;
        case 3:     /*a=3��ʾ�������*/
            /*�������������ѷ���������*/
            printf("�����������\n��ʼ��ַ �������� ��־\n");
            for(i=0; i<m; i++)
                printf("%6.0f%9.0f%6d\n",free_table[i].address,free_table[i].length, free_table[i].flag);
            printf(" �������,����ѷ�������\n");
            getch();
            printf(" ����ѷ�������\n��ʼ��ַ �������� ��־\n");
            for(i=0; i<n; i++)
                if(used_table[i].flag!=0)
                    printf("%6.0f%9.0f%6c\n",used_table[i].address,used_table[i].length, used_table[i].flag);
                else
                    printf("%6.0f%9.0f%6d\n",used_table[i].address,used_table[i].length, used_table[i].flag);
            break;
        default:
            printf("û�и�ѡ��\n");
        }/*case*/
    }/*while*/
    return 1;
}
