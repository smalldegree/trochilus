#include "trls_queue.h"


trls_uint_t
trls_queue_len(trls_queue_t *h)
{
    trls_uint_t  len = 0;
    trls_queue_t *node = NULL;

    node = trls_queue_head(h);

    do
    {
        len++;
        node = node->next;
    }
    while(node != trls_queue_sentinel(h));

    return len;
}

trls_queue_t *
trls_queue_pos(trls_queue_t *h, trls_uint_t pos)
{
    trls_uint_t  i, len;
    trls_queue_t *node;

    len = trls_queue_len(h);

    if(0 >= len || 0 > pos)
        return NULL;

    i = 0;
    trls_queue_tras(node, h)
    {
        if(i == pos)
            return node;

        i++;
    }

    return NULL;
}

trls_queue_t *
trls_queue_middle(trls_queue_t *h)
{
    trls_queue_t *middle;
    trls_queue_t *next;

    middle = trls_queue_head(h);

    if(middle == trls_queue_last(h))
        return middle;

    next = trls_queue_head(h);

    for(;;)
    {
        middle = trls_queue_next(middle);
        next = trls_queue_next(next);

        if(next == trls_queue_last(h))
            return middle;

        next = trls_queue_next(next);
        if(next == trls_queue_last(h))
            return middle;
    }
}

void
trls_queue_sort(trls_queue_t *h, trls_queue_cmp_pt cmp)
{
    trls_queue_t *q;
    trls_queue_t *prev;
    trls_queue_t *next;

    q = trls_queue_head(h);
    if(q == trls_queue_last(h))
        return;

    for(q = trls_queue_next(q); q != trls_queue_sentinel(h); q = next)
    {
        prev = trls_queue_prev(q);
        next = trls_queue_next(q);

        trls_queue_del(q);

        do
        {
            if(cmp(prev, q) <= 0)
                break;

            prev = trls_queue_prev(prev);
        }
        while(prev != trls_queue_sentinel(h));

        trls_queue_insert_head(prev, q);
    }
}
