import date.Date;

public class Main {
    public static void main(String[] args) {
        // first();
        // second();
//        third();
    }

    public static void first() {

        int[] arr = {1, 23, 3};
        ChoiceSort choiceSort = new ChoiceSort(arr);
        choiceSort.sort();
        choiceSort.print();
    }

    public static void second() {
        Triangle triangle = new Triangle(1, 2, 3);
        System.out.println(triangle.judge());
    }

    public static void third() {
        Date date = new Date(2004, 11, 29);
        System.out.println(date.gapNext());
    }
}
