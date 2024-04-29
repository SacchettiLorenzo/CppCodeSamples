OBJS	= main.o editDistance.o
TEST	= test.o editDistance.o UnitTest.o
OUT	= executable.out
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

clean:
	rm -f $(OBJS) $(OUT)

test: $(TEST)
	$(CC) -g $(TEST) -o $(OUT) $(LFLAGS)
	
test.o: test.c
	$(CC) $(FLAGS) test.c

UnitTest.o: UnitTest.c
	$(CC) $(FLAGS) UnitTest.c

editDistance.o: ./EditDistance.c 
	${CC} $(CFLAGS) -c $< -o $@ 
	
