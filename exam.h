#ifndef EXAM_H
#define EXAM_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define EXAM_ASSERT_TRUE(cond) _exam_assert_true((cond), #cond, __FILE__, __LINE__)
#define EXAM_ASSERT_FALSE(cond) _exam_assert_false((cond), #cond, __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_PTR(a, b) _exam_assert_eq_ptr((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_PTR(a, b) _exam_assert_neq_ptr((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_NULL(ptr) _exam_assert_eq_ptr((ptr), NULL, __FILE__, __LINE__)
#define EXAM_ASSERT_NON_NULL(ptr) _exam_assert_neq_ptr((ptr), NULL, __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_INT(a, b) _exam_assert_eq_int((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_INT(a, b) _exam_assert_neq_int((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_UINT(a, b) _exam_assert_eq_uint((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_UINT(a, b) _exam_assert_neq_uint((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_FLOAT(a, b, eps) _exam_assert_eq_float((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_FLOAT(a, b, eps) _exam_assert_neq_float((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_DOUBLE(a, b, eps) _exam_assert_eq_double((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_DOUBLE(a, b, eps) _exam_assert_neq_double((a), (b),(eps), __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_STR(a, b) _exam_assert_eq_str((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_STR(a, b) _exam_assert_neq_str((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_MEM(a, b, size) _exam_assert_eq_mem((a), (b), (size), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_MEM(a, b, size) _exam_assert_neq_mem((a), (b), (size), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_RANGE_INT(x, min, max) _exam_assert_in_range_int((x), (min), (max), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_RANGE_INT(x, min, max) _exam_assert_not_in_range_int((x), (min), (max), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_RANGE_UINT(x, min, max) _exam_assert_in_range_uint((x), (min), (max), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_RANGE_UINT(x, min, max) _exam_assert_not_in_range_uint((x), (min), (max), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_RANGE_FLOAT(x, min, max, eps) _exam_assert_in_range_float((x), (min), (max), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_RANGE_FLOAT(x, min, max, eps) _exam_assert_not_in_range_float((x), (min), (max), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_RANGE_DOUBLE(x, min, max, eps) _exam_assert_in_range_double((x), (min), (max), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_RANGE_DOUBLE(x, min, max, eps) _exam_assert_not_in_range_double((x), (min), (max), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_ARR_INT(x, arr, count) _exam_assert_in_arr_int((x), (arr), (count), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_ARR_INT(x, arr, count) _exam_assert_not_in_arr_int((x), (arr), (count), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_ARR_UINT(x, arr, count) _exam_assert_in_arr_uint((x), (arr), (count), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_ARR_UINT(x, arr, count) _exam_assert_not_in_arr_uint((x), (arr), (count), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_ARR_FLOAT(x, arr, count, eps) _exam_assert_in_arr_float((x), (arr), (count), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_ARR_FLOAT(x, arr, count, eps) _exam_assert_not_in_arr_float((x), (arr), (count), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_ARR_DOUBLE(x, arr, count, eps) _exam_assert_in_arr_double((x), (arr), (count), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_ARR_DOUBLE(x, arr, count, eps) _exam_assert_not_in_arr_double((x), (arr), (count), (eps), __FILE__, __LINE__)

#define _EXAM_REG_NAME(category_name, test_name) \
    exam_reg_##category_name##_##test_name

#define _EXAM_DEF_NAME(category_name, test_name) \
    exam_def_##category_name##_##test_name

#define EXAM_DEFINE_TEST(category_name, test_name) \
    static void _EXAM_DEF_NAME(category_name, test_name)(void); \
    static void _EXAM_REG_NAME(category_name, test_name)(void) __attribute__((constructor)); \
    static void _EXAM_REG_NAME(category_name, test_name)(void) \
    { \
        struct exam_test test = { \
            .category = #category_name, \
            .name = #test_name, \
            .func = _EXAM_DEF_NAME(category_name, test_name), \
        }; \
        exam_list_append(&exam_state.test_list, &test); \
    } \
    static void _EXAM_DEF_NAME(category_name, test_name)(void)

enum exam_test_state
{
    EXAM_TEST_NONE = 0,
    EXAM_TEST_RUNNING,
    EXAM_TEST_PASSED,
    EXAM_TEST_FAILED,
    EXAM_TEST_CRASHED,
};

#ifndef EXAM_TEST_OUTPUT_SIZE
#define EXAM_TEST_OUTPUT_SIZE 1024
#endif

struct exam_test
{
    const char *category;
    const char *name;
    void (*func)(void);

    enum exam_test_state state;
    int exit_signal;

    char output[EXAM_TEST_OUTPUT_SIZE + 1];
    size_t output_size;
    bool output_truncated;
};

struct exam_test_list
{
    struct exam_test *data;
    size_t count;
    size_t capacity;
};

struct exam_filter
{
    const char *category_name;
    const char *test_name;
};

struct exam_state
{
    struct exam_test_list test_list;

    void (*on_start)(void);
    void (*on_finish)(void);
    void (*on_test_start)(const struct exam_test *test);
    void (*on_test_finish)(const struct exam_test *test);

    size_t passed;
    size_t failed;
    size_t crashed;
};

enum exam_color
{
    EXAM_COLOR_AUTO = 0,
    EXAM_COLOR_ALWAYS,
    EXAM_COLOR_NEVER,
};

enum exam_cli_action
{
    EXAM_ACTION_RUN = 0,
    EXAM_ACTION_LIST,
    EXAM_ACTION_HELP,
};

struct exam_cli_state
{
    size_t jobs;
    enum exam_cli_action action;
    enum exam_color color;
    struct exam_filter filter;
};

#ifdef __cplusplus
extern "C" {
#endif
extern void _exam_assert_true(bool result, const char *expression, const char *file, size_t line);
extern void _exam_assert_false(bool result, const char *expression, const char *file, size_t line);
extern void _exam_assert_eq_ptr(const void *a, const void *b, const char *file, size_t line);
extern void _exam_assert_neq_ptr(const void *a, const void *b, const char *file, size_t line);
extern void _exam_assert_eq_int(intmax_t a, intmax_t b, const char *file, size_t line);
extern void _exam_assert_neq_int(intmax_t a, intmax_t b, const char *file, size_t line);
extern void _exam_assert_eq_uint(uintmax_t a, uintmax_t b, const char *file, size_t line);
extern void _exam_assert_neq_uint(uintmax_t a, uintmax_t b, const char *file, size_t line);
extern void _exam_assert_eq_float(float a, float b, float eps, const char *file, size_t line);
extern void _exam_assert_neq_float(float a, float b, float eps, const char *file, size_t line);
extern void _exam_assert_eq_double(double a, double b, double eps, const char *file, size_t line);
extern void _exam_assert_neq_double(double a, double b, double eps, const char *file, size_t line);
extern void _exam_assert_eq_str(const char *a, const char *b, const char *file, size_t line);
extern void _exam_assert_neq_str(const char *a, const char *b, const char *file, size_t line);
extern void _exam_assert_neq_mem(const void *a, const void *b, size_t size, const char *file, size_t line);
extern void _exam_assert_eq_mem(const void *a, const void *b, size_t size, const char *file, size_t line);
extern void _exam_assert_in_range_int(intmax_t x, intmax_t min, intmax_t max, const char *file, size_t line);
extern void _exam_assert_not_in_range_int(intmax_t x, intmax_t min, intmax_t max, const char *file, size_t line);
extern void _exam_assert_in_range_uint(uintmax_t x, uintmax_t min, uintmax_t max, const char *file, size_t line);
extern void _exam_assert_not_in_range_uint(uintmax_t x, uintmax_t min, uintmax_t max, const char *file, size_t line);
extern void _exam_assert_in_range_float(float x, float min, float max, float eps, const char *file, size_t line);
extern void _exam_assert_not_in_range_float(float x, float min, float max, float eps, const char *file, size_t line);
extern void _exam_assert_in_range_double(double x, double min, double max, double eps, const char *file, size_t line);
extern void _exam_assert_not_in_range_double(double x, double min, double max, double eps, const char *file, size_t line);
extern void _exam_assert_in_arr_int(intmax_t x, const intmax_t *arr, size_t count, const char *file, size_t line);
extern void _exam_assert_not_in_arr_int(intmax_t x, const intmax_t *arr, size_t count, const char *file, size_t line);
extern void _exam_assert_in_arr_uint(uintmax_t x, const uintmax_t *arr, size_t count, const char *file, size_t line);
extern void _exam_assert_not_in_arr_uint(uintmax_t x, const uintmax_t *arr, size_t count, const char *file, size_t line);
extern void _exam_assert_in_arr_float(float x, const float *arr, size_t count, float eps, const char *file, size_t line);
extern void _exam_assert_not_in_arr_float(float x, const float *arr, size_t count, float eps, const char *file, size_t line);
extern void _exam_assert_in_arr_double(double x, const double *arr, size_t count, double eps, const char *file, size_t line);
extern void _exam_assert_not_in_arr_double(double x, const double *arr, size_t count, double eps, const char *file, size_t line);

extern struct exam_state exam_state;
extern bool exam_test_passes_filter(const struct exam_test *test, struct exam_filter filter);
extern void exam_run_tests(struct exam_test_list *list, struct exam_filter filter, size_t jobs);
extern void exam_list_append(struct exam_test_list *list, const struct exam_test *test);
extern void exam_list_destroy(struct exam_test_list *list);
extern void exam_list_sort(struct exam_test_list *list);

extern struct exam_cli_state exam_cli_state;
extern int exam_cli_main(int argc, char **argv);
#ifdef __cplusplus
}
#endif

#ifdef EXAM_SOURCE
#include <stdio.h> /* printf(), fprintf(), vfprintf(), fputc(), perror(), stdout, stderr */
#include <stdlib.h> /* malloc(), realloc(), free(), qsort(), exit(), strtoull(), EXIT_FAILURE */
#include <string.h> /* strcmp(), memcmp(), strerror() */
#include <stdarg.h> /* va_list, va_start(), va_end() */
#include <errno.h> /* errno */
#include <math.h> /*  isnan(), isinf(), isfinite() */

#ifdef __linux__
#include <unistd.h> /* isatty(), STDOUT_FILENO */
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#else
#error "Your platform is currently not supported"
#endif

struct exam_state exam_state = {0};

static int _exam_test_cmp(const void *a, const void *b);
static bool _exam_str_cmp(const char *a, const char *b);
static bool _exam_float_cmp(float a, float b, float eps);
static bool _exam_double_cmp(double a, double b, double eps);

static bool _exam_float_in_range(float x, float min, float max, float eps);
static bool _exam_double_in_range(double x, double min, double max, double eps);

static const char *_exam_str_repr(const char *str);

static void _exam_dief(const char *fmt, ...);
static void _exam_die_perror(const char *str);
static void _exam_fail_test(const char *file, size_t line, const char *fmt, ...);

void _exam_assert_true(bool res, const char *expression, const char *file, size_t line)
{
    if (!res)
        _exam_fail_test(file, line,
                        "%s is not true",
                        expression);
}

void _exam_assert_false(bool res, const char *expression, const char *file, size_t line)
{
    if (res)
        _exam_fail_test(file, line,
                        "%s is not false",
                        expression);
}

void _exam_assert_eq_ptr(const void *a, const void *b, const char *file, size_t line)
{
    if (a != b)
        _exam_fail_test(file, line,
                        "%p != %p",
                        a, b);
}

void _exam_assert_neq_ptr(const void *a, const void *b, const char *file, size_t line)
{
    if (a == b)
        _exam_fail_test(file, line,
                        "%p == %p",
                        a, b);
}

void _exam_assert_eq_int(intmax_t a, intmax_t b, const char *file, size_t line)
{
    if (a != b)
        _exam_fail_test(file, line,
                        "%jd != %jd",
                        a, b);
}

void _exam_assert_neq_int(intmax_t a, intmax_t b, const char *file, size_t line)
{
    if (a == b)
        _exam_fail_test(file, line,
                        "%jd == %jd",
                        a, b);
}

void _exam_assert_eq_uint(uintmax_t a, uintmax_t b, const char *file, size_t line)
{
    if (a != b)
        _exam_fail_test(file, line,
                        "%ju != %ju",
                        a, b);
}

void _exam_assert_neq_uint(uintmax_t a, uintmax_t b, const char *file, size_t line)
{
    if (a == b)
        _exam_fail_test(file, line,
                        "%ju == %ju",
                        a, b);
}

void _exam_assert_eq_float(float a, float b, float eps, const char *file, size_t line)
{
    if (!_exam_float_cmp(a, b, eps))
        _exam_fail_test(file, line,
                        "%.9g != %.9g",
                         a, b);
}

void _exam_assert_neq_float(float a, float b, float eps, const char *file, size_t line)
{
    if (_exam_float_cmp(a, b, eps))
        _exam_fail_test(file, line,
                        "%.9g == %.9g",
                        a, b);
}

void _exam_assert_eq_double(double a, double b, double eps, const char *file, size_t line)
{
    if (!_exam_double_cmp(a, b, eps))
        _exam_fail_test(file, line,
                        "%.17g != %.17g",
                        a, b);
}

void _exam_assert_neq_double(double a, double b, double eps, const char *file, size_t line)
{
    if (_exam_double_cmp(a, b, eps))
        _exam_fail_test(file, line,
                        "%.17g == %.17g",
                        a, b);
}

void _exam_assert_eq_str(const char *a, const char *b, const char *file, size_t line)
{
    if (!_exam_str_cmp(a, b))
        _exam_fail_test(file, line,
                        "\"%s\" != \"%s\"",
                        _exam_str_repr(a), _exam_str_repr(b));
}

void _exam_assert_neq_str(const char *a, const char *b, const char *file, size_t line)
{
    if (_exam_str_cmp(a, b))
        _exam_fail_test(file, line,
                        "%s == %s",
                         _exam_str_repr(a), _exam_str_repr(b));
}

void _exam_assert_eq_mem(const void *a, const void *b, size_t size, const char *file, size_t line)
{
    const unsigned char *expected = a;
    const unsigned char *actual = b;

    for (size_t i = 0; i < size; i ++) {
        if (expected[i] != actual[i])
            _exam_fail_test(file, line,
                            "memory differs at offset %zu: expected=0x%02x actual=0x%02x",
                            i, expected[i], actual[i]);
    }
}

void _exam_assert_neq_mem(const void *a, const void *b, size_t size, const char *file, size_t line)
{
    if (size == 0)
        return;

    if (memcmp(a, b, size) == 0)
        _exam_fail_test(file, line,
                        "memory regions are equal (%zu bytes)",
                        size);
}

void _exam_assert_in_range_int(intmax_t x, intmax_t min, intmax_t max, const char *file, size_t line)
{
    if (min > max)
        _exam_dief("invalid range [%jd, %jd]", min, max);

    if (x < min || x > max)
        _exam_fail_test(file, line,
                        "%jd is not within the range [%jd, %jd]",
                        x, min, max);
}

void _exam_assert_not_in_range_int(intmax_t x, intmax_t min, intmax_t max, const char *file, size_t line)
{
    if (min > max)
        _exam_dief("invalid range [%jd, %jd]", min, max);

    if (x >= min && x <= max)
        _exam_fail_test(file, line,
                        "%jd is within the range [%jd, %jd]",
                        x, min, max);
}

void _exam_assert_in_range_uint(uintmax_t x, uintmax_t min, uintmax_t max, const char *file, size_t line)
{
    if (min > max)
        _exam_dief("invalid range [%ju, %ju]", min, max);

    if (x < min || x > max)
        _exam_fail_test(file, line,
                        "%ju is not within the range [%ju, %ju]",
                        x, min, max);
}

void _exam_assert_not_in_range_uint(uintmax_t x, uintmax_t min, uintmax_t max, const char *file, size_t line)
{
    if (min > max)
        _exam_dief("invalid range [%ju, %ju]", min, max);

    if (x >= min && x <= max)
        _exam_fail_test(file, line, 
                        "%ju is within the range [%ju, %ju]",
                        x, min, max);
}

void _exam_assert_in_range_float(float x, float min, float max, float eps, const char *file, size_t line)
{
    if (min > max)
        _exam_dief("invalid range [%.9g, %.9g]", min, max);

    if (!_exam_float_in_range(x, min, max, eps))
        _exam_fail_test(file, line,
                        "%.9g is not within the range [%.9g, %.9g]",
                        x, min, max);
}

void _exam_assert_not_in_range_float(float x, float min, float max, float eps, const char *file, size_t line)
{
    if (min > max)
        _exam_dief("invalid range [%.9g, %.9g]", min, max);

    if (_exam_float_in_range(x, min, max, eps))
        _exam_fail_test(file, line,
                        "%.9g is within the range [%.9g, %.9g]",
                        x, min, max);
}

void _exam_assert_in_range_double(double x, double min, double max, double eps, const char *file, size_t line)
{
    if (min > max)
        _exam_dief("invalid range [%.17g, %.17g]", min, max);

    if (!_exam_double_in_range(x, min, max, eps))
        _exam_fail_test(file, line,
                        "%.17g is not within the range [%.17g, %.17g]",
                        x, min, max);
}

void _exam_assert_not_in_range_double(double x, double min, double max, double eps, const char *file, size_t line)
{
    if (min > max)
        _exam_dief("invalid range [%.17g, %.17g]", min, max);

    if (_exam_double_in_range(x, min, max, eps))
        _exam_fail_test(file, line,
                        "%.17g is within the range [%.17g, %.17g]",
                        x, min, max);
}

void _exam_assert_in_arr_int(intmax_t x, const intmax_t *arr, size_t count, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (arr[i] == x)
            return;
    }

    _exam_fail_test(file, line,
                    "%jd not in %p (count=%zu)",
                    x, (void*)arr, count);
}

void _exam_assert_not_in_arr_int(intmax_t x, const intmax_t *arr, size_t count, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (arr[i] == x)
            _exam_fail_test(file, line,
                            "%jd in %p (count=%zu)",
                            x, (void*)arr, count);
    }
}

void _exam_assert_in_arr_uint(uintmax_t x, const uintmax_t *arr, size_t count, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (arr[i] == x)
            return;
    }

    _exam_fail_test(file, line, 
                    "%ju not in %p (count=%zu)",
                    x, (void*)arr, count);
}

void _exam_assert_not_in_arr_uint(uintmax_t x, const uintmax_t *arr, size_t count, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (arr[i] == x)
            _exam_fail_test(file, line,
                            "%ju in %p (count=%zu)",
                            x, (void*)arr, count);
    }
}

void _exam_assert_in_arr_float(float x, const float *arr, size_t count, float eps, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (_exam_float_cmp(x, arr[i], eps))
            return;
    }

    _exam_fail_test(file, line,
                    "%.9g not in %p (count=%zu)",
                    x, (void*)arr, count);
}

void _exam_assert_not_in_arr_float(float x, const float *arr, size_t count, float eps, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (_exam_float_cmp(x, arr[i], eps))
            _exam_fail_test(file, line,
                            "%.9g in %p (count=%zu)",
                            x, (void*)arr, count);
    }
}

void _exam_assert_in_arr_double(double x, const double *arr, size_t count, double eps, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (_exam_double_cmp(x, arr[i], eps))
            return;
    }

    _exam_fail_test(file, line,
                    "%.17g not in %p (count=%zu)",
                    x, (void*)arr, count);
}

void _exam_assert_not_in_arr_double(double x, const double *arr, size_t count, double eps, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (_exam_double_cmp(x, arr[i], eps))
            _exam_fail_test(file, line,
                            "%.17g in %p (count=%zu)",
                            x, (void*)arr, count);
    }
}

struct exam_test_process
{
    pid_t pid;
    size_t test_index;
    int out_fd;
};

static struct exam_test_process _exam_start_test(struct exam_test *test, size_t idx);
static void _exam_finish_test(struct exam_test *test, int status, int out_fd);
static void _exam_read_output(struct exam_test *test, int out_fd);

void exam_run_tests(struct exam_test_list *list, struct exam_filter filter, size_t jobs)
{
    exam_state.passed = 0;
    exam_state.failed = 0;
    exam_state.crashed = 0;

    if (list->count == 0)
        return;

    if (exam_state.on_start)
        exam_state.on_start();

    if (jobs == 0) {
        long cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
        if (cpu_count <= 0)
            jobs = 1;
        else
            jobs = cpu_count;
    }
    if (jobs > list->count)
        jobs = list->count;

    struct exam_test_process *running = calloc(jobs, sizeof(*running));
    if (running == NULL)
        _exam_die_perror("calloc");

    size_t next_idx = 0;
    size_t running_count = 0;
    while (next_idx < list->count || running_count > 0) {
        while (running_count < jobs && next_idx < list->count) {
            size_t idx = next_idx++;
            struct exam_test *test = &list->data[idx];
            if (!exam_test_passes_filter(test, filter))
                continue;

            running[running_count++] = _exam_start_test(test, idx);
        }

        if (running_count == 0)
            break;

        int status;
        pid_t pid = waitpid(-1, &status, 0);
        if (pid == -1)
            _exam_die_perror("wait");

        bool found = false;
        for (size_t i = 0; i < running_count; ++i) {
            if (running[i].pid != pid)
                continue;

            struct exam_test *test = &list->data[running[i].test_index];
            _exam_finish_test(test, status, running[i].out_fd);

            running[i] = running[--running_count];
            found = true;
            break;
        }

        if (!found)
            _exam_dief("wait returned unknown child pid: %ld", (long)pid);
    }
    free(running);

    if (exam_state.on_finish)
        exam_state.on_finish();
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

void exam_list_append(struct exam_test_list *list, const struct exam_test *test)
{
    if (list->count == SIZE_MAX)
        _exam_dief("test list too large");

    size_t new_count = list->count + 1;
    if (list->data == NULL || new_count > list->capacity) {
        size_t new_cap = list->capacity;
        if (new_cap < 4) {
            new_cap = 4;
        } else {
            if (new_cap > SIZE_MAX / 2)
                _exam_dief("test list too large");

            new_cap *= 2;
        }
        if (new_cap < new_count)
            new_cap = new_count;
        if (new_cap > SIZE_MAX / sizeof(*list->data))
            _exam_dief("test list too large");

        struct exam_test *data = realloc(list->data, sizeof(*list->data) * new_cap);
        if (data == NULL)
            _exam_die_perror("realloc");

        list->data = data;
        list->capacity = new_cap;
    }

    list->data[list->count++] = *test;
}

void exam_list_destroy(struct exam_test_list *list)
{
    if (list->data == NULL)
        return;

    free(list->data);
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

void exam_list_sort(struct exam_test_list *list)
{
    qsort(list->data, list->count, sizeof(*list->data), _exam_test_cmp);
}

static struct exam_test_process _exam_start_test(struct exam_test *test, size_t idx)
{
    if (test->state != EXAM_TEST_NONE)
        _exam_dief("tried to run test with an unexpected state: %d",
                   test->state);

    if (exam_state.on_test_start)
        exam_state.on_test_start(test);

    int fildes[2];
    if (pipe(fildes) == -1)
        _exam_die_perror("pipe");

    test->state = EXAM_TEST_RUNNING;
    test->output[0] = '\0';
    test->output_size = 0;
    test->output_truncated = false;

    struct exam_test_process process = {0};
    process.test_index = idx;

    pid_t pid = fork();
    switch (pid) {
        case -1:
            _exam_die_perror("fork");
            break; // unreachable
        case 0:
            close(fildes[0]);
            if (dup2(fildes[1], STDOUT_FILENO) == -1)
                _exam_die_perror("dup2");
            if (dup2(fildes[1], STDERR_FILENO) == -1)
                _exam_die_perror("dup2");
            close(fildes[1]);

            test->func();
            fflush(stdout);
            fflush(stderr);
            _exit(EXIT_SUCCESS);
            break;
        default:
            close(fildes[1]);
            process.pid = pid;
            process.out_fd = fildes[0];
            break;
    }

    return process;
}

static void _exam_finish_test(struct exam_test *test, int status, int out_fd)
{
    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == EXIT_SUCCESS)
            test->state = EXAM_TEST_PASSED;
        else
            test->state = EXAM_TEST_FAILED;
    } else if (WIFSIGNALED(status)) {
        test->state = EXAM_TEST_CRASHED;
        test->exit_signal = WTERMSIG(status);
    } else {
        _exam_dief("unexpected wait status for test %s/%s",
                   test->category,
                   test->name);
    }

    _exam_read_output(test, out_fd);
    close(out_fd);

    switch (test->state) {
        case EXAM_TEST_PASSED:
            exam_state.passed++;
            break;
        case EXAM_TEST_FAILED:
            exam_state.failed++;
            break;
        case EXAM_TEST_CRASHED:
            exam_state.crashed++;
            break;
        default:
            _exam_dief("test finished with unexpected state: %d",
                       test->state);
    }

    if (exam_state.on_test_finish)
        exam_state.on_test_finish(test);
}

static void _exam_read_output(struct exam_test *test, int out_fd)
{
    char buf[256];
    for (;;) {
        ssize_t n = read(out_fd, buf, sizeof(buf));
        if (n == -1) {
            if (errno == EINTR)
                continue;
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                return;

            _exam_die_perror("read");
        }
        if (n == 0)
            return;

        if (n > 0) {
            size_t remaining = EXAM_TEST_OUTPUT_SIZE - test->output_size;
            size_t copy = n < (ssize_t)remaining ? (size_t)n : remaining;

            if (copy > 0) {
                memcpy(test->output + test->output_size, buf, copy);
                test->output_size += copy;
                test->output[test->output_size] = '\0';
            }

            if ((size_t)n > copy)
                test->output_truncated = true;
        }
    }
}

static void _exam_dief(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}

static void _exam_die_perror(const char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}

static void _exam_fail_test(const char *file, size_t line, const char *fmt, ...)
{
    fprintf(stderr, "[%s:%zu] ", file, line);

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}

static int _exam_test_cmp(const void *a, const void *b)
{
    const struct exam_test *test_a = a;
    const struct exam_test *test_b = b;
    int result = strcmp(test_a->category, test_b->category);
    if (result == 0)
        result = strcmp(test_a->name, test_b->name);
    return result;
}

static bool _exam_str_cmp(const char *a, const char *b)
{
    if (a == NULL || b == NULL)
        return a == b;

    return strcmp(a, b) == 0;
}

static bool _exam_float_cmp(float a, float b, float eps)
{
    if (!isfinite(eps) || eps < 0)
        _exam_dief("invalid epsilon: %.9g", eps);

    if (isnan(a) && isnan(b))
        return true;
    if (isinf(a) && isinf(b))
        return ((a < 0) == (b < 0));

    float diff = a - b;
    diff = (diff > 0 ? diff : -diff);
    if (isnan(diff) || isinf(diff))
        return false;
    if (diff <= eps)
        return true;

    float absA = (a > 0 ? a : -a);
    float absB = (b > 0 ? b : -b);
    float largest = (absA > absB ? absA : absB);
    return diff <= eps * largest;
}

static bool _exam_float_in_range(float x, float min, float max, float eps)
{
    if (!isfinite(eps) || eps < 0)
        _exam_dief("invalid epsilon: %.9g", eps);

    return (_exam_float_cmp(x, min, eps) || x > min) &&
           (_exam_float_cmp(x, max, eps) || x < max);
}

static bool _exam_double_cmp(double a, double b, double eps)
{
    if (!isfinite(eps) || eps < 0)
        _exam_dief("invalid epsilon: %.17g", eps);

    if (isnan(a) && isnan(b))
        return true;
    if (isinf(a) && isinf(b))
        return ((a < 0) == (b < 0));

    double diff = a - b;
    diff = (diff > 0 ? diff : -diff);
    if (isnan(diff) || isinf(diff))
        return false;
    if (diff <= eps)
        return true;

    double absA = (a > 0 ? a : -a);
    double absB = (b > 0 ? b : -b);
    double largest = (absA > absB ? absA : absB);
    return diff <= eps * largest;
}

static bool _exam_double_in_range(double x, double min, double max, double eps)
{
    if (!isfinite(eps) || eps < 0)
        _exam_dief("invalid epsilon: %.17g", eps);

    return (_exam_double_cmp(x, min, eps) || x > min) &&
           (_exam_double_cmp(x, max, eps) || x < max);
}

static const char *_exam_str_repr(const char *str)
{
    if (str == NULL)
        return "NULL";

    return str;
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

struct exam_cli_state exam_cli_state = {0};

static int _exam_cli_run();
static int _exam_cli_list();
static void _exam_cli_usage();

static void _exam_cli_on_finish();
static void _exam_cli_on_test_finish(const struct exam_test *test);

static void _exam_cli_test_output(const struct exam_test *test);
static const char *_exam_cli_color(const char *color);
static bool _exam_cli_is_option(const char *str, const char *short_name, const char *long_name);
static bool _exam_cli_is_color();

int exam_cli_main(int argc, char **argv)
{
    exam_list_sort(&exam_state.test_list);
    exam_state.on_finish = _exam_cli_on_finish;
    exam_state.on_test_finish = _exam_cli_on_test_finish;

    exam_cli_state = (struct exam_cli_state){0};

    int rc = EXIT_SUCCESS;
    for (int i = 1; i < argc; ++i) {
        if (_exam_cli_is_option(argv[i], "-j", "--jobs")) {
            size_t value = 0;

            if (i + 1 < argc && argv[i + 1][0] != '-') {
                const char *jobs_str = argv[++i];

                errno = 0;
                char *end;
                unsigned long long parsed = strtoull(jobs_str, &end, 10);
                if (errno == ERANGE || end == jobs_str || *end != '\0' || parsed > SIZE_MAX) {
                    fprintf(stderr, "invalid jobs count '%s'\n", jobs_str);
                    rc = EXIT_FAILURE;
                    goto cleanup;
                }

                value = (size_t)parsed;
            }

            exam_cli_state.jobs = value;
        } else if (_exam_cli_is_option(argv[i], "-l", "--list")) {
            exam_cli_state.action = EXAM_ACTION_LIST;
        } else if (_exam_cli_is_option(argv[i], NULL, "--color")) {
            if (i == argc - 1) {
                fprintf(stderr, "usage: --color WHEN (can be auto, always or never)\n");
                rc = EXIT_FAILURE;
                goto cleanup;
            }

            const char *color_str = argv[++i];
            if (strcmp(color_str, "auto") == 0) {
                exam_cli_state.color = EXAM_COLOR_AUTO;
            } else if (strcmp(color_str, "always") == 0) {
                exam_cli_state.color = EXAM_COLOR_ALWAYS;
            } else if (strcmp(color_str, "never") == 0) {
                exam_cli_state.color = EXAM_COLOR_NEVER;
            } else {
                fprintf(stderr,
                        "unknown color '%s'\n"
                        "usage: --color WHEN (can be auto, always or never)\n",
                        color_str);
                rc = EXIT_FAILURE;
                goto cleanup;
            }
        } else if (_exam_cli_is_option(argv[i], "-h", "--help")) {
            exam_cli_state.action = EXAM_ACTION_HELP;
        } else if (_exam_cli_is_option(argv[i], "-n", "--name")) {
            if (i == argc - 1) {
                fprintf(stderr, "usage: --name NAME\n");
                rc = EXIT_FAILURE;
                goto cleanup;
            }

            char *name = argv[++i];
            if (name[0] == '-') {
                fprintf(stderr, "usage: --name NAME\n");
                rc = EXIT_FAILURE;
                goto cleanup;
            }

            exam_cli_state.filter.test_name = name;
        } else if (_exam_cli_is_option(argv[i], "-c", "--category")) {
            if (i == argc - 1) {
                fprintf(stderr, "usage: --category CATEGORY\n");
                rc = EXIT_FAILURE;
                goto cleanup;
            }

            char *name = argv[++i];
            if (name[0] == '-') {
                fprintf(stderr, "usage: --category CATEGORY\n");
                rc = EXIT_FAILURE;
                goto cleanup;
            }

            exam_cli_state.filter.category_name = name;
        } else {
            fprintf(stderr, "unknown option '%s'\n", argv[i]);
            rc = EXIT_FAILURE;
            _exam_cli_usage();
            goto cleanup;
        }
    }

    switch (exam_cli_state.action) {
        case EXAM_ACTION_RUN:
            rc = _exam_cli_run();
            break;
        case EXAM_ACTION_LIST:
            rc = _exam_cli_list();
            break;
        case EXAM_ACTION_HELP:
            rc = EXIT_SUCCESS;
            _exam_cli_usage();
            break;
        default:
            rc = EXIT_FAILURE;
            fprintf(stderr, "unexpected action %d\n", exam_cli_state.action);
            break;
    }

cleanup:
    exam_list_destroy(&exam_state.test_list);
    return rc;
}

static int _exam_cli_run()
{
    exam_run_tests(&exam_state.test_list, exam_cli_state.filter, exam_cli_state.jobs);
    if (exam_state.failed > 0 || exam_state.crashed > 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static int _exam_cli_list()
{
    size_t found = 0;
    for (size_t i = 0; i < exam_state.test_list.count; ++i) {
        const struct exam_test *test = &exam_state.test_list.data[i];
        if (!exam_test_passes_filter(test, exam_cli_state.filter))
            continue;

        printf("%s%s%s/%s\n",
                _exam_cli_color(EXAM_CLI_CYAN),
                test->category,
                _exam_cli_color(EXAM_CLI_RESET),
                test->name);

        found ++;
    }

    printf("%zu tests found\n", found);
    return EXIT_SUCCESS;
}

static void _exam_cli_usage()
{
    printf("usage: "EXAM_CLI_NAME" [options] [filter...]\n"
           "options:\n"
           "    -j, --jobs N        run up to N jobs at once\n"
           "    -l, --list          list available tests\n"
           "        --color WHEN    colorize output: auto, always, never\n"
           "    -h, --help          show this message\n"
           "filters:\n"
           "    -n, --name NAME          test name\n"
           "    -c, --category CATEGORY  category name\n");
}

static void _exam_cli_on_finish()
{
    fprintf(stdout,
            "%zu passed, %zu failed, %zu crashed\n",
            exam_state.passed,
            exam_state.failed,
            exam_state.crashed);
}

static void _exam_cli_on_test_finish(const struct exam_test *test)
{
    switch(test->state) {
        case EXAM_TEST_PASSED:
            fprintf(stdout,
                    "%s[PASS] %s/%s%s\n",
                    _exam_cli_color(EXAM_CLI_GREEN),
                    test->category,
                    test->name,
                    _exam_cli_color(EXAM_CLI_RESET));
            break;
        case EXAM_TEST_FAILED:
            fprintf(stderr,
                    "%s[FAIL] %s/%s%s\n",
                    _exam_cli_color(EXAM_CLI_RED),
                    test->category,
                    test->name,
                    _exam_cli_color(EXAM_CLI_RESET));
            _exam_cli_test_output(test);
            break;
        case EXAM_TEST_CRASHED:
            fprintf(stderr,
                    "%s[CRASH] %s/%s (signal %d)%s\n",
                    _exam_cli_color(EXAM_CLI_YELLOW),
                    test->category,
                    test->name,
                    test->exit_signal,
                    _exam_cli_color(EXAM_CLI_RESET));
            _exam_cli_test_output(test);
            break;
        default:
            fprintf(stderr,
                    "%s unexpected state (%d)\n",
                    test->name,
                    test->state);
            break;
    }

}

static void _exam_cli_test_output(const struct exam_test *test)
{
    if (test->output_size <= 0)
        return;

    const char *color = EXAM_CLI_RED;
    if (test->state == EXAM_TEST_CRASHED)
        color = EXAM_CLI_YELLOW;

    fputs(color, stderr);
    fputc('\t', stderr);
    for (size_t i = 0; i < test->output_size; i++) {
        char ch = test->output[i];
        fputc(ch, stderr);
        if (ch == '\n' && i != test->output_size - 1)
            fputc('\t', stderr);
    }

    if (test->output_truncated) {
        if (test->output[test->output_size - 1] != '\n')
            fputc('\n', stderr);
        fputs("\t...\n", stderr);
    }

    fputs(EXAM_CLI_RESET, stderr);
}

static const char *_exam_cli_color(const char *color)
{
    if (_exam_cli_is_color())
        return color;

    return "";
}

static bool _exam_cli_is_option(const char *str, const char *short_name, const char *long_name)
{
    if (str == NULL)
        return false;

    if (short_name != NULL && strcmp(str, short_name) == 0)
        return true;
    if (long_name != NULL && strcmp(str, long_name) == 0)
        return true;

    return false;
}

static bool _exam_cli_is_color()
{
    if (exam_cli_state.color == EXAM_COLOR_NEVER)
        return false;
    if (exam_cli_state.color == EXAM_COLOR_ALWAYS)
        return true;

    return isatty(STDOUT_FILENO) || isatty(STDERR_FILENO);
}
#endif /* EXAM_SOURCE */

#ifdef EXAM_SHORT_NAMES
#define ASSERT_TRUE EXAM_ASSERT_TRUE
#define ASSERT_FALSE EXAM_ASSERT_FALSE
#define ASSERT_EQ_PTR EXAM_ASSERT_EQ_PTR
#define ASSERT_NEQ_PTR EXAM_ASSERT_NEQ_PTR
#define ASSERT_NULL EXAM_ASSERT_NULL
#define ASSERT_NON_NULL EXAM_ASSERT_NON_NULL
#define ASSERT_EQ_INT EXAM_ASSERT_EQ_INT
#define ASSERT_NEQ_INT EXAM_ASSERT_NEQ_INT
#define ASSERT_EQ_UINT EXAM_ASSERT_EQ_UINT
#define ASSERT_NEQ_UINT EXAM_ASSERT_NEQ_UINT
#define ASSERT_EQ_FLOAT EXAM_ASSERT_EQ_FLOAT
#define ASSERT_NEQ_FLOAT EXAM_ASSERT_NEQ_FLOAT
#define ASSERT_EQ_DOUBLE EXAM_ASSERT_EQ_DOUBLE
#define ASSERT_NEQ_DOUBLE EXAM_ASSERT_NEQ_DOUBLE
#define ASSERT_EQ_STR EXAM_ASSERT_EQ_STR
#define ASSERT_NEQ_STR EXAM_ASSERT_NEQ_STR
#define ASSERT_EQ_MEM EXAM_ASSERT_EQ_MEM
#define ASSERT_NEQ_MEM EXAM_ASSERT_NEQ_MEM
#define ASSERT_IN_RANGE_INT EXAM_ASSERT_IN_RANGE_INT
#define ASSERT_NOT_IN_RANGE_INT EXAM_ASSERT_NOT_IN_RANGE_INT
#define ASSERT_IN_RANGE_UINT EXAM_ASSERT_IN_RANGE_UINT
#define ASSERT_NOT_IN_RANGE_UINT EXAM_ASSERT_NOT_IN_RANGE_UINT
#define ASSERT_IN_RANGE_FLOAT EXAM_ASSERT_IN_RANGE_FLOAT
#define ASSERT_NOT_IN_RANGE_FLOAT EXAM_ASSERT_NOT_IN_RANGE_FLOAT
#define ASSERT_IN_RANGE_DOUBLE EXAM_ASSERT_IN_RANGE_DOUBLE
#define ASSERT_NOT_IN_RANGE_DOUBLE EXAM_ASSERT_NOT_IN_RANGE_DOUBLE
#define ASSERT_IN_ARR_INT EXAM_ASSERT_IN_ARR_INT
#define ASSERT_NOT_IN_ARR_INT EXAM_ASSERT_NOT_IN_ARR_INT
#define ASSERT_IN_ARR_UINT EXAM_ASSERT_IN_ARR_UINT
#define ASSERT_NOT_IN_ARR_UINT EXAM_ASSERT_NOT_IN_ARR_UINT
#define ASSERT_IN_ARR_FLOAT EXAM_ASSERT_IN_ARR_FLOAT
#define ASSERT_NOT_IN_ARR_FLOAT EXAM_ASSERT_NOT_IN_ARR_FLOAT
#define ASSERT_IN_ARR_DOUBLE EXAM_ASSERT_IN_ARR_DOUBLE
#define ASSERT_NOT_IN_ARR_DOUBLE EXAM_ASSERT_NOT_IN_ARR_DOUBLE

#define DEFINE_TEST EXAM_DEFINE_TEST
#endif /* EXAM_SHORT_NAMES */
#endif /* EXAM_H */
