public class Triangle {
    /** ������һ��.
     */
    private int a;
    /** ������һ��.
     */
    private int b;
    /** ������һ��.
     */
    private int c;

    /** �๹�췽��.
     * @param aa ������һ��
     * @param bb ������һ��
     * @param cc ������һ��
     */
    public Triangle(final int aa, final int bb, final int cc) {
        this.a = aa;
        this.b = bb;
        this.c = cc;
    }

    /** �жϷ���.
     * ���ж��Ƿ���������
     * ���ж��Ƿ��ǵȱߺ͵���������
     * ����Ϊ����������
     * @return ���ؽ���ַ���
     */
    public String judge() {
        if (a + b <= c || a + c <= b || b + c <= a) {
            return "�޷�����������";
        }
        if (a == b && c == b) {
            return "�ȱ�������";
        }
        if (a == b || c == b || a == c) {
            return "����������";
        }
        return "����������";
    }
}
