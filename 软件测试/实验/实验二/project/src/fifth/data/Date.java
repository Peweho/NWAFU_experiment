package fifth.data;
import fourth.P4;

import static fifth.data.Const.*;
public class Date {
    /** ��ʾ�����е����.
     */
    private int year;

    /** ��ʾ�����е��·�.
     */
    private int month;
    /** ��ʾ�����е���.
     */
    private int day;
    /** �õ�����������.
     * @return ���Ϊ�ַ���
     */
    public String gapNext( int y,  int m,int d) {
        year = y;
        month = m;
        day = d;
        y = year;
        m = month;
        d = day + 2;
        // 1������Ƕ��£��ж�����
        if (this.month == 2) {
            if (isLeap()) {
                if (d > FEBRARY_LEAP_DAYS) {
                    m++;
                    d %= FEBRARY_LEAP_DAYS;
                }
            } else {
                if (d > FEBRARY_DAYS) {
                    m++;
                    d %= FEBRARY_DAYS;
                }
            }
        } else {
            int totalDay = isMonth() ? LARGE_DAYS : SMALL_DAYS;
            if (d > totalDay) {
                m += 1;
                d %= totalDay;
                if (m > MONTHS) {
                    m %= MONTHS;
                    y++;
                }
            }
        }
        return y + "-" + m + "-" + d;
    }

    /** �ж��Ƿ�������.
     * @return trueΪ����
     */
    public boolean isLeap() {
        if (this.year % LEAP_FOUR_HUNDRED == 0 || this.year % LEAP_HUNDRED != 0 && this.year % LEAP_FOUR == 0) {
            return true;
        }
        return false;
    }

    /** �жϴ�С��.
     * @return ����True ���£�False С��
     */
    public boolean isMonth() {
        if (this.month == APR || this.month == JUN || this.month == SEP || this.month == NOV) {
            return false;
        }
        return true;
    }

}
