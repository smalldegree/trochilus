#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include "trls_cunit.h"


#define TRLS_CUNIT_RESULT_FILE "trls_cunit_result_file"


extern void trls_cunit_suite_queue_module(void);


typedef void (*trls_cunit_suite)(void);

trls_cunit_suite g_trls_cunit_suites[] =
{
    trls_cunit_suite_queue_module
};


static void
trls_cunit_registry(void)
{
    if(CUE_SUCCESS != CU_initialize_registry())
    {
        printf("trls_cunit_registry error: %d.\n", CU_get_error());
        exit(0);
    }

    if(NULL == CU_get_registry())
    {
        printf("trls_cunit_registry failed.\n");
        exit(0);
    }

    assert(!CU_is_test_running());
}

static void
trls_cunit_process_auto_mode(void)
{
    CU_ErrorAction   error_action;
    CU_BasicRunMode  mode;

    error_action = CUEA_FAIL;
    mode = CU_BRM_VERBOSE;

    CU_basic_set_mode(mode);
    CU_set_error_action(error_action);
    CU_automated_run_tests();
}

static void
trls_cunit_process_basic_mode(void)
{
    CU_ErrorAction   error_action;
    CU_BasicRunMode  mode;

    error_action = CUEA_FAIL;
    mode = CU_BRM_VERBOSE;

    CU_basic_set_mode(mode);
    CU_set_error_action(error_action);

    printf("\n");
    printf("TrlsTests completed @[%d].\n", CU_basic_run_tests());
}

static void
trls_cunit_process_console_mode(void)
{
    CU_console_run_tests();
}

static void
trls_cunit_help_msg(void)
{
    printf("Usage: trls_cunit [options]\n");
    printf("       -a : trls cunit process auto mode\n");
    printf("       -b : trls cunit process basic mode\n");
    printf("       -c : trls cunit process console mode\n");
    printf("       -h : trls cunit help message\n");
    printf("       -? : trls cunit help message\n");
}

static void
trls_cunit_parse_options(int argc, char **argv)
{
    int  res;

    while(-1 != (res = getopt(argc, argv, "abch?")))
    {
        switch(res)
        {
            case 'a':
                 trls_cunit_process_auto_mode();
                 break;
            case 'b':
                 trls_cunit_process_basic_mode();
                 break;
            case 'c':
                 trls_cunit_process_console_mode();
                 break;
            case 'h':
            case '?':
                 trls_cunit_help_msg();
                 break;
            default:
                 break;
        }
    }
}

int
main(int argc, char **argv)
{
    int  i;

    setvbuf(stdout, NULL, _IONBF, 0);

    trls_cunit_registry();

    CU_set_error_action(CUEA_ABORT);
    CU_set_output_filename(TRLS_CUNIT_RESULT_FILE);
    CU_list_tests_to_file();

    for(i = 0; i < sizeof(g_trls_cunit_suites) / sizeof(trls_cunit_suite); i++)
        g_trls_cunit_suites[i]();

    if(1 == argc)
        trls_cunit_process_basic_mode();
    else
        trls_cunit_parse_options(argc, argv);

    CU_cleanup_registry();

    return 0;
}

