//this class are specific for the purpose of the exercises

public class MaxFloatPriorityQueue extends PriorityQueue<Float> {
    public MaxFloatPriorityQueue() {
        comparator = new FloatComparator();
        heap = new Heap<Float>(comparator);
        heap.setMaxHeap();
    }

    public void EncreaseValue(Float old, Float newValue){
        if(comparator.compare(newValue,old) > 0){
            updateValue(old, newValue);
        }else{
            System.out.println("New value should be greater than old value");
        }
    }

}