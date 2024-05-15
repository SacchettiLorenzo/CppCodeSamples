OBJS	= main.o edit_distance.o
TEST	= test.o edit_distance.o UnitTest.o
SOURCE	= main.c edit_distance.c
HEADER	= edit_distance.h
OUT	= executable.out
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra

all: $(OBJS)

	$(CC) -g $(OBJS) -o $(OUT) 

main.o: main.c
	$(CC) $(FLAGS) main.c 

clean:
	rm -f $(OBJS) $(TEST) $(OUT)

test: $(TEST)
	$(CC) -g $(TEST) -o $(OUT) 
	
test.o: test.c
	$(CC) $(FLAGS) test.c

UnitTest.o: UnitTest.c
	$(CC) $(FLAGS) UnitTest.c

edit_distance.o: edit_distance.c 
	${CC} $(FLAGS) edit_distance.c  
	
