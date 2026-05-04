
CFLAGS = -Wall -Wextra

all: interp

interp: main.o parser.o interpreter.o tests.o
	gcc $(CFLAGS) main.o parser.o interpreter.o tests.o -o interp

main.o: main.c 
	gcc $(CFLAGS) -c main.c

parser.o: parser.c 
	gcc $(CFLAGS) -c parser.c

interpreter.o: interpreter.c 
	gcc $(CFLAGS) -c interpreter.c

tests.o: tests.c 
	gcc $(CFLAGS) -c tests.c

clean:
	rm main.o parser.o interpreter.o tests.o interp instructionLog.txt