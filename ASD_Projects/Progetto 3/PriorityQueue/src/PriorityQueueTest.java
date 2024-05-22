import static org.junit.Assert.*;
import org.junit.Test;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class PriorityQueueTest {




    @Test
    public void testEmpty(){
        IntegerComparator comparator_I = new IntegerComparator();
        PriorityQueue<Integer> PQ = new PriorityQueue<Integer>(comparator_I);
        assertTrue(PQ.empty());
    }

    @Test
    public void testPush(){
        IntegerComparator comparator_I = new IntegerComparator();
        PriorityQueue<Integer> PQ = new PriorityQueue<Integer>(comparator_I);
        PQ.push(10);
        assertTrue(PQ.contains(10));
    }

    @Test
    public void testContains(){
        IntegerComparator comparator_I = new IntegerComparator();
        PriorityQueue<Integer> PQ = new PriorityQueue<Integer>(comparator_I);
        PQ.push(1);
        PQ.push(2);
        PQ.push(10);
        PQ.push(6);
        PQ.push(20);
        assertTrue(PQ.contains(2));
    }

    @Test
    public void testTop(){
        IntegerComparator comparator_I = new IntegerComparator();
        PriorityQueue<Integer> PQ = new PriorityQueue<Integer>(comparator_I);
        Integer i = 10;
        PQ.push(i);
        assertEquals(PQ.top(),i);
    }

    @Test
    public void testPop(){
        IntegerComparator comparator_I = new IntegerComparator();
        PriorityQueue<Integer> PQ = new PriorityQueue<Integer>(comparator_I);
        Integer i = 10;
        PQ.push(1);
        PQ.push(2);
        PQ.push(i);
        PQ.push(6);
        PQ.push(20);
        PQ.pop();
        assertEquals(PQ.top(),i);
    }

    @Test
    public void testRemove(){
        IntegerComparator comparator_I = new IntegerComparator();
        PriorityQueue<Integer> PQ = new PriorityQueue<Integer>(comparator_I);
        PQ.push(1);
        PQ.push(2);
        PQ.push(10);
        PQ.push(6);
        PQ.push(20);
        PQ.remove(2);
        assertFalse(PQ.contains(2));
    }

}