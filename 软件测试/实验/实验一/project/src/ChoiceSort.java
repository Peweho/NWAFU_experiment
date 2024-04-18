import java.util.Arrays;
public class ChoiceSort {
    /** arr����.
     * ������������
    */
    private int[] arr;
    /** ���췽��.
     * @param nums �Ҵ���������
     */
    public ChoiceSort(final int[] nums) {
        arr = nums;
    }

    /** ���򷽷� ʹ��ѡ�����򣬽���ǴӴ�С������.
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

    /** ��ӡ����.
     * �������������
     */
    public void print() {
        System.out.println(Arrays.toString(arr));
    }

    /** ��������.
     * @param i ����������Ԫ�ص��±�
     * @param j ����������Ԫ�ص��±�
     */
    public void swap(final int i, final int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
