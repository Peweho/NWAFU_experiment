#include <stdio.h>
#include <stdlib.h>
void quicksort(int* a,int start,int end)
{
        int biao=start;
        int i = start,j = end;
        while(i<j)
        {
                while(i < j)
                {
                        if(a[j] < a[biao])
                        {
                                int t = a[j];
                                a[j] = a[biao];
                                a[biao] = t;
                                biao = j;
                                --j;
                                break;
                        }
                        else
                        {
                                --j;
                        }
                }
                while(i<j)
                {
                        if(a[i] > a[biao])
                        {
                                int t = a[i];
                                a[i] = a[biao];
                                a[biao] = t;
                                biao = i;
                                ++i;

                                break;
                        }
                        else
                        {
                                ++i;
                        }
                }

                if(i==j)
                {
                        if(i<biao)
                                quicksort(a,i,biao-1);
                        if(biao<j)
                                quicksort(a,biao+1,j);
                }
        }
}
int main()
{
    int a[10]={2,4,5,7,6,5,34,9,2,1};
    quicksort(a,0,9);
    for(int i=0;i<10;++i)
    {
        printf("%d ",a[i]);
    }
    return 0;
}
