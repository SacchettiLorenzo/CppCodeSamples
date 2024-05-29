//this class are specific for the purpose of the exercises

public class MinFloatPriorityQueue extends PriorityQueue<Float> {

    public MinFloatPriorityQueue() {
        comparator = new FloatComparator();
        heap = new Heap<Float>(comparator);
        heap.setMinHeap();
    }

    public void DecreaseValue(Float old, Float newValue){
        if(comparator.compare(newValue,old) < 0){
            updateValue(old, newValue);
        }else{
            System.out.println("New value should be lower than old value");
        }
    }

}
