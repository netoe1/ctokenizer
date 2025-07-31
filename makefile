
SRC =./src
TOKENIZER_C = $(SRC)/tokenizer.c
TOKENIZER_H = $(SRC)/tokenizer.h

all:
	gcc -o main tokenizer.c main.c


tokenizer.o: ./src/tokenizer.h
	gcc -o tokenizer.o -c ./src/tokenizer.c
