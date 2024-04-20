package third;

import org.junit.jupiter.api.Assertions;
import org.junit.Test;

public class HolidaySkedTest {
    @Test
    public void isHoliday() {
        HolidaySked holidaySked = new HolidaySked();
        Assertions.assertTrue(holidaySked.isHoliday(165));
    }
}