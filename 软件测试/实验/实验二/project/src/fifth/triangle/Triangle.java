package fifth.triangle;

public class Triangle {
    public String judge(int a,int b,int c) {
        if (a + b <= c || a + c <= b || b + c <= a) {
            return "无法构成三角形";
        }
        if (a == b && c == b) {
            return "等边三角形";
        }
        if (a == b || c == b || a == c) {
            return "等腰三角形";
        }
        return "不等三角形";
    }
}
