#include "trls_cunit.h"
#include "trls_config.h"


void
test_trls_queue_init(void)
{
    trls_queue_t  queue;

    trls_queue_init(&queue);

    CU_ASSERT_PTR_EQUAL(queue.prev, queue.next);
    CU_ASSERT_PTR_EQUAL(queue.prev, &queue);
}

void
test_trls_queue_empty(void)
{
    trls_queue_t  queue;

    trls_queue_init(&queue);

    CU_ASSERT_EQUAL(trls_queue_empty(&queue), 1);
}


int
trls_cunit_suite_queue_init(void)
{
    return 0;
}

int
trls_cunit_suite_queue_clean(void)
{
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

