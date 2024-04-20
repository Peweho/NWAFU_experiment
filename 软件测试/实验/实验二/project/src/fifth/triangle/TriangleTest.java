package fifth.triangle;

import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.util.Arrays;
import java.util.Collection;

@RunWith(Parameterized.class)
public class TriangleTest {
    private int a;
    private int b;
    private int c;
    private String res;
    private Triangle t = new Triangle();

    @Parameterized.Parameters
    public static Collection<Object[]> data(){
        Object[][] object={{4,4,8,"无法构成三角形"},{4,4,4,"等边三角形"},{10,3,10,"等腰三角形"},{4,6,8,"不等三角形"}};
        return Arrays.asList(object);
    }

    public TriangleTest(int x,int y,int z,String res) {
        this.a = x;
        this.b = y;
        this.c = z;
        this.res = res;
    }

    @Test
    public void judge() {
        Assert.assertEquals(res,t.judge(a,b,c));
    }
}