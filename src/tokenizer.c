#ifndef TOKENIZER_C
#define TOKENIZER_C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct TokenUnitary
{
    int size;
    char *str;
};

struct TokenList
{
    int size;
    struct TokenUnitary *tokens;
};

typedef struct TokenList TokenList;
typedef struct TokenUnitary TokenUnitary;

static void verify_ptr_and_exit(void *ptr, const char *err_message);
static void verify_str_and_exit(const char *ptr);
void initialize(TokenList *list);

static void verify_ptr_and_exit(void *ptr, const char *err_message)
{
    if (!ptr)
    {
        perror("[vefptr-err]: Invalid Pointer");
        exit(EXIT_FAILURE);
    }
    perror(err_message);
    exit(EXIT_FAILURE);
}
static void verify_str_and_exit(const char *ptr)
{
    if (!ptr || ptr[0] == '\0')
    {
        verify_ptr_and_exit((void *)ptr, "[vefstr-err]: Invalid String.");
    }
}

void initialize(TokenList *list)
{
    verify_ptr_and_exit((void *)list, "[initialize-err]: invalid ptr to TokenList");

    list->size = 0;
    list->tokens = NULL;
}

#endif
