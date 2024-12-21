#include "list.h"

#include <string.h>

static int input_line(char **str, FILE *f)
{
    *str = malloc((STR_MAX_LEN + 1) * sizeof(char));
    if (!(*str))
        return RC_ERR_MEM;

    char ch = fgetc(f);
    int i = 0;
    
    while (ch != '\n' && ch != EOF)
    {
        (*str)[i] = ch;
        i++;
        ch = fgetc(f);
    }

    (*str)[i] = '\0';

    if ((*str)[0] == '\0')
    {
        free(*str);
        return RC_ERR_EMPTY_WORD;
    }

    size_t len = i;
    void *p = realloc(*str, len + 1);
    if (!p)
        return RC_ERR_MEM;
    
    *str = p;

    return RC_OK;
}

static node_t *init_node(char *word)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
        return NULL;
    
    node->data = word;
    node->next = NULL;
    
    return node;
}

static void free_node(node_t *node)
{
    free(node->data);
    free(node);
}

void free_list(node_t *head)
{
    node_t *node;
    while (head)
    {
        node = (head)->next;
        free_node(head);
        head = node;
    }
}

int add_node(node_t **head, char *word)
{
    node_t *node = init_node(word);
    if (!node)
    {
        free_list(*head);
        return RC_ERR_MEM;
    }

    if (!(*head))
    {
        *head = node;
        return RC_OK;
    }

    node_t *curr_node = *head;
    while (curr_node->next)
        curr_node = curr_node->next;
    
    curr_node->next = node;

    return RC_OK;
}

int input_list(node_t **head, FILE *f)
{
    char *line;
    int read = 0;
    int res;

    while (!(res = input_line(&line, f)))
    { 
        if (add_node(head, line))
        {
            free_list(*head);
            return RC_ERR_MEM;
        }

        read = 1;
    }

    if (!read)
    {
        free_list(*head);
        return RC_ERR_EMPTY_FILE;
    }

    return RC_OK;
}

static int has_space(char *word)
{
    size_t len = strlen(word);

    for (size_t i = 0; i < len; i++)
    {
        if (word[i] == ' ')
            return 1;
    }
    return 0;
}

void split_letters(node_t **curr)
{
    char *word = (*curr)->data;
    size_t len = strlen(word);
    node_t *head = NULL;

    for (size_t i = 0; i < len; i++)
    {
        char *str = malloc(2 * sizeof(char));
        str[0] = word[i];
        str[1] = '\0';
        add_node(&head, str);
    }
    *curr = head;
}

void split_words(FILE *f, node_t **head)
{
    node_t *curr = *head;
    node_t *next;
    while (curr)
    {
        next = curr->next;
        if (!has_space(curr->data))
            split_letters(&curr);
        output_list(curr, f);
        curr->next = next;
        curr = next;
    }
}

void output_list(node_t *head, FILE *f)
{
    node_t *curr = head;
    while (curr) 
    {
        fprintf(f, "%s\n", curr->data);
        curr = curr->next;
    }
}

void print_list(node_t *head)
{
    node_t *curr = head;
    while (curr)
    {
        printf("%s\n", curr->data);
        curr = curr->next;
    }
}
