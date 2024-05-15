OBJS	= main.o Generic_data_manipulation.o
TEST	= test.o Generic_data_manipulation.o UnitTest.o
SOURCE	= main.c Generic_data_manipulation.c
HEADER	= Generic_data_manipulation.h
OUT	= executable.out
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) 

main.o: main.c
	$(CC) $(FLAGS) main.c 

clean:
	rm -f $(OBJS) $(OUT)

test: $(TEST)
	$(CC) -g $(TEST) -o $(OUT) 

test.o: test.c
	$(CC) $(FLAGS) test.c

UnitTest.o: UnitTest.c
	$(CC) $(FLAGS) UnitTest.c

Generic_data_manipulation.o: Generic_data_manipulation.c
	$(CC) $(FLAGS) Generic_data_manipulation.c