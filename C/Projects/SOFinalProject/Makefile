SHELL:=bash
CC:=gcc
CFLAGS:=-ansi -pedantic -Wvla -Wextra -Werror

./build/master.o: ./src/master.c ./include/master.h
	${CC} ${CFLAGS} -c $< -o $@
