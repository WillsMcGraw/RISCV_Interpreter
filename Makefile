
CFLAGS = -Wextra

all: emulator

emulator: main.o parser.o interpreter.o basic_instruction_testing.o
	gcc $(CFLAGS) main.o parser.o interpreter.o basic_instruction_testing.o -o emulator

main.o: main.c 
	gcc $(CFLAGS) -c main.c

parser.o: parser.c 
	gcc $(CFLAGS) -c parser.c

interpreter.o: interpreter.c 
	gcc $(CFLAGS) -c interpreter.c

basic_instruction_testing.o: basic_instruction_testing.c 
	gcc $(CFLAGS) -c basic_instruction_testing.c

clean:
	rm main.o parser.o interpreter.o basic_instruction_testing.o emulator instructionLog.txt