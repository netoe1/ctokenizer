#include "tokenizer.h"

int main(void)
{
    struct Node *node;

    char *teste = "teste1\nfoo2,Inter3";
    tokenize(&node, teste, " ");
    printTokens(node);
    return 0;
}
