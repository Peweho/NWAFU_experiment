package fifth.sort;

import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.util.Arrays;
import java.util.Collection;

import static org.junit.Assert.*;

@RunWith(Parameterized.class)
public class ChoiceSortTest {
    private ChoiceSort cs = new ChoiceSort();
    private int[] nums;
    private int[] res;

    @Parameterized.Parameters
    public static Collection<Object[]> data(){
        Object[][] object={{new int[]{1,4,72,2},new int[]{72,4,2,1}}};
        return Arrays.asList(object);
    }

    public ChoiceSortTest(int[] nums,int[] res) {
        this.nums = nums;
        this.res = res;
    }

    @Test
    public void sort() {
        Assert.assertArrayEquals(res,cs.sort(nums));
    }
}