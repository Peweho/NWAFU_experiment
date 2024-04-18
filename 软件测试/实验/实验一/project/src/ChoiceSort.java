import java.util.Arrays;
public class ChoiceSort {
    /** arr变量.
     * 定义排序数组
    */
    private int[] arr;
    /** 构造方法.
     * @param nums 我待排序数组
     */
    public ChoiceSort(final int[] nums) {
        arr = nums;
    }

    /** 排序方法 使用选择排序，结果是从大到小的序列.
     */
    public void sort() {
        for (int i = 0; i < this.arr.length; i++) {
            for (int j = i + 1; j < this.arr.length; j++) {
                if (arr[i] < arr[j]) {
                    swap(i, j);
                }
            }
        }
    }

    /** 打印方法.
     * 输出排序后的数组
     */
    public void print() {
        System.out.println(Arrays.toString(arr));
    }

    /** 交换方法.
     * @param i 待交换数组元素的下标
     * @param j 待交换数组元素的下标
     */
    public void swap(final int i, final int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
