

public class Main {
    public static void main(String[] args) {



//        StringComparator comparator_S = new StringComparator();
//        Heap<String> heap_String = new Heap<String>(comparator_S);
//
//        heap_String.Insert("ciao");
//        heap_String.Insert("come");
//        heap_String.Insert("stai?");
//        heap_String.Insert("io");
//        heap_String.Insert("tutto");
//        heap_String.Insert("bene");
//        heap_String.Insert("la");
//        heap_String.Insert("famiglia?");
//        heap_String.Insert("bene");
//        heap_String.Insert("dai");
//        heap_String.Remove(4);
//
//        heap_String.Extract();
//
//        heap_String.Insert("suca");





        IntegerComparator comparator_I = new IntegerComparator();
//        Heap<Integer> heap_int = new Heap<Integer>(comparator_I);
//        heap_int.get(12);
//        heap_int.Insert(20);
//        heap_int.Insert(21);
//        heap_int.Insert(68);
//        heap_int.Insert(5);
//        heap_int.Insert(15);
//        heap_int.Insert(8);



//        PriorityQueue<Integer> PQ = new PriorityQueue<Integer>(comparator_I,PriorityQueue.HeapType.MAX);
//        PQ.push(1);
//        PQ.push(2);
//        PQ.push(10);
//        PQ.push(6);
//        PQ.push(20);
//        PQ.push(20);


        MaxFloatPriorityQueue PQ = new MaxFloatPriorityQueue();
        PQ.push(1.0f);
        PQ.push(2.0f);
        PQ.push(10.0f);
        PQ.push(6.0f);
        PQ.push(20.0f);
        PQ.push(20.0f);
        PQ.EncreaseValue(20.0f,30.0f);
        PQ.EncreaseValue(20.0f,30.0f);
        //PQ.remove(5.0f);

        //System.out.println(PQ.top());
        //boolean contains = PQ.contains(10);
        //Integer res = PQ.top();
    }
}