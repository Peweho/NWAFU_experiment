public class Triangle {
    /** 三角形一边.
     */
    private int a;
    /** 三角形一边.
     */
    private int b;
    /** 三角形一边.
     */
    private int c;

    /** 类构造方法.
     * @param aa 三角形一边
     * @param bb 三角形一边
     * @param cc 三角形一边
     */
    public Triangle(final int aa, final int bb, final int cc) {
        this.a = aa;
        this.b = bb;
        this.c = cc;
    }

    /** 判断方法.
     * 先判断是否是三角形
     * 在判断是否是等边和等腰三角形
     * 否则为不等三角形
     * @return 返回结果字符串
     */
    public String judge() {
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
