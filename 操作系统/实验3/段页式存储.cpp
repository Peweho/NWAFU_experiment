#include<stdio.h>
#include <dos.h>
#include<stdlib.h>
#include<conio.h>
#define n 25  /*�ٶ��α����Ϊ25����*/
#define p 10  /*ÿ�������10ҳ*/ 
#define m 4  /*�ٶ�һҳ��СΪ4��һ��ָ���СΪ1*/
#define c 1
#define start 1024/*��ʼ��ַ*/


struct paragraph_register
{
	int address;
	int length;
}pr[n];

struct paragraph_table
{
	int number;
	int state;
	int capacity;
	int page_address;
}paragraph_table[n*p];

struct page_table
{
	int number;
	int state;
	char* block;
}page_table[n*p*m];

struct address
{
	int paragraph_number;
	int page_number;
	int page_address;
};

int addInstruct(char* str)
{
	for(int i=0;i<n;++i)
	{
		if(pr[i].length != p)
		{
			for(int j=0;j<p;++j)
			{
				if(paragraph_table[i*p + j].state != 1)
				{
					for(int k=0;k<m;++k)
					{
						if(page_table[i*n*p +k].state != 1)
						{
							page_table[i*n*p +k].state = 1;
							page_table[i*n*p +k].number = k;
							page_table[i*n*p +k].block = str;
						}
					}
				}
			}
		}	
	} 
}

int main()
{
	for(int i=0;i<n;++i)
	{
		pr[i].address = 0;
		pr[i].length = 0;	
	} 
	pr[0].address = start;
	return 0;
}
