SHELL:=bash 
CC:=gcc
CFLAGS := -Wall -Wextra -g

all: ./editDistance.o ./executable.out

./editDistance.o: ./EditDistance.c 
	${CC} $(CFLAGS) -c $< -o $@ 

./executable.out: ./EditDistance.o
	${CC} ./editDistance.o -o $@ 

.PHONY: clean
clean:
	rm -f editDistance.o executable.out