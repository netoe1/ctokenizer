#ifndef TOKENIZER_C
#define TOKENIZER_C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Tokens
{
    int size;
    char **vector;
};

typedef struct Tokens Tokens;

static void verify_ptr_and_exit(void *ptr, const char *err_message);
static void verify_str_and_exit(const char *ptr);

void init_tokens(Tokens *ptr);
void free_vectors(Tokens *ptr);
void tokenize(Tokens *ptr, char *prhase, const char *lead_to_cut);
void debug_get_tokens(Tokens *ptr);

static void verify_str_and_exit(const char *ptr)
{
    if (ptr == NULL || ptr[0] == '\0')
    {
        fprintf(stderr, "[verify_str-err]: ptr must be a valid pointer!\n");
        exit(EXIT_FAILURE);
    }
}

static void verify_ptr_and_exit(void *ptr, const char *err_message)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "%s\n", err_message);
        exit(EXIT_FAILURE);
    }
}

void init_tokens(Tokens *ptr) // Stable
{
    if (ptr->vector == NULL)
    {
        fprintf(stderr, "[init_tokens-err]: You cannot create a structure; it's already created.\n");
        return;
    }

    ptr->vector = NULL;
    ptr->size = 0;

    puts("[init_tokens-debug]: Tokens init with success.");
}

void free_vectors(Tokens *ptr) // Stable
{
    if (ptr == NULL)

        return;

    for (int i = 0; i < ptr->size; i++)
    {
        if (ptr->vector[i] != NULL)
        {
            printf("\n[free_vectors-debug]: Try to free pointer at %d position...\n", i);
            free(ptr->vector[i]);
            continue;
        }
        printf("\n[free_vectors-debug]: Pointer at %d is already NULL...\n", i);
    }
    free(ptr->vector);
}

void tokenize(Tokens *ptr, char phrase[], const char *lead_to_find)
{
    verify_ptr_and_exit((void *)ptr, "[tokenize-err]: invalid ptr structure");
    verify_str_and_exit(phrase);
    verify_str_and_exit(lead_to_find);

    char *phraseMutable = strdup(phrase);
    char *token = strtok(phraseMutable, lead_to_find);
    if (token == NULL)
    {
        fprintf(stderr, "[tokenize-err]: buffer not capable.");
        free_vectors(ptr);
        free(phraseMutable);
        exit(EXIT_FAILURE);
    }
    printf("\nmeu token eh %s\n", token);

    while (token != NULL)
    {
        token = strtok(NULL, lead_to_find);
        printf("\nTOKEN HEHE:%s", token);
        if (ptr->size == 0)
        {
            printf("\nptr-size:%d", ptr->size);
            ptr->vector = (char **)malloc(sizeof(char **));
            // if (ptr->vector == NULL)
            // {
            //     fprintf(stderr, "[tokenizer-err]: Out of memory.");
            //     free_vectors(ptr);
            //     free(phraseMutable);
            //     exit(EXIT_FAILURE);
            // }
            ptr->vector[ptr->size] = (char *)malloc(sizeof(char *) * (strlen(token) + 1));
            // if (ptr->vector[ptr->size] == NULL)
            // {
            //     fprintf(stderr, "[tokenizer-err]:Out of memory.");
            //     free_vectors(ptr);
            //     free(phraseMutable);
            //     exit(EXIT_FAILURE);
            // }
            ptr->vector[ptr->size][strlen(token) + 1] = '\0';
            sprintf(ptr->vector[0], "%s", token);
        }
        else
        {
            ptr->vector = (char **)realloc(ptr->vector, sizeof(char **));
            // if (ptr->vector[ptr->size] == NULL)
            // {
            //     fprintf(stderr, "[tokenizer-err]: Out of memory.");
            //     free_vectors(ptr);
            //     free(phraseMutable);
            //     exit(EXIT_FAILURE);
            // }

            ptr->vector[ptr->size] = (char *)malloc(sizeof(char *) * (strlen(token) + 1));
            // if (ptr->vector[ptr->size] == NULL)
            // {
            //     fprintf(stderr, "[tokenizer-err]: Out of memory.");
            //     free_vectors(ptr);
            //     free(phraseMutable);
            //     exit(EXIT_FAILURE);
            // }

            ptr->vector[ptr->size][strlen(token) + 1] = '\0';
            sprintf(ptr->vector[ptr->size], "%s", token);
        }
        ptr->size++;
    }
    free(phraseMutable);
}

void debug_get_tokens(Tokens *ptr)
{
    verify_ptr_and_exit(ptr, "[debug_get_tokens-err]: invalid Tokens *ptr at function parameter.");
    for (int i = 0; i == ptr->size; i++)
    {
        printf("\nToken [%d]:%s", i, ptr->vector[i]);
    }
}
#endif
