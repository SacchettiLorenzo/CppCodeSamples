SHELL:=bash
CC:=gcc
CFLAGS:=-ansi -pedantic -Wvla -Wextra -Werror 

all: ./build/master.o ./build/alimentazione.o ./build/atomo.o ./build/attivatore.o ./bin/master.out ./bin/alimentazione.out  ./bin/atomo.out ./bin/attivatore.out

./build/master.o: ./src/master.c ./include/master.h ./include/common.h
	${CC} ${CFLAGS} -c $< -o $@

./bin/master.out: ./build/master.o
	${CC} $< -o $@ -lm

./build/alimentazione.o: ./src/alimentazione.c ./include/alimentazione.h ./include/common.h
	${CC} ${CFLAGS} -c $< -o $@

./bin/alimentazione.out: ./build/alimentazione.o
	${CC} $< -o $@

./build/atomo.o: ./src/atomo.c ./include/atomo.h ./include/common.h
	${CC} ${CFLAGS} -c $< -o $@

./bin/atomo.out: ./build/atomo.o
	${CC} $< -o $@

./build/attivatore.o: ./src/attivatore.c ./include/attivatore.h ./include/common.h
	${CC} ${CFLAGS} -c $< -o $@

./bin/attivatore.out: ./build/attivatore.o
	${CC} $< -o $@



