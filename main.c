#include "list.h"

#define RC_ERR_OPEN 1
#define RC_ERR_IO 2

int main(void)
{
    FILE *f = fopen(FILE_IN, "r");
    if (!f)
        return RC_ERR_OPEN;

    node_t *head = NULL;
    int res_code = input_list(&head, f);
    if (res_code)
        return RC_ERR_IO;
    
    fclose(f);

    f = fopen(FILE_OUT, "w");

    split_words(f, &head);

    fclose(f);

    free_list(head);

    return RC_OK;
}

