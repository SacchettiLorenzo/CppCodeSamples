import java.util.*;

public class Heap<T> implements AbstractHeap<T>{

    private int heap_size = 0;
    private int key = 0;
    T x;

    boolean MinMax= true; //true = max

    private ArrayList<Map.Entry<Integer,T>> heap;
    private Comparator<T> comparator;
    public int getHeap_size() {
        return heap_size;
    }
    public Heap(Comparator<T> comparator) {
        this.comparator = comparator;
        heap = new ArrayList<Map.Entry<Integer,T>>();
    }

    public ArrayList<Map.Entry<Integer, T>> getHeap() {
        return heap;
    }

    public void setMaxHeap(){
        this.MinMax = true;
    }

    public void setMinHeap(){
        this.MinMax = false;
    }

    private int getKey(){
        return ++key;
    }
    public Map.Entry<Integer, T> getFirst(){
            try {
                return this.heap.getFirst();
            }catch (NoSuchElementException e){
                System.out.println("Heap is empty");
            }
        return null;
    }

    public Map.Entry<Integer, T> get(int index){
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
    public AbstractMap.SimpleEntry<Integer,T> Insert(T value) {
        heap_size++;
        int i = heap_size-1;
        AbstractMap.SimpleEntry<Integer,T> am = new AbstractMap.SimpleEntry<Integer,T>(value.toString().hashCode(),value);
        heap.addLast(am);
        //select operation based on the type of heap desired
        if(this.MinMax){
            while (i > 0 && comparator.compare(heap.get(Parent(i)).getValue(), heap.get(i).getValue()) < 0) {
                Collections.swap(heap, i, Parent(i));
                i = Parent(i);
            }
        }else{
            while (i > 0 && comparator.compare(heap.get(Parent(i)).getValue(), heap.get(i).getValue()) > 0) {
                Collections.swap(heap, i, Parent(i));
                i = Parent(i);
            }
        }
           return am;
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
        if(this.MinMax){
            int largest = index;
            //find max
            if(comparator.compare(heap.get(Left(index)).getValue(), heap.get(index).getValue()) > 0){
                largest = Left(index);
            }

            if(comparator.compare(heap.get(Right(index)).getValue(), heap.get(index).getValue()) > 0){
                largest = Right(index);
            }
            if(largest != index){
                Collections.swap(heap,largest,index);
                Heapify(largest);
            }
        }else{
            int smallest = index;
            //find max
            if(comparator.compare(heap.get(Left(index)).getValue(), heap.get(index).getValue()) < 0){
                smallest = Left(index);
            }

            if(comparator.compare(heap.get(Right(index)).getValue(), heap.get(index).getValue()) < 0){
                smallest = Right(index);
            }
            if(smallest != index){
                Collections.swap(heap, smallest,index);
                Heapify(smallest);
            }
        }


    }

}
