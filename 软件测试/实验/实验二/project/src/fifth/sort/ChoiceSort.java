package fifth.sort;

import java.util.Arrays;

public class ChoiceSort {
    private int[] arr;
    public int[] sort(final int[] nums) {
        arr = nums;
        for (int i = 0; i < this.arr.length; i++) {
            for (int j = i + 1; j < this.arr.length; j++) {
                if (arr[i] < arr[j]) {
                    swap(i, j);
                }
            }
        }

        return arr;
    }
    public void swap(final int i, final int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
