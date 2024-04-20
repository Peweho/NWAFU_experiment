package second;
import static java.lang.Math.sqrt;

public class Practice_2 {
    public boolean isPrime(int num) {
        for (int i=2;i<sqrt(num);i++){
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }
}
