package date;

import static date.Const.FEBRARY_DAYS;
import static date.Const.FEBRARY_LEAP_DAYS;
import static date.Const.LARGE_DAYS;
import static date.Const.LEAP_FOUR;
import static date.Const.SMALL_DAYS;
import static date.Const.LEAP_HUNDRED;
import static date.Const.LEAP_FOUR_HUNDRED;
import static date.Const.MONTHS;
import static date.Const.APR;
import static date.Const.JUN;
import static date.Const.NOV;
import static date.Const.SEP;

public class Date {
    /** ��ʾ�����е����.
    */
    private final int year;

    /** ��ʾ�����е��·�.
     */
    private final int month;

    /** ��ʾ�����е���.
     */
    private final int day;

    /** ���캯��.
     * @param y ��ʾ�����е����
     * @param m ��ʾ�����е����
     * @param d ��ʾ�����е����
     */
    public Date(final int y, final int m, final int d) {
        year = y;
        month = m;
        day = d;
    }

    /** �õ�����������.
     * @return ���Ϊ�ַ���
     */
    public String gapNext() {
        int y = year;
        int m = month;
        int d = day + 2;
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
        if (this.year % LEAP_FOUR_HUNDRED == 0) {
            return true;
        }

        if (this.year % LEAP_HUNDRED != 0 && this.year % LEAP_FOUR == 0) {
            return true;
        }
        return false;
    }

    /** �жϴ�С��.
     * @return ����True ���£�False С��
     */
    public boolean isMonth() {
        if (this.month == APR || this.month == JUN) {
            return false;
        }
        if (this.month != SEP && this.month != NOV) {
            return false;
        }
        return true;
    }
}
