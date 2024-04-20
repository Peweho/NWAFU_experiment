package fifth.data;

import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.awt.*;
import java.util.Arrays;
import java.util.Collection;

import static org.junit.Assert.*;

@RunWith(Parameterized.class)
public class DateTest {
    private Date d = new fifth.data.Date();
    private int year;

    /** 表示日期中的月份.
     */
    private int month;

    /** 表示日期中的日.
     */
    private int day;
    private String res ;
    @Parameterized.Parameters
    public static Collection<Object[]> data(){
        Object[][] object={{2000,2,20,"2000-2-22"},
                            {2000,2,28,"2000-3-1"},
                            {2001,12,30,"2002-1-1"},
                            {2001,12,28,"2001-12-30"},
                            {2001,2,26,"2001-2-28"},
                            {2001,2,27,"2001-3-1"},
                            {2001,11,30,"2001-12-2"}};
        return Arrays.asList(object);
    }

    public DateTest(int y,int m,int d,String res) {
        year = y;
        month = m;
        day = d;
        this.res = res;
    }

    @Test
    public void gapNext() {
        Assert.assertEquals(res,d.gapNext(year,month,day));
    }
}