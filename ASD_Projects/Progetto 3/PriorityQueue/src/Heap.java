import java.util.Comparator;
import java.util.Vector;
import java.util.*;

public class Heap<T> implements AbstractHeap<T>{

    private int heap_size = 0;
    ArrayList<T> heap;
    Comparator<T> comparator;
    public Heap(Comparator<T> comparator) {
        heap = new ArrayList<>();
        this.comparator = comparator;
    }

    @Override
    public int Parent(int index) {
        return index/2;
    }

    @Override
    public int Left(int index){
        return index*2;
    };

    @Override
    public int Right(int index){
        return index*2+1;
    }

    @Override
    public void Insert(T value) {
        heap_size++;
        int i = heap_size-1;
        heap.addLast(value);


        while (i > 0 &&  comparator.compare(heap.get(Parent(i)),heap.get(i)) < 0) {
            Collections.swap(heap,i,Parent(i));
            i = Parent(i);
        }
    }

    @Override
    public void Extract() {
        heap.removeFirst();
        heap_size--;
        Heapify(0);
    }

    @Override
    public void Heapify(int index) {
        int largest = index;
        if(comparator.compare(heap.get(Left(index)), heap.get(index)) > 0){
            largest = Left(index);
        }

        if(comparator.compare(heap.get(Right(index)), heap.get(index)) > 0){
            largest = Right(index);
        }
        if(largest != index){
            Collections.swap(heap,largest,index);
            Heapify(largest);
        }

    }

}
