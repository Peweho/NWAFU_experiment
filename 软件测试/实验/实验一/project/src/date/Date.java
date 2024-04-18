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
    /** 表示日期中的年份.
    */
    private final int year;

    /** 表示日期中的月份.
     */
    private final int month;

    /** 表示日期中的日.
     */
    private final int day;

    /** 构造函数.
     * @param y 表示日期中的年份
     * @param m 表示日期中的年份
     * @param d 表示日期中的年份
     */
    public Date(final int y, final int m, final int d) {
        year = y;
        month = m;
        day = d;
    }

    /** 得到两天后的日期.
     * @return 结果为字符串
     */
    public String gapNext() {
        int y = year;
        int m = month;
        int d = day + 2;
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
        if (this.year % LEAP_FOUR_HUNDRED == 0) {
            return true;
        }

        if (this.year % LEAP_HUNDRED != 0 && this.year % LEAP_FOUR == 0) {
            return true;
        }
        return false;
    }

    /** 判断大小月.
     * @return 返回True 大月，False 小月
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
