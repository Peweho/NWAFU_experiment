package third;

import org.junit.Test;
import org.junit.jupiter.api.Assertions;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.util.Arrays;
import java.util.Collection;

import static org.junit.Assert.*;

@RunWith(Parameterized.class)
public class HolidaySkedArgsTest {
    private int hoildays;
    private boolean res;
    private HolidaySked h = new HolidaySked();

    @Parameterized.Parameters
    public static Collection<Object[]> data(){
        Object[][] object={{30,false},{29,false},{43,true}};
        return Arrays.asList(object);
    }

    public HolidaySkedArgsTest(int hoildays,boolean res) {
        this.hoildays = hoildays;
        this.res = res;
    }

    @Test
    public void isHoliday() {
        Assertions.assertEquals(res,h.isHoliday(hoildays));
    }
}