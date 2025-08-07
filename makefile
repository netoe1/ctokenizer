
SRC =./src
TOKENIZER_C = $(SRC)/tokenizer.c
TOKENIZER_H = $(SRC)/tokenizer.h

all:
	gcc -o main ./src/main.c ./src/tokenizer.c -g


tokenizer.o: ./src/tokenizer.h
	gcc -o tokenizer.o -c ./src/tokenizer.c

debug_mem:
	make all
	gdb main
clean:
	rm -f main *.bin *.o