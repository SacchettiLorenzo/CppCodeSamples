import java.util.Comparator;

public class PriorityQueue<T> implements AbstractQueue<T>{

    Heap<T> queue;
    Comparator<T> comparator;
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
        queue.Insert(o);
        return true;
    }

    //todo: test this method
    @Override
    public boolean contains(T o) {
        if(empty()){return false;}
        if(comparator.compare(queue.get(0),o) == 0){
            return true;
        }
        return contains_wrapped(o,1);
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
