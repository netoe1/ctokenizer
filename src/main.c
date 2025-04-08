#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.c"
int main(void)
{
    struct Node *list = NULL;

    addToken(&list, "alpha");
    addToken(&list, "beta");
    addToken(&list, "gamma");
    addToken(&list, "delta");

    printf("Original list:\n");
    printList(list);

    printf("\nIndex of 'gamma': %d\n", getTokenIndex(list, "gamma"));

    printf("\nRemoving 'beta' by content:\n");
    removeTokenByContent(&list, "beta");
    printList(list);

    printf("\nRemoving index 1 (should remove 'gamma'):\n");
    removeTokenByIndex(&list, 1);
    printList(list);
    freeList(list);
    return 0;
}