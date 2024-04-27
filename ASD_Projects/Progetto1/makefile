OBJS	= main.o Generic_data_manipulation.o
SOURCE	= main.c Generic_data_manipulation.c
HEADER	= Generic_data_manipulation.h
OUT	= executable
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

Generic_data_manipulation.o: Generic_data_manipulation.c
	$(CC) $(FLAGS) Generic_data_manipulation.c 


clean:
	rm -f $(OBJS) $(OUT)