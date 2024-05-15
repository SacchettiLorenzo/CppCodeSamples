//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        IntegerComparator comparator = new IntegerComparator();
        Heap<Integer> heap = new Heap<Integer>(comparator);

        heap.Insert(1);
        heap.Insert(4);
        heap.Insert(2);
        heap.Insert(3);
        heap.Insert(9);
        heap.Insert(7);
        heap.Insert(8);
        heap.Insert(10);
        heap.Insert(14);
        heap.Insert(16);

        heap.Extract();

        heap.Insert(12);

    }
}