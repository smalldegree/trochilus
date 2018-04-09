#ifndef __TRLS_QUEUE_H__
#define __TRLS_QUEUE_H__


#include "trls_base.h"


//trls_queue node definition
struct trls_queue_s
{
    struct trls_queue_s *prev;
    struct trls_queue_s *next;
};
typedef struct trls_queue_s trls_queue_t;


//trls_queue comparison definition
typedef trls_int_t (*trls_queue_cmp_pt)(trls_queue_t *m, trls_queue_t *n);


/*
 * trls_queue_init(h)
 * trls_queue_empty(h)
 * trls_queue_sentinel(h)
 * trls_queue_head(h)
 * trls_queue_last(h)
 * trls_queue_prev(q)
 * trls_queue_next(q)
 * trls_queue_middle(h)
 * trls_queue_del(q)
 * trls_queue_len(h)
 * trls_queue_split(h, q, n)
 * trls_queue_union(h, n)
 * trls_queue_tras(pos, h)
 * trls_queue_entry(q, type, mem)
 * trls_queue_insert_head(h, q)
 * trls_queue_insert_tail(h, q)
 * trls_queue_insert_prev(p, q)
 * trls_queue_insert_next(p, q)
 * trls_queue_insert_behind_head(h, q)
 * trls_queue_insert_before_tail(h, q)
 * trls_queue_sort(h, cmp)
 */


//init a trls_queue
#define trls_queue_init(h)                                         \
        (h)->prev = (h);                                               \
        (h)->next = (h)

//judge whether a trls_queue is empty
#define trls_queue_empty(h)                                        \
        (h) == (h)->prev

//set the sentinel node for a trls_queue
#define trls_queue_sentinel(h)                                     \
        (h)

//get the head node from a trls_queue
#define trls_queue_head(h)                                         \
        (h)->next

//get the last node from a trls_queue
#define trls_queue_last(h)                                         \
        (h)->prev

//get the prev node from a trls_queue node
#define trls_queue_prev(q)                                         \
        (q)->prev

//get the next node from a trls_queue node
#define trls_queue_next(q)                                         \
        (q)->next

//get the middle node from a trls_queue
//implemented by a function

//delete the node from a trls_queue
#define trls_queue_del(q)                                          \
        (q)->next->prev = (q)->prev;                                   \
        (q)->prev->next = (q)->next;                                   \
        (q)->prev = NULL;                                            \
        (q)->next = NULL

//get the nodes total num for a trls_queue
#define trls_queue_len(h)                                          \
        do                                                         \
        {                                                          \
            trls_uint_t  len = 0;                                  \
            trls_queue_t *node = NULL;                             \
                                                                   \
            node = trls_queue_head(h);                             \
                                                                   \
            do                                                     \
            {                                                      \
                len++;                                             \
                node = node->next;                                 \
            }                                                      \
            while(node != trls_queue_sentinel(h))                  \
                                                                   \
            return len;                                            \
        }                                                          \
        while(0)

//split trls_queue h into h & n two trls_queues by node q
#define trls_queue_split(h, q, n)                                  \
        (n)->prev = (h)->prev;                                         \
        (n)->prev->next = (n);                                         \
        (n)->next = (q);                                               \
        (h)->prev = (q)->prev;                                         \
        (h)->prev->next = (h);                                         \
        (q)->prev = (n)

//union trls_queue h & n to a trls_queue h
#define trls_queue_union(h, n)                                     \
        (h)->prev->next = (n)->next;                                   \
        (n)->next->prev = (h)->prev;                                   \
        (h)->prev = (n)->prev;                                         \
        (n)->prev->next = (h)

//traverse a trls_queue h
#define trls_queue_tras(pos, h)                                    \
        for((pos) = (h)->next; (pos) != trls_queue_sentinel(h);    \
            (pos) = (pos)->next)

//get the user data associated with a trls_queue node q
#define trls_queue_entry(q, type, mem)                             \
        (type *)((u_char *)(q) - offsetof(type, mem))

//insert the node q before the head node, hold 1st position
#define trls_queue_insert_head(h, q)                               \
        (q)->next = (h)->next;                                         \
        (q)->next->prev = (q);                                         \
        (q)->prev = (h);                                               \
        (h)->next = (q)

//insert the node q behind the last node, hold last position
#define trls_queue_insert_tail(h, q)                               \
        (q)->prev = (h)->prev;                                         \
        (q)->prev->next = (q);                                         \
        (q)->next = (h);                                               \
        (h)->prev = (q)

//insert the node q before the node p
#define trls_queue_insert_prev(p, q)                               \
        (q)->prev = (p)->prev;                                         \
        (q)->prev->next = (q);                                         \
        (q)->next = (p);                                               \
        (p)->prev = (q)

//insert the node q behind the node p
#define trls_queue_insert_next(p, q)                               \
        (q)->next = (p)->next;                                         \
        (q)->next->prev = (q);                                         \
        (q)->prev = (p);                                               \
        (p)->next = (q)

//insert the node q behind the head node, hold 2rd position
#define trls_queue_insert_behind_head(h, q)                        \
        trls_queue_insert_next((h)->next, q)

//insert the node q before the last node, hold 2rd last position
#define trls_queue_insert_before_tail(h, q)                        \
        trls_queue_insert_prev((h)->prev, q)


trls_queue_t *
trls_queue_middle(trls_queue_t *h);

void
trls_queue_sort(trls_queue_t *h, trls_queue_cmp_pt cmp);


#endif
