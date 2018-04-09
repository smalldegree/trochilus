#include <stdio.h>
#include <stdlib.h>
#include "trls_config.h"


int main(int argc, char **argv)
{
    trls_queue_t head;
    trls_queue_t *q;

    q = malloc(sizeof(trls_queue_t));

    trls_queue_init(&head);
    trls_queue_insert_head(&head, q);

    q = malloc(sizeof(trls_queue_t));
    trls_queue_insert_head(&head, q);

    q = malloc(sizeof(trls_queue_t));
    trls_queue_insert_head(&head, q);

    return 0;
}
