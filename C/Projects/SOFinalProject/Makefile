SHELL:=bash
CC:=gcc
CFLAGS:=-ansi -pedantic -Wvla -Wextra -Werror -D_GNU_SOURCE

all: ./build/common.o ./build/master.o ./build/alimentazione.o ./build/atomo.o ./build/attivatore.o ./build/inibitore.o ./bin/master.out ./bin/alimentazione.out ./bin/atomo.out ./bin/attivatore.out ./bin/inibitore.out

./build/common.o: ./src/common.c ./include/common.h
	${CC} ${CFLAGS} -c $< -o $@ 

./build/master.o: ./src/master.c ./include/master.h ./include/common.h
	${CC} ${CFLAGS} -c $< -o $@ -lm

./bin/master.out: ./build/master.o ./build/common.o
	${CC} ./build/master.o ./build/common.o -o $@  -lm

./build/alimentazione.o: ./src/alimentazione.c ./include/alimentazione.h ./include/common.h
	${CC} ${CFLAGS} -c $< -o $@

./bin/alimentazione.out: ./build/alimentazione.o ./build/common.o
	${CC} ./build/alimentazione.o ./build/common.o -o $@ -lm

./build/atomo.o: ./src/atomo.c ./include/atomo.h ./include/common.h
	${CC} ${CFLAGS} -c $< -o $@

./bin/atomo.out: ./build/atomo.o ./build/common.o
	${CC} ./build/atomo.o ./build/common.o -o $@ -lm

./build/attivatore.o: ./src/attivatore.c ./include/attivatore.h ./include/common.h
	${CC} ${CFLAGS} -c $< -o $@

./bin/attivatore.out: ./build/attivatore.o ./build/common.o
	${CC} ./build/attivatore.o ./build/common.o -o $@ -lm

./build/inibitore.o: ./src/inibitore.c ./include/inibitore.h ./include/common.h
	${CC} ${CFLAGS} -c $< -o $@

./bin/inibitore.out: ./build/inibitore.o ./build/common.o
	${CC} ./build/inibitore.o ./build/common.o -o $@ -lm