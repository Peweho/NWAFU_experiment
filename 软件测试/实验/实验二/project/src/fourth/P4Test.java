package fourth;

import org.junit.Test;
import org.junit.jupiter.api.Assertions;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.util.Arrays;
import java.util.Collection;

import static org.junit.Assert.*;

@RunWith(Parameterized.class)
public class P4Test {
    private P4 p = new P4();
    private int x;
    private int y;
    private int z;
    private int res;

    @Parameterized.Parameters
    public static Collection<Object[]> data(){
        Object[][] object={{4,4,8,2},{4,6,8,1},{2,3,10,0},{4,6,8,1},{2,6,8,1},{2,4,10,0},{4,6,10,1},{4,4,4,2}};
        return Arrays.asList(object);
    }

    public P4Test(int x,int y,int z,int res) {
        this.x = x;
        this.y = y;
        this.z = z;
        this.res = res;
    }

    @Test
    public void doWork() {
        Assertions.assertEquals(res,p.DoWork(x,y,z));
    }
}