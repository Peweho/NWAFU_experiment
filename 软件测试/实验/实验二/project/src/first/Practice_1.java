package first;

public class Practice_1 {
    public int common_divisor(int a,int b){       //�����Լ��
        int c,r;
        if (a<b)
        {	c=a;
            a=b;
            b=c;
        }
        r=1;
        while (r!=0)
        {
            r=a%b;
            a=b;
            b=r;
        }
        return a;
    }
    public int common_multiple(int a,int b){          //��С������
        return a*b/common_divisor(a,b);
    }
    public boolean seek_1(int []a,int x){           //����
        boolean flag=false;
        for(int i=0;i<a.length ;i++){
            if (x==a[i])
                flag=true;
        }
        return flag;
    }

    public static void main(String[] args) {
        int b[]={10,20,15,30,25,40,35,50};
        int x,y,k;
        x=12;y=6;k=40;
        Practice_1 a=new Practice_1();
        System.out.println("���Լ��Ϊ��"+a.common_divisor(x,y));
        System.out.println("��С������Ϊ��"+a.common_multiple(x,y));
        System.out.println("���ҽ��Ϊ��"+a.seek_1(b,k));
    }
}

