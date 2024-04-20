package fourth;

public class P4 {
    public int DoWork(int x, int y, int z)
    {
        int k=0, j=0;
        if( x > 3 && z < 10 )
        {
            k=x*y-1;
            j = (int) Math.sqrt(k);
        }

        if( x == 4 || y > 5 )
        {
            j = x*y + 10;
        }
        j = j % 3;

        return j;
    }
}
