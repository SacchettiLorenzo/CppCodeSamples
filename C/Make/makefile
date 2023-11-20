//makefile compila solo il file che è cambiato rispetto all'ultima compilazione
//compilazione condizionale
//la compilazione avviene guardando il timestamp di modifica del file oggetto
//i prerequisiti servono a identificare quali file sono nocessari per la compilazione e il linking
//target: quello prima dei ":"
//il nome del file generato deve essere sempre uguale al target
//per lanciare il makefile si usa il comando make main
//make supporta il pattern substitutution per accorciare la lunghezza dei comandi
//il pattern sobstitution è relativo alla specifica operazione di compilazione o linking e non a tutto il makefile
//se si crea un file chiamato "clean" eseguendo make clean il makefile genera un file chiamato clean al posto di eseguire la funzione clean
//.PHONY: target specifica che qualsiasi cosa chiamata come target non genera file ma esegue solamente comandi all'interno di makefile
//makefile va identato 

SHELL:=bash //tipo di shell usata
CC:=gcc
CFLAGS:= -ansi -pedantic //opzioni per il compilatore

.PHONY: clean 

all: main main2 //esegue la compilazione e il linking con differenti nomi come reqisito (da rivedere)


lib.o lib.c lib.h//prerequisiti di compilazione di lib.o dipendente da lib.c
	${CC} ${CFLAGS} -c lib.c -o lib.o //compilazione di lib in un file non eseguibile

main.o main.c lib.h
	${CC} ${CFLAGS} -c main.c -o main.opzioni

main: main.o lib.o // linking
	${CC} ${CFLAGS} main.o lib.o -o main

main: main.o lib.o // linking
${CC} ${CFLAGS} $^ -o main //usa i prerequisiti scritti la riga sopra

main: main.o lib.o // linking
${CC} ${CFLAGS} $^ -o $@ //usa il nome del target scritto la riga sopra come nome thel file

main.o main.c lib.h
	${CC} ${CFLAGS} -c $<-o $@ //nella compilazione non vanno inseriti gli header quindi in questo caso viene sostituito solo il primo tra i requisiti specificati

clean: 
	rm -f *.o main lib //rimuovo tutti i file oggetto che iniziano con un certo pattern(-f)senza segnalare errore se non esistono in modo da rieseguire la compilazione 




