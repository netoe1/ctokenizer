#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.c"

int main(void)
{
    TokenList list;

    initialize(&list);
    addNewToken(&list, "hehe0");
    addNewToken(&list, "hehe1");
    addNewToken(&list, "hehe2");
    removeToken(&list, "hehe1");
    printTokens(&list);
    freeTokens(&list);
    return 0;
}
