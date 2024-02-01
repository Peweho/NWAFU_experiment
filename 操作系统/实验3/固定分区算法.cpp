#include<stdio.h>
#include <dos.h>
#include<stdlib.h>
#include<conio.h>
//#include<iostream.h>
#define n 10  /*假定系统允许的最大作业数为n，假定模拟实验中n值为10*/
#define m 10  /*假定系统允许的空闲区表最大为m，假定模拟实验中m值为10*/
#define minisize 100 /*空闲分区被分配时，如果分配后剩余的空间小于minisize，则将该空闲分区全部分配，若大于minisize，则切割分配*/

struct
{
    float address;  /*已分配分区起始地址*/
    float length;  /*已分配分区长度，单位为字节*/
    int flag;   /*已分配区表登记栏标志，用"0"表示空栏目*/
} used_table[n]; /*已分配区表*/

struct
{
    float address;  /*空闲区起始地址*/
    float length;  /*空闲区长度，单位为字节*/
    int flag;   /*空闲区表登记栏标志，用"0"表示空栏目，用"1"表示未分配*/
} free_table[m]; /*空闲区表*/

void allocate(char J,float xk) /*给J作业，采用最佳分配算法分配xk大小的空间*/
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
			printf("作业已满");
			return;
		}
	}
	printf("无可用空闲区");
	return;
}/*主存分配函数结束*/

void reclaim(char J)
/*回收作业名为J的作业所占主存空间*/
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
	printf("没有%c作业",J);

}/*主存回收函数结束*/

int main( )
{
    int i,a;
    float xk;
    char J;
    /*空闲分区表初始化：*/
    int size = 10240;

    for(i=0; i<m; i++)
    {
    	free_table[i].length= 10240/n;
    	free_table[i].address = size + i*free_table[i].length;
    	free_table[i].flag=0;  /*其余空闲分区表项未被使用*/
	}
        
    /*已分配表初始化：*/
    for(i=0; i<n; i++)
        used_table[i].flag=0;  /*初始时均未分配*/
    while(1)
    {
        printf("*********************************************");
        printf("\n\t\t选择功能项\n");
        printf("*********************************************");
        printf("\n\n\t\t0-退出");
        printf("\n\t\t1-分配主存");
        printf("\n\t\t2-回收主存");
        printf("\n\t\t3-显示主存");
        printf("\n\n\t\t\t\t选择功能项(0~3) :\n");
        scanf("%d",&a);
        switch(a)
        {
        case 0:
            exit(0);  /*a=0程序结束*/
        case 1:     /*a=1分配主存空间*/
            printf("输入作业名J和作业所需长度xk: \n");
            scanf("%*c%c%f",&J,&xk);
            allocate(J,xk);  /*分配主存空间*/
            break;
        case 2:     /*a=2回收主存空间*/
            printf("输入要回收分区的作业名");
            scanf("%*c%c",&J);
            reclaim(J);  /*回收主存空间*/
            break;
        case 3:     /*a=3显示主存情况*/
            /*输出空闲区表和已分配表的内容*/
            printf("输出空闲区表：\n起始地址 分区长度 标志\n");
            for(i=0; i<m; i++)
                printf("%6.0f%9.0f%6d\n",free_table[i].address,free_table[i].length, free_table[i].flag);
            printf(" 按任意键,输出已分配区表\n");
            getch();
            printf(" 输出已分配区表：\n起始地址 分区长度 标志\n");
            for(i=0; i<n; i++)
                if(used_table[i].flag!=0)
                    printf("%6.0f%9.0f%6c\n",used_table[i].address,used_table[i].length, used_table[i].flag);
                else
                    printf("%6.0f%9.0f%6d\n",used_table[i].address,used_table[i].length, used_table[i].flag);
            break;
        default:
            printf("没有该选项\n");
        }/*case*/
    }/*while*/
    return 1;
}
