#include "trls_cunit.h"
#include "trls_config.h"


static trls_queue_t *q1, *q2, *q3, *q4, *q5;
static trls_queue_t *g_trls_queue_head = NULL;
static trls_queue_t *g_trls_queue_arr[5];
static trls_queue_t *g_trls_queue_n = NULL;


void
test_trls_queue_init(void)
{
    trls_queue_init(g_trls_queue_head);

    CU_ASSERT_PTR_EQUAL(g_trls_queue_head->prev, g_trls_queue_head->next);
    CU_ASSERT_PTR_EQUAL(g_trls_queue_head->prev, g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(g_trls_queue_head->next, g_trls_queue_head);
}

void
test_trls_queue_empty(void)
{
    int res;

    trls_queue_init(g_trls_queue_head);
    res = trls_queue_empty(g_trls_queue_head);

    CU_ASSERT_EQUAL(res, 1);
}

void
test_trls_queue_sentinel(void)
{
    trls_queue_t *sentinel;

    sentinel = trls_queue_sentinel(g_trls_queue_head);

    CU_ASSERT_PTR_EQUAL(sentinel, g_trls_queue_head);
}

void
test_trls_queue_head(void)
{
    trls_queue_t *queue;

    trls_queue_insert_tail(g_trls_queue_head, q1);
    trls_queue_insert_tail(g_trls_queue_head, q2);

    queue = trls_queue_head(g_trls_queue_head);

    CU_ASSERT_PTR_EQUAL(queue, q1);
}

void
test_trls_queue_last(void)
{
    trls_queue_t *queue;

    queue = trls_queue_last(g_trls_queue_head);

    CU_ASSERT_PTR_EQUAL(queue, q2);
}

void
test_trls_queue_prev(void)
{
    trls_queue_t *queue;

    queue = trls_queue_prev(q2);
    CU_ASSERT_PTR_EQUAL(queue, q1);

    queue = trls_queue_prev(q1);
    CU_ASSERT_PTR_EQUAL(queue, g_trls_queue_head);

    queue = trls_queue_prev(g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(queue, q2);
}

void
test_trls_queue_next(void)
{
    trls_queue_t *queue;

    queue = trls_queue_next(q1);
    CU_ASSERT_PTR_EQUAL(queue, q2);

    queue = trls_queue_next(q2);
    CU_ASSERT_PTR_EQUAL(queue, g_trls_queue_head);

    queue = trls_queue_next(g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(queue, q1);
}

void
test_trls_queue_middle(void)
{
    trls_queue_t *queue;

    queue = trls_queue_middle(g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(queue, q2);

    trls_queue_insert_tail(g_trls_queue_head, q3);

    queue = trls_queue_middle(g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(queue, q2);

    trls_queue_insert_tail(g_trls_queue_head, q4);

    queue = trls_queue_middle(g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(queue, q3);
}

void
test_trls_queue_del(void)
{
    trls_uint_t len;

    len = trls_queue_len(g_trls_queue_head);
    CU_ASSERT_EQUAL(len, 4);

    trls_queue_del(q4);
    len = trls_queue_len(g_trls_queue_head);
    CU_ASSERT_EQUAL(len, 3);

    CU_ASSERT_PTR_EQUAL(q3->next, g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(g_trls_queue_head->prev, q3);
}

void
test_trls_queue_len(void)
{
    trls_uint_t len;

    len = trls_queue_len(g_trls_queue_head);
    CU_ASSERT_EQUAL(len, 3);

    trls_queue_insert_tail(g_trls_queue_head, q4);
    len = trls_queue_len(g_trls_queue_head);
    CU_ASSERT_EQUAL(len, 4);
}

void
test_trls_queue_split(void)
{
    trls_queue_split(g_trls_queue_head, q3, g_trls_queue_n);

    CU_ASSERT_PTR_EQUAL(g_trls_queue_head->prev, q2);
    CU_ASSERT_PTR_EQUAL(q2->next, g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(g_trls_queue_n->prev, q4);
    CU_ASSERT_PTR_EQUAL(g_trls_queue_n->next, q3);
    CU_ASSERT_PTR_EQUAL(q3->prev, g_trls_queue_n);
    CU_ASSERT_PTR_EQUAL(q4->next, g_trls_queue_n);
}

void
test_trls_queue_union(void)
{
    trls_queue_union(g_trls_queue_head, g_trls_queue_n);

    CU_ASSERT_PTR_EQUAL(q2->next, q3);
    CU_ASSERT_PTR_EQUAL(q3->prev, q2);
    CU_ASSERT_PTR_EQUAL(q4->next, g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(g_trls_queue_head->prev, q4);
}

void
test_trls_queue_tras(void)
{
    trls_uint_t  i;
    trls_queue_t *pos;

    i = 0;
    trls_queue_tras(pos, g_trls_queue_head)
    {
        CU_ASSERT_PTR_EQUAL(pos, g_trls_queue_arr[i]);
        i++;
    }
}

void
test_trls_queue_pos(void)
{
    trls_uint_t  i, len;
    trls_queue_t *queue;

    len = trls_queue_len(g_trls_queue_head);
    for(i = 0; i < len; i++)
    {
        queue = trls_queue_pos(g_trls_queue_head, i);
        CU_ASSERT_PTR_EQUAL(queue, g_trls_queue_arr[i]);
    }
}

void
test_trls_queue_entry(void)
{
    trls_queue_t head;
    trls_queue_t *queue;

    typedef struct trls_queue_test_node_s
    {
        trls_uint_t  value;
        trls_queue_t list;
    } trls_queue_test_node_t;

    trls_queue_test_node_t *p, node;
    node.value = 10;

    trls_queue_init(&head);
    trls_queue_insert_tail(&head, &node.list);

    p = trls_queue_entry(&node.list, trls_queue_test_node_t, list);

    CU_ASSERT_PTR_EQUAL(p, &node);
    CU_ASSERT_PTR_EQUAL(&p->list, &node.list);
    CU_ASSERT_EQUAL(p->value, 10);
}

void
test_trls_queue_insert_head(void)
{
    trls_queue_del(q4);
    trls_queue_del(q3);
    trls_queue_del(q2);

    CU_ASSERT_PTR_EQUAL(q1->next, g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(g_trls_queue_head->prev, q1);

    trls_queue_insert_head(g_trls_queue_head, q2);
    CU_ASSERT_PTR_EQUAL(q2->next, q1);
    CU_ASSERT_PTR_EQUAL(q2->prev, g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(g_trls_queue_head->next, q2);
    CU_ASSERT_PTR_EQUAL(g_trls_queue_head->prev, q1);
    CU_ASSERT_PTR_EQUAL(q1->next, g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(q1->prev, q2);

    trls_queue_del(q2);
}

void
test_trls_queue_insert_tail(void)
{
    trls_queue_insert_tail(g_trls_queue_head, q2);

    CU_ASSERT_PTR_EQUAL(q1->next, q2);
    CU_ASSERT_PTR_EQUAL(q1->prev, g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(q2->next, g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(q2->prev, q1);
    CU_ASSERT_PTR_EQUAL(g_trls_queue_head->next, q1);
    CU_ASSERT_PTR_EQUAL(g_trls_queue_head->prev, q2);

    trls_queue_del(q2);
    trls_queue_insert_tail(g_trls_queue_head, q3);
}

void
test_trls_queue_insert_prev(void)
{
    trls_queue_insert_prev(q3, q2);

    CU_ASSERT_PTR_EQUAL(q1->next, q2);
    CU_ASSERT_PTR_EQUAL(q2->next, q3);
    CU_ASSERT_PTR_EQUAL(q2->prev, q1);
    CU_ASSERT_PTR_EQUAL(q3->prev, q2);
}

void
test_trls_queue_insert_next(void)
{
    trls_queue_insert_next(q3, q4);

    CU_ASSERT_PTR_EQUAL(q3->next, q4);
    CU_ASSERT_PTR_EQUAL(q4->next, g_trls_queue_head);
    CU_ASSERT_PTR_EQUAL(q4->prev, q3);
}

void
test_trls_queue_insert_behind_head()
{
    trls_queue_del(q2);

    trls_queue_insert_behind_head(g_trls_queue_head, q2);

    CU_ASSERT_PTR_EQUAL(q1->next, q2);
    CU_ASSERT_PTR_EQUAL(q2->next, q3);
    CU_ASSERT_PTR_EQUAL(q2->prev, q1);
    CU_ASSERT_PTR_EQUAL(q3->prev, q2);
}

void
test_trls_queue_insert_before_tail()
{
    trls_queue_del(q4);

    trls_queue_insert_tail(g_trls_queue_head, q5);
    trls_queue_insert_before_tail(g_trls_queue_head, q4);

    CU_ASSERT_PTR_EQUAL(q3->next, q4);
    CU_ASSERT_PTR_EQUAL(q4->next, q5);
    CU_ASSERT_PTR_EQUAL(q4->prev, q3);
    CU_ASSERT_PTR_EQUAL(q5->prev, q4);
}

void
test_trls_queue_sort(void)
{
    //do nothing at present
}

int
trls_cunit_suite_queue_init(void)
{
    g_trls_queue_head = malloc(sizeof(trls_queue_t));
    if(NULL == g_trls_queue_head)
        return -1;

    g_trls_queue_n = malloc(sizeof(trls_queue_t));
    if(NULL == g_trls_queue_n)
        return -1;

    q1 = malloc(sizeof(trls_queue_t));
    if(NULL == q1)
        return -1;

    q2 = malloc(sizeof(trls_queue_t));
    if(NULL == q2)
        return -1;

    q3 = malloc(sizeof(trls_queue_t));
    if(NULL == q3)
        return -1;

    q4 = malloc(sizeof(trls_queue_t));
    if(NULL == q4)
        return -1;

    q5 = malloc(sizeof(trls_queue_t));
    if(NULL == q5)
        return -1;

    g_trls_queue_arr[0] = q1;
    g_trls_queue_arr[1] = q2;
    g_trls_queue_arr[2] = q3;
    g_trls_queue_arr[3] = q4;
    g_trls_queue_arr[4] = q5;

    return 0;
}

int
trls_cunit_suite_queue_clean(void)
{
    if(NULL != g_trls_queue_head)
    {
        free(g_trls_queue_head);
        g_trls_queue_head = NULL;
    }

    return 0;
}

void
trls_cunit_suite_queue_setup(void)
{
    return;
}

void
trls_cunit_suite_queue_teardown(void)
{
    return;
}


CU_TestInfo trls_cunit_test_queue_info[] =
{
    {"for trls_queue_init: ", test_trls_queue_init},
    {"for trls_queue_empty: ", test_trls_queue_empty},
    {"for trls_queue_sentinel: ", test_trls_queue_sentinel},
    {"for trls_queue_head: ", test_trls_queue_head},
    {"for trls_queue_last: ", test_trls_queue_last},
    {"for trls_queue_prev: ", test_trls_queue_prev},
    {"for trls_queue_next: ", test_trls_queue_next},
    {"for trls_queue_middle: ", test_trls_queue_middle},
    {"for trls_queue_del: ", test_trls_queue_del},
    {"for trls_queue_len: ", test_trls_queue_len},
    {"for trls_queue_split: ", test_trls_queue_split},
    {"for trls_queue_union: ", test_trls_queue_union},
    {"for trls_queue_tras: ", test_trls_queue_tras},
    {"for trls_queue_pos: ", test_trls_queue_pos},
    {"for trls_queue_entry: ", test_trls_queue_entry},
    {"for trls_queue_insert_head: ", test_trls_queue_insert_head},
    {"for trls_queue_insert_tail: ", test_trls_queue_insert_tail},
    {"for trls_queue_insert_prev: ", test_trls_queue_insert_prev},
    {"for trls_queue_insert_next: ", test_trls_queue_insert_next},
    {"for trls_queue_insert_behind_head: ", test_trls_queue_insert_behind_head},
    {"for trls_queue_insert_before_tail: ", test_trls_queue_insert_before_tail},
    {"for trls_queue_sort: ", test_trls_queue_sort},
    CU_TEST_INFO_NULL
};

CU_SuiteInfo trls_cunit_suite_queue_info[] =
{
    {"trls_cunit_suite_queue_info", trls_cunit_suite_queue_init, trls_cunit_suite_queue_clean,
                                    trls_cunit_suite_queue_setup, trls_cunit_suite_queue_teardown,
                                    &trls_cunit_test_queue_info[0]},
    CU_SUITE_INFO_NULL
};

void
trls_cunit_suite_queue_module(void)
{
    if(CUE_SUCCESS != CU_register_suites(trls_cunit_suite_queue_info))
    {
        fprintf(stderr, "Register suites failed: %s\n", CU_get_error_msg());
        exit(-1);
    }
}

