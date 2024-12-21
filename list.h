#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

#define RC_OK 0
#define RC_ERR_EMPTY_FILE 3
#define RC_ERR_EMPTY_WORD 4
#define RC_ERR_MEM 5

#define STR_MAX_LEN 50

#define FILE_IN "in.txt"
#define FILE_OUT "out.txt"

typedef struct node node_t;

struct node
{
    char *data;
    node_t *next;
};

int input_list(node_t **head, FILE *f);
void output_list(node_t *head, FILE *f);
void print_list(node_t *head);
void free_list(node_t *head);
void split_words(FILE *f, node_t **head);
void split_letters(node_t **curr);

#endif //LIST_H
