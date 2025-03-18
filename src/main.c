#include <stdio.h>
#include "tokenizer.c"

int main(void)
{
    Tokens tokens;

    init_tokens(&tokens);
    tokenize(&tokens, "hello,hello", ",");
    free_vectors(&tokens);
    return 0;
}
