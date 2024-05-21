import java.util.Comparator;
import java.util.ArrayList;
import java.util.*;

public class Heap<T> implements AbstractHeap<T>{

    private int heap_size = 0;

    private ArrayList<T> heap;
    private Comparator<T> comparator;
    public int getHeap_size() {
        return heap_size;
    }
    public Heap(Comparator<T> comparator) {
        this.comparator = comparator;
        heap = new ArrayList<T>();
    }

    public T getFirst(){
            try {
                return this.heap.getFirst();
            }catch (NoSuchElementException e){
                System.out.println("Heap is empty");
            }
        return null;
    }

    public T get(int index){
        try {
            return heap.get(index);
        }catch (IndexOutOfBoundsException e){
            System.out.println("Heap does not reach " + index + "th element");
        }
       return null;
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
           while (i > 0 && comparator.compare(heap.get(Parent(i)), heap.get(i)) < 0) {
               Collections.swap(heap, i, Parent(i));
               i = Parent(i);
           }
    }

    @Override
    public void Extract() {
        try{
            heap.removeFirst();
        }catch (NoSuchElementException e){
            System.out.println("Heap is empty");
        }

        heap_size--;
        Heapify(0);
    }

    public void Remove(int index){
        try{
            heap.remove(index);
        }catch (IndexOutOfBoundsException e){
            System.out.println("Heap does not reach " + index + "th element");
        }
        heap_size--;
        //Heapify(0); //todo: check if needs to uncomment this
    }

    @Override
    public void Heapify(int index) {
        int largest = index;
        //find max
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
