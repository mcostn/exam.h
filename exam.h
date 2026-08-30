#ifndef EXAM_H
#define EXAM_H

#include <stdio.h> /* printf() */
#include <stdlib.h> /* exit(), EXIT_FAILURE */
#include <string.h> /* strcmp() */
#include <stdbool.h>

#ifdef EXAM_SHORT_NAMES
#define ASSERT EXAM_ASSERT
#define ASSERT_TRUE EXAM_ASSERT_TRUE
#define ASSERT_FALSE EXAM_ASSERT_FALSE
#define ASSERT_NULL EXAM_ASSERT_NULL
#define ASSERT_NOT_NULL EXAM_ASSERT_NOT_NULL
#define ASSERT_EQ_INT EXAM_ASSERT_EQ_INT
#define ASSERT_EQ_UINT EXAM_ASSERT_EQ_UINT
#define ASSERT_EQ_FLOAT EXAM_ASSERT_EQ_FLOAT
#define ASSERT_EQ_DOUBLE EXAM_ASSERT_EQ_DOUBLE
#define ASSERT_EQ_STR EXAM_ASSERT_EQ_STR

#define DEFINE_TEST EXAM_DEFINE_TEST
#endif /* EXAM_SHORT_NAMES */

#define EXAM_ASSERT(cond) \
    do { \
        if (!(cond)) { \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define EXAM_ASSERT_TRUE(cond) EXAM_ASSERT(cond)
#define EXAM_ASSERT_FALSE(cond) EXAM_ASSERT(!(cond))
#define EXAM_ASSERT_NULL(p) EXAM_ASSERT((p) == NULL)
#define EXAM_ASSERT_NOT_NULL(p) EXAM_ASSERT((p) != NULL)
#define EXAM_ASSERT_EQ_INT(val, exp) EXAM_ASSERT((int)(val) == (int)exp)
#define EXAM_ASSERT_EQ_UINT(val, exp) EXAM_ASSERT((unsigned int)(val) == (unsigned int)exp)
#define EXAM_ASSERT_EQ_FLOAT(val, exp) EXAM_ASSERT((float)(val) == (float)exp)
#define EXAM_ASSERT_EQ_DOUBLE(val, exp) EXAM_ASSERT((double)(val) == (double)exp)
#define EXAM_ASSERT_EQ_STR(val, exp) EXAM_ASSERT((val) != NULL && (exp) != NULL && strcmp((val), (exp)) == 0)

#define EXAM_DEFINE_TEST(category_name, test_name) \
    static void exam_def_##category_name##_##test_name(void); \
    static void exam_reg_##category_name##_##test_name(void) __attribute__((constructor)); \
    static void exam_reg_##category_name##_##test_name(void) \
    { \
        size_t idx = exam_state.tests_count++; \
        if (exam_state.tests == NULL || exam_state.tests_count > exam_state.tests_capacity) { \
            size_t min_cap = exam_state.tests_count; \
            if (min_cap < 4) min_cap = 4; \
            else min_cap = exam_state.tests_capacity * 2; \
            exam_state.tests_capacity = min_cap; \
            exam_state.tests = realloc(exam_state.tests, sizeof(*exam_state.tests) * exam_state.tests_capacity); \
        } \
        exam_state.tests[idx].category = #category_name;\
        exam_state.tests[idx].name = #test_name; \
        exam_state.tests[idx].func = exam_def_##category_name##_##test_name; \
        exam_state.tests[idx].file = __FILE__; \
        exam_state.tests[idx].line = __LINE__; \
    } \
    static void exam_def_##category_name##_##test_name(void)

enum exam_test_state
{
    EXAM_TEST_NONE = 0,
    EXAM_TEST_RUNNING,
    EXAM_TEST_PASSED,
    EXAM_TEST_FAILED,
    EXAM_TEST_CRASHED,
};

struct exam_test
{
    char *category;
    char *name;
    void (*func)(void);
    char *file;
    size_t line;
    enum exam_test_state state;
    int exit_signal; // in case state = EXAM_TEST_CRASHED
};

struct exam_state
{
    struct exam_test *tests;
    size_t tests_count;
    size_t tests_capacity;
};

struct exam_cli_state
{
    char *category;
};

#ifdef __cplusplus
extern "C" {
#endif
extern struct exam_state exam_state;
extern int exam_run_test(struct exam_test *test);
extern int exam_cli_main(int argc, char **argv);
#ifdef __cplusplus
}
#endif
#endif /* EXAM_H */

#ifdef EXAM_SOURCE
#ifdef __linux__
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#else
#error "Your platform is currently not supported"
#endif

struct exam_state exam_state = {0};

int exam_run_test(struct exam_test *test)
{
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        test->func();
        _exit(EXIT_SUCCESS);
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        if (exit_status == EXIT_SUCCESS)
            test->state = EXAM_TEST_PASSED;
        else
            test->state = EXAM_TEST_FAILED;
        return EXIT_SUCCESS;
    }

    if (WIFSIGNALED(status)) {
        int signal = WTERMSIG(status);
        test->state = EXAM_TEST_CRASHED;
        test->exit_signal = signal;
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

static struct exam_cli_state cli_state = {0};
static void exam_cli_cmd_run();
static void exam_cli_cmd_ls();
static void exam_cli_cmd_help();
static void exam_cli_usage();

int exam_cli_main(int argc, char **argv)
{
    if (argc == 1) {
        exam_cli_usage();
        return EXIT_FAILURE;
    }

    // options
    for (int i = 1; i < argc; i ++) {
        if (argv[i][0] != '-') continue;

        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            exam_cli_cmd_help();
        } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--category") == 0) {
            if (i == argc - 1 || argv[i + 1][0] == '-') {
                fprintf(stderr, "expected category\n");
                exit(EXIT_FAILURE);
            }
            cli_state.category = argv[++i];
        } else {
            fprintf(stderr, "unknown option %s\n", argv[i]);
            exam_cli_usage();
            exit(EXIT_FAILURE);
        }
    }

    // commands
    for (int i = 1; i < argc; i ++) {
        if (argv[i][0] == '-') continue;

        if (strcmp(argv[i], "run") == 0) {
            exam_cli_cmd_run();
        } else if (strcmp(argv[i], "ls") == 0) {
            exam_cli_cmd_ls();
        } else {
            fprintf(stderr, "unknown command %s\n", argv[i]);
            exam_cli_usage();
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}

static void exam_cli_cmd_run()
{
    const char *category = cli_state.category;
    for (size_t i = 0; i < exam_state.tests_count; i++) {
        if (category != NULL && strcmp(exam_state.tests[i].category, category) != 0)
            continue;

        struct exam_test *test = &exam_state.tests[i];
        exam_run_test(test);
        switch(test->state) {
            case EXAM_TEST_PASSED:
                fprintf(stdout, "%s passed\n", test->name);
                break;
            case EXAM_TEST_FAILED:
                fprintf(stderr, "%s failed\n", test->name);
                break;
            case EXAM_TEST_CRASHED:
                fprintf(stderr, "%s crashed (signal %d)\n", test->name, test->exit_signal);
                break;
            default:
                fprintf(stderr, "%s unexpected state (%d)\n", test->name, test->state);
                break;
        }
    }

    exit(EXIT_SUCCESS);
}

static void exam_cli_cmd_ls()
{
    size_t found = 0;
    const char *category = cli_state.category;
    for (size_t i = 0; i < exam_state.tests_count; i++) {
        if (category != NULL && strcmp(exam_state.tests[i].category, category) != 0)
            continue;

        printf("%s (category=%s)\n", exam_state.tests[i].name, exam_state.tests[i].category);
        found ++;
    }
    printf("%ld tests found\n", found);
    exit(EXIT_SUCCESS);
}

static void exam_cli_cmd_help()
{
    exam_cli_usage();
    exit(EXIT_SUCCESS);
}

static void exam_cli_usage()
{
    printf("exam - Show and run unit tests\n"
           "usage: exam run [-c|--category] [<category_name>]\n"
           "       exam ls [-c|--category] [<category_name>]\n"
           "\n"
           "options:\n"
           "    -h, --help    show this message\n");
}
#endif /* EXAM_SOURCE */
