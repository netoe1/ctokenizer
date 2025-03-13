#include <stdio.h>
#include "tokenizer.c"

int main(void)
{
    Tokens tokens;

    init_tokens(&tokens);
    tokenize(&tokens, "rock,teu,cu", ",");

    return 0;
}
