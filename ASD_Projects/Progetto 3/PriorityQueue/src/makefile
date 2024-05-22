OBJS    = Comparators.java AbstractHeap.java AbstractQueue.java Heap.java PriorityQueue.java Main.java
TEST    = Comparators.java AbstractHeap.java AbstractQueue.java Heap.java PriorityQueue.java PriorityQueueTest.java TestRunner.java
LIB     = ".:/junit-4.13.2.jar;/hamcrest-core-1.3.jar;"
CC  = javac

all: $(OBJS)

	$(CC) $(OBJS)

test: $(TEST)

	$(CC) -cp $(LIB) $(TEST)

clean:
	rm -f IntegerComparator.class StringComparator.class AbstractHeap.class AbstractQueue.class Heap.class PriorityQueue.class Main.class PriorityQueueTest.class TestRunner.class