package fifth.triangle;

public class Triangle {
    public String judge(int a,int b,int c) {
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
