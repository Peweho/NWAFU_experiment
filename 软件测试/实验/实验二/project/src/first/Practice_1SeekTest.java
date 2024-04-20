package first;

import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;
import java.util.Arrays;
import java.util.Collection;

@RunWith(Parameterized.class)
public class Practice_1SeekTest {
    private Practice_1 p = new Practice_1();
    private int[] nums;
    private int target;
    private boolean res;

    @Parameters
    public static Collection<Object[]> data(){
        Object[][] object={{new int[]{1,4,5,8,3},5,true},{new int[]{29,2,1,58},4,false}};
        return Arrays.asList(object);
    }

    public Practice_1SeekTest(int[] nums,int target,boolean res) {
        this.nums = nums;
        this.res = res;
        this.target = target;
    }

    @Test
    public void seek_1() {
        Assert.assertEquals(res, p.seek_1(nums, target));
    }
}