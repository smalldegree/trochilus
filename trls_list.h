#ifndef __TRLS_LIST_H__
#define __TRLS_LIST_H__


typedef struct trls_queue_s trls_queue_t;
struct trls_queue_s
{
    trls_queue_t *prev;
    trls_queue_t *next;
};

#endif
