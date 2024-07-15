import java.util.AbstractMap;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Optional;

public class PriorityQueue<T> implements AbstractQueue<T>{

    Heap<T> heap;
    Comparator<T> comparator;

    HashMap<Integer, T> map = new HashMap<Integer,T>(); //used to tell if an element is present or not
    public enum HeapType{MIN,MAX}

    protected PriorityQueue(){}

    public PriorityQueue(Comparator<T> comparator) {
        this.comparator = comparator;
        heap = new Heap<T>(comparator);
        heap.setMaxHeap();
        }


    public PriorityQueue(Comparator<T> comparator, PriorityQueue.HeapType heapType) {
        this.comparator = comparator;
        heap = new Heap<T>(comparator);
        if(heapType == HeapType.MIN){
            heap.setMinHeap();
        }
        else if(heapType == HeapType.MAX){
            heap.setMaxHeap();
        }
    }


    @Override
    public boolean empty() {
        if(heap.getHeap_size() == 0){
            return true;
        }
        return false;
    }

    @Override
    public boolean push(T o) {
        AbstractMap.SimpleEntry<Integer,T> res = heap.Insert(o);
        map.put(res.getKey().hashCode(),res.getValue());
        return true;
    }

    @Override
    public boolean contains(T o) {
        return map.containsValue(o);
    }



    @Override
    public T top() {
        return heap.getFirst().getValue();
    }

    @Override
    public void pop() {
        heap.Extract();
    }

    @Override
    public boolean remove(T o) {
         //todo: check if work. may uncomment Heapify in remove method in Heap class
        if(comparator.compare(heap.getFirst().getValue(),o) == 0){
            heap.Remove(0);
            return true;
        }
        int res = remove_if_exist(o,1);
        map.remove(res);
        // check if need to remove from map or not
        int index = 0;
        while(index < heap.getHeap_size()){
            if(comparator.compare(o,heap.get(index).getValue()) == 0){
                map.remove(heap.get(index).getKey().hashCode());
                break;
            }
            index++;
        }


        if(res != -1){
            return true;
        }
        return false;
    }

    private int  remove_if_exist(T o, int index){
        if(comparator.compare(heap.get(index).getValue(),o) == 0){
            int resKey = heap.get(index).getKey();
            heap.Remove(index);
            return resKey;
        }

        int res = -1;
        if(comparator.compare(o,heap.get(index).getValue()) < 0) {

            if (heap.Left(index) < heap.getHeap_size()) {
                res =  remove_if_exist(o, heap.Left(index));
            }
            if (res == -1 && heap.Right(index) < heap.getHeap_size()) {
                res =  remove_if_exist(o, heap.Right(index));
            }
            return res;
        }

        return -1;
    }

    protected void updateValue(T o, T newValue){
        int index = 0;
        while(index < heap.getHeap_size()){
            if(comparator.compare(o,heap.get(index).getValue()) == 0){
                map.remove(heap.get(index).getKey().hashCode());
                heap.Remove(index);
                AbstractMap.SimpleEntry<Integer,T> res = heap.Insert(newValue);
                map.put(res.getKey().hashCode(),res.getValue());
                heap.Heapify(0);


                break;

            }
            index++;
        }
        index = 0;
        while(index < heap.getHeap_size()){
            if(comparator.compare(o,heap.get(index).getValue()) == 0){
                map.put(heap.get(index).getKey().hashCode(),heap.get(index).getValue());

                break;

            }
            index++;
        }
    }

}
