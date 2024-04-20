package fifth.data;
import fourth.P4;

import static fifth.data.Const.*;
public class Date {
    /** 表示日期中的年份.
     */
    private int year;

    /** 表示日期中的月份.
     */
    private int month;
    /** 表示日期中的日.
     */
    private int day;
    /** 得到两天后的日期.
     * @return 结果为字符串
     */
    public String gapNext( int y,  int m,int d) {
        year = y;
        month = m;
        day = d;
        y = year;
        m = month;
        d = day + 2;
        // 1、如果是二月，判断闰年
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

    /** 判断是否是闰年.
     * @return true为闰年
     */
    public boolean isLeap() {
        if (this.year % LEAP_FOUR_HUNDRED == 0 || this.year % LEAP_HUNDRED != 0 && this.year % LEAP_FOUR == 0) {
            return true;
        }
        return false;
    }

    /** 判断大小月.
     * @return 返回True 大月，False 小月
     */
    public boolean isMonth() {
        if (this.month == APR || this.month == JUN || this.month == SEP || this.month == NOV) {
            return false;
        }
        return true;
    }

}
