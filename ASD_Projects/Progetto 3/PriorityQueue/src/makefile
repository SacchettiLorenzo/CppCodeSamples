# Source files
OBJS    = Comparators.java AbstractHeap.java AbstractQueue.java Heap.java PriorityQueue.java Main.java
TEST    = junit-4.13.2.jar hamcrest-core-1.3.jar Comparators.java AbstractHeap.java AbstractQueue.java Heap.java PriorityQueue.java PriorityQueueTest.java

# Compiler and execution commands
CC      = javac
EXEC    = java

# Classpath
JUNIT_CP = junit-4.13.2.jar:hamcrest-core-1.3.jar

all: compile

compile: $(OBJS)
	$(CC) $(OBJS)

test: $(TEST)
	$(CC) -cp $(JUNIT_CP):. $(filter %.java, $(TEST))

run: test
	$(EXEC) -cp $(JUNIT_CP):. org.junit.runner.JUnitCore PriorityQueueTest

clean:
	rm -f *.class
