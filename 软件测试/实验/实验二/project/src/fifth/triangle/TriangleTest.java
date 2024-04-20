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
        Object[][] object={{4,4,8,"�޷�����������"},{4,4,4,"�ȱ�������"},{10,3,10,"����������"},{4,6,8,"����������"}};
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