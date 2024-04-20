package first;

import org.junit.jupiter.api.Assertions;
import org.junit.Test;

public class Practice_1Test {
    Practice_1 practice1 = new Practice_1();

    @Test
    public void common_divisor() {
        int a = 144;
        int b = 24;
        Assertions.assertEquals(24, practice1.common_divisor(a,b));
    }

    @Test
    public void common_multiple() {
        int a = 144;
        int b = 24;
        Assertions.assertEquals(144, practice1.common_multiple(a,b));
    }

    @Test
    public void seek_1() {
        int a[] = {1,4,5,3,6,23,67,23,745};
        Assertions.assertEquals(true, practice1.seek_1(a,4));
    }
}