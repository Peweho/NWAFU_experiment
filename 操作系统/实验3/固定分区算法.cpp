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
	for(int i=0; i<m; i++)
    {
    	if(free_table[i].flag == 0 && free_table[i].length >= xk)
    	{
    		free_table[i].flag = 1;
    		for(int j=0; j<n; j++)
    		{
    			if(used_table[j].flag == 0)
    			{
    				used_table[j].address = free_table[i].address;
    				used_table[j].length = xk;
    				used_table[j].flag = J;
    				return;
				}
			}
			printf("��ҵ����");
			return;
		}
	}
	printf("�޿��ÿ�����");
	return;
}/*������亯������*/

void reclaim(char J)
/*������ҵ��ΪJ����ҵ��ռ����ռ�*/
{
	for(int j=0; j<n; j++)
	{
		if(used_table[j].flag == J)
		{
			for(int i=0; i<m; i++)
			{
				if(free_table[i].address == used_table[j].address)
				{
					free_table[i].flag = 0;
					break;
				}
			}
			used_table[j].flag = 0;
			used_table[j].address = 0;
			used_table[j].length = 0;
			return;
		} 
	}
	printf("û��%c��ҵ",J);

}/*������պ�������*/

int main( )
{
    int i,a;
    float xk;
    char J;
    /*���з������ʼ����*/
    int size = 10240;

    for(i=0; i<m; i++)
    {
    	free_table[i].length= 10240/n;
    	free_table[i].address = size + i*free_table[i].length;
    	free_table[i].flag=0;  /*������з�������δ��ʹ��*/
	}
        
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
