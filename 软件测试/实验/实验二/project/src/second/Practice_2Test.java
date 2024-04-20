package second;

import org.junit.jupiter.api.Assertions;
import org.junit.Before;
import org.junit.Test;

public class Practice_2Test {
    private int num;
    private Practice_2 obj;

    @Before
    public void setUp() {
        num = 34;
        obj = new Practice_2();
    }

    @Test
    public void isPrime() {
        Assertions.assertFalse(obj.isPrime(num));
    }

}