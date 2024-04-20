package first;

import org.junit.jupiter.api.Assertions;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import java.util.Arrays;
import java.util.Collection;

@RunWith(Parameterized.class)
public class Practice_1ArgsTest {
    private Practice_1 p = new Practice_1();
    private int a; private int b; private int div_res; private int mul_res;

    @Parameterized.Parameters
    public static Collection<Object[]> data(){
        Object[][] object={{30,4,2,60},{29,2,1,58},{28,2,2,28}};
        return Arrays.asList(object);
    }

    public Practice_1ArgsTest(int a, int b,int divRes,int mul_res) {
        this.a = a;
        this.b = b;
        this.div_res = divRes;
        this.mul_res = mul_res;
    }

    @Test
    public void common_divisor() {
        Assertions.assertEquals(div_res,p.common_divisor(a,b));
    }

    @Test
    public void common_multiple() {
        Assertions.assertEquals(mul_res,p.common_multiple(a,b));
    }
}