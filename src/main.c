#include "tokenizer.h"

int main(void)
{
    struct Node *node = NULL;

    char *teste = "teste1\nfoo2,Inter3";

    if (!teste)
    {
        fprintf(stderr, "main-err: NULL string provided!\n");
        return -1;
    }
    tokenize(&node, teste, " ");
    printTokens(node);
    return 0;
}
