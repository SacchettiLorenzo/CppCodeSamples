import java.util.AbstractMap;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;

public class PriorityQueue<T> implements AbstractQueue<T>{

    Heap<T> queue;
    Comparator<T> comparator;
    HashMap<Integer, T> map = new HashMap<Integer,T>();
    public PriorityQueue(Comparator<T> comparator) {
        this.comparator = comparator;
        queue = new Heap<T>(comparator);
    }

    @Override
    public boolean empty() {
        if(queue.getHeap_size() == 0){
            return true;
        }
        return false;
    }

    @Override
    public boolean push(T o) {
        AbstractMap.SimpleEntry<Integer,T> res = queue.Insert(o);
        map.put(res.getKey(),res.getValue());
        return true;
    }

    @Override
    public boolean contains(T o) {
        //this map is not a copy of queue but only keep pointer to his element
        //HashMap<Integer, T> map = new HashMap<Integer,T>();
        //map = (HashMap<Integer, T>) queue.getHeap().stream().collect(Collectors.toMap(Map.Entry<Integer, T>::getKey, Map.Entry::getValue));

        return map.containsValue(o);
        //        if(empty()){return false;}
//        if(comparator.compare(queue.get(0),o) == 0){
//            return true;
//        }
//        return contains_wrapped(o,1);
    }

    private boolean contains_wrapped(T o, int index){
       if(comparator.compare(queue.get(index),o) == 0){
           return true;
       }

       boolean res = false;
        if(comparator.compare(o,queue.get(index)) < 0) {

            //search left
            if (queue.Left(index) < queue.getHeap_size()) {
                res =  contains_wrapped(o, queue.Left(index));
            }
            //serch right
            if (res != true && queue.Right(index) < queue.getHeap_size()) {
                res =  contains_wrapped(o, queue.Right(index));
            }
            return res;
        }

        return false;
    }

    @Override
    public T top() {
        return queue.getFirst();
    }

    @Override
    public void pop() {
        queue.Extract();
    }

    @Override
    public boolean remove(T o) {
        map.remove(o);
         //todo: check if work. may uncomment Heapify in remove method in Heap class
        if(comparator.compare(queue.get(0),o) == 0){
            queue.Remove(0);
            return true;
        }
        return remove_if_exist(o,1);
    }

    private boolean remove_if_exist(T o, int index){
        if(comparator.compare(queue.get(index),o) == 0){
            queue.Remove(index);
            return true;
        }

        boolean res = false;
        if(comparator.compare(o,queue.get(index)) < 0) {

            if (queue.Left(index) < queue.getHeap_size()) {
                res =  remove_if_exist(o, queue.Left(index)+1);
            }
            if (res != true && queue.Right(index) > queue.getHeap_size()) {
                res =  remove_if_exist(o, queue.Right(index)+1);
            }
            return res;
        }

        return false;
    }
}
