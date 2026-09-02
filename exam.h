#ifndef EXAM_H
#define EXAM_H

#include <stdio.h> /* printf(), perror() */
#include <stdlib.h> /* exit(), EXIT_FAILURE */
#include <string.h> /* strcmp() */
#include <stdarg.h> /* va_list, va_start(), va_end() */
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
    int exit_signal; /* in case state = EXAM_TEST_CRASHED */
};

struct exam_filter
{
    char *category_name;
    char *test_name;
};

struct exam_state
{
    struct exam_test *tests;
    size_t tests_count;
    size_t tests_capacity;
    size_t passed;
    size_t failed;
    size_t crashed;
};

struct exam_cli_state
{
    struct exam_filter filter;
    bool no_color;
};

#ifdef __cplusplus
extern "C" {
#endif
extern struct exam_state exam_state;
extern bool exam_test_passes_filter(const struct exam_test *test, struct exam_filter filter);
extern void exam_sort_tests(struct exam_test *tests, size_t count);
extern void exam_run_tests(struct exam_test *tests, size_t count, struct exam_filter options);
extern void exam_run_test(struct exam_test *test);
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

static void exam_dief(const char *fmt, ...);
static void exam_die_errno(const char *str);
static int exam_test_compare(const void *a, const void *b);

void exam_run_tests(struct exam_test *tests, size_t count, struct exam_filter filter)
{
    for (size_t i = 0; i < count; i ++) {
        if (!exam_test_passes_filter(&tests[i], filter))
            continue;

        exam_run_test(&tests[i]);
    }
}

void exam_run_test(struct exam_test *test)
{
    if (test->state != EXAM_TEST_NONE)
        exam_dief("tried to run test with an unexpected state: %d\n", test->state);

    test->state = EXAM_TEST_RUNNING;

    pid_t pid = fork();
    if (pid == -1)
        exam_die_errno("fork");

    if (pid == 0) {
        test->func();
        _exit(EXIT_SUCCESS);
    }

    int status;
    if (waitpid(pid, &status, 0) == -1)
        exam_die_errno("waitpid");

    if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        if (exit_status == EXIT_SUCCESS)
            test->state = EXAM_TEST_PASSED;
        else
            test->state = EXAM_TEST_FAILED;
    }

    if (WIFSIGNALED(status)) {
        int signal = WTERMSIG(status);
        test->state = EXAM_TEST_CRASHED;
        test->exit_signal = signal;
    }
}

bool exam_test_passes_filter(const struct exam_test *test, struct exam_filter filter)
{
    bool out = true;

    const char *category_name = filter.category_name;
    if (category_name != NULL)
        out = out && (test->category != NULL &&
                      strcmp(test->category, category_name) == 0);

    const char *test_name = filter.test_name;
    if (test_name != NULL)
        out = out && (test->name != NULL &&
                     strcmp(test->name, test_name) == 0);

    return out;
}

void exam_sort_tests(struct exam_test *tests, size_t count)
{
    qsort(tests, count, sizeof(*tests), exam_test_compare);
}


static void exam_dief(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

static void exam_die_errno(const char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}

static int exam_test_compare(const void *a, const void *b)
{
    const struct exam_test *test_a = a;
    const struct exam_test *test_b = b;
    int result = strcmp(test_a->category, test_b->category);
    if (result == 0)
        result = strcmp(test_a->name, test_b->name);
    return result;
}

/* Cli */
#ifndef EXAM_CLI_NAME
#define EXAM_CLI_NAME "exam"
#endif

#define EXAM_CLI_RESET  "\033[0m"
#define EXAM_CLI_RED    "\033[31m"
#define EXAM_CLI_GREEN  "\033[32m"
#define EXAM_CLI_YELLOW "\033[33m"
#define EXAM_CLI_CYAN   "\033[36m"

static struct exam_cli_state exam_cli_state = {0};

static void exam_cli_cmd_run();
static void exam_cli_cmd_ls();
static void exam_cli_usage();
static const char *exam_cli_color(const char *color);

int exam_cli_main(int argc, char **argv)
{
    exam_sort_tests(exam_state.tests, exam_state.tests_count);

    /* options */
    int command_count = 1;
    for (int i = 1; i < argc; i ++) {
        if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--test-name") == 0) {
            if (i == argc - 1 || argv[i + 1][0] == '-')
                exam_dief("%sexpected name%s\n",
                          exam_cli_color(EXAM_CLI_RED),
                          exam_cli_color(EXAM_CLI_RESET));

            exam_cli_state.filter.test_name = argv[++i];
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            exam_cli_usage();
            exit(EXIT_SUCCESS);
        } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--category") == 0) {
            if (i == argc - 1 || argv[i + 1][0] == '-')
                exam_dief("%sexpected category%s\n",
                          exam_cli_color(EXAM_CLI_RED),
                          exam_cli_color(EXAM_CLI_RESET));

            exam_cli_state.filter.category_name = argv[++i];
        } else if (strcmp(argv[i], "--no-color") == 0) {
            exam_cli_state.no_color = true;
        } else if (argv[i][0] == '-') {
            exam_cli_usage();
            exam_dief("%sunknown option '%s'%s\n",
                      exam_cli_color(EXAM_CLI_RED),
                      argv[i],
                      exam_cli_color(EXAM_CLI_RESET));
            exit(EXIT_FAILURE);
        } else {
            argv[command_count++] = argv[i];
        }
    }

    if (command_count != 2) {
        exam_cli_usage();
        exam_dief("%sexpected only one command, but got %d%s\n",
                  exam_cli_color(EXAM_CLI_RED),
                  command_count - 1,
                  exam_cli_color(EXAM_CLI_RESET));
    }

    /* commands */
    argc = command_count;
    for (int i = 1; i < argc; i ++) {
        if (strcmp(argv[i], "run") == 0) {
            exam_cli_cmd_run();
        } else if (strcmp(argv[i], "ls") == 0) {
            exam_cli_cmd_ls();
        } else {
            exam_cli_usage();
            exam_dief("%sunknown command '%s'%s\n",
                      exam_cli_color(EXAM_CLI_RED),
                      argv[i],
                      exam_cli_color(EXAM_CLI_RESET));
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}

static void exam_cli_cmd_run()
{
    exam_run_tests(exam_state.tests, exam_state.tests_count, exam_cli_state.filter);

    for (size_t i = 0; i < exam_state.tests_count; i++) {
        struct exam_test *test = &exam_state.tests[i];
        if (!exam_test_passes_filter(test, exam_cli_state.filter))
            continue;

        switch(test->state) {
            case EXAM_TEST_PASSED:
                exam_state.passed ++;
                fprintf(stdout,
                        "%s[PASS] %s/%s%s\n",
                        exam_cli_color(EXAM_CLI_GREEN),
                        test->category,
                        test->name,
                        exam_cli_color(EXAM_CLI_RESET));
                break;
            case EXAM_TEST_FAILED:
                exam_state.failed ++;
                fprintf(stderr,
                        "%s[FAIL %s:%zu] %s/%s%s\n",
                        exam_cli_color(EXAM_CLI_RED),
                        test->file,
                        test->line,
                        test->category,
                        test->name,
                        exam_cli_color(EXAM_CLI_RESET));
                break;
            case EXAM_TEST_CRASHED:
                exam_state.crashed ++;
                fprintf(stderr,
                        "%s[CRASH %s:%zu] %s/%s (signal %d)%s\n",
                        exam_cli_color(EXAM_CLI_YELLOW),
                        test->file,
                        test->line,
                        test->category,
                        test->name,
                        test->exit_signal,
                        exam_cli_color(EXAM_CLI_RESET));
                break;
            default:
                fprintf(stderr,
                        "%s unexpected state (%d)\n",
                        test->name,
                        test->state);
                break;
        }

    }

    fprintf(stdout,
            "%zu passed, %zu failed, %zu crashed\n",
            exam_state.passed,
            exam_state.failed,
            exam_state.crashed);

    if (exam_state.failed > 0 || exam_state.crashed > 0)
        exit(EXIT_FAILURE);
    else
        exit(EXIT_SUCCESS);
}

static void exam_cli_cmd_ls()
{
    size_t found = 0;
    for (size_t i = 0; i < exam_state.tests_count; i++) {
        const struct exam_test *test = &exam_state.tests[i];
        if (!exam_test_passes_filter(test, exam_cli_state.filter))
            continue;

        printf("%s%s%s/%s\n",
                exam_cli_color(EXAM_CLI_CYAN),
                test->category,
                exam_cli_color(EXAM_CLI_RESET),
                test->name);

        found ++;
    }

    printf("%zu tests found\n", found);
    exit(EXIT_SUCCESS);
}

static void exam_cli_usage()
{
    printf("%s"EXAM_CLI_NAME"%s - Find and run unit tests\n"
           "%susage%s:\n"
           "     %s"EXAM_CLI_NAME" run%s\n"
           "     %s"EXAM_CLI_NAME" ls%s\n"
           "\n"
           "%soptions%s:\n"
           "    %s-t, --test-name <name>%s\n"
           "                  filter by test name\n"
           "    %s-c, --category <name>%s\n"
           "                  filter by category\n"
           "    %s--no-color%s    don't display using colors\n"
           "    %s-h, --help%s    show this message\n",
           exam_cli_color(EXAM_CLI_GREEN), /* exam */
           exam_cli_color(EXAM_CLI_RESET),
           exam_cli_color(EXAM_CLI_YELLOW), /* usage */
           exam_cli_color(EXAM_CLI_RESET),
           exam_cli_color(EXAM_CLI_GREEN), /* run */
           exam_cli_color(EXAM_CLI_RESET),
           exam_cli_color(EXAM_CLI_GREEN), /* ls */
           exam_cli_color(EXAM_CLI_RESET),
           exam_cli_color(EXAM_CLI_YELLOW), /* options */
           exam_cli_color(EXAM_CLI_RESET),
           exam_cli_color(EXAM_CLI_GREEN), /* -t, --test-name */
           exam_cli_color(EXAM_CLI_RESET),
           exam_cli_color(EXAM_CLI_GREEN), /* -c, --category */
           exam_cli_color(EXAM_CLI_RESET),
           exam_cli_color(EXAM_CLI_GREEN), /* --no-color */
           exam_cli_color(EXAM_CLI_RESET),
           exam_cli_color(EXAM_CLI_GREEN), /* -h, --help */
           exam_cli_color(EXAM_CLI_RESET));
}

static const char *exam_cli_color(const char *color)
{
    if (exam_cli_state.no_color)
        return "";

    return color;
}
#endif /* EXAM_SOURCE */
