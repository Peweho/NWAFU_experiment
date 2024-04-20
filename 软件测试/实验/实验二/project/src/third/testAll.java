package third;

import first.Practice_1Test;
import org.junit.runner.RunWith;
import org.junit.runners.Suite;
import second.Practice_2Test;

@RunWith(Suite.class)
@Suite.SuiteClasses({Practice_1Test.class, Practice_2Test.class, HolidaySkedTest.class})
public class testAll {
}
