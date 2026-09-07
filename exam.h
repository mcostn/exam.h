#ifndef EXAM_H
#define EXAM_H

#include <stdio.h> /* printf(), perror() */
#include <stdlib.h> /* malloc(), exit(), EXIT_FAILURE */
#include <string.h> /* strcmp(), memcmp() */
#include <stdarg.h> /* va_list, va_start(), va_end() */
#include <stdbool.h> /* bool, true, false */
#include <stdint.h> /* intmax_t, uintmax_t */
#include <math.h> /*  isnan(), isinf() */

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

struct exam_test
{
    const char *category;
    const char *name;
    void (*func)(void);
    enum exam_test_state state;
    int exit_signal; /* in case state = EXAM_TEST_CRASHED */
};

struct exam_test_list
{
    struct exam_test *data;
    size_t count;
    size_t capacity;
};

struct exam_filter
{
    char *category_name;
    char *test_name;
};

struct exam_state
{
    struct exam_test_list test_list;
    size_t passed;
    size_t failed;
    size_t crashed;
};

struct exam_cli_state
{
    bool parallel;
    struct exam_filter filter;
    bool no_color;
};

#ifdef __cplusplus
extern "C" {
#endif
extern void _exam_assert_true(bool result, const char *expression, const char *file, size_t line);
extern void _exam_assert_false(bool result, const char *expression, const char *file, size_t line);
extern void _exam_assert_eq_ptr(void *a, void *b, const char *file, size_t line);
extern void _exam_assert_neq_ptr(void *a, void *b, const char *file, size_t line);
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
extern void exam_run_tests_parallel(struct exam_test_list *list, struct exam_filter filter);
extern void exam_run_tests(struct exam_test_list *list, struct exam_filter options);
extern void exam_run_test(struct exam_test *test);
extern void exam_list_append(struct exam_test_list *list, const struct exam_test *test);
extern void exam_list_destroy(struct exam_test_list *list);
extern void exam_list_sort(struct exam_test_list *list);

extern struct exam_cli_state exam_cli_state;
extern int exam_cli_main(int argc, char **argv);
#ifdef __cplusplus
}
#endif

#ifdef EXAM_SOURCE
#ifdef __linux__
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#else
#error "Your platform is currently not supported"
#endif

struct exam_state exam_state = {0};

static int _exam_test_cmp(const void *a, const void *b);

static bool _exam_float_cmp(float a, float b, float eps);
static bool _exam_float_in_range(float x, float min, float max, float eps);
static bool _exam_double_cmp(double a, double b, double eps);
static bool _exam_double_in_range(double x, double min, double max, double eps);

static void *_exam_run_worker(void *arg);

static void _exam_dief(const char *fmt, ...);
static void _exam_die_errno(const char *str);

void _exam_assert_true(bool res, const char *expression, const char *file, size_t line)
{
    if (!res) {
        fprintf(stderr,
                "[%s:%zu] %s is not true\n",
                file,
                line,
                expression);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_false(bool res, const char *expression, const char *file, size_t line)
{
    if (res) {
        fprintf(stderr,
                "[%s:%zu] %s is not false\n",
                file,
                line,
                expression);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_eq_ptr(void *a, void *b, const char *file, size_t line)
{
    if (a != b) {
        fprintf(stderr,
                "[%s:%zu] %p != %p\n",
                file,
                line,
                a,
                b);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_neq_ptr(void *a, void *b, const char *file, size_t line)
{
    if (a == b) {
        fprintf(stderr,
                "[%s:%zu] %p == %p\n",
                file,
                line,
                a,
                b);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_eq_int(intmax_t a, intmax_t b, const char *file, size_t line)
{
    if (a != b) {
        fprintf(stderr,
                "[%s:%zu] %jd != %jd\n",
                file,
                line,
                a,
                b);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_neq_int(intmax_t a, intmax_t b, const char *file, size_t line)
{
    if (a == b) {
        fprintf(stderr,
                "[%s:%zu] %jd == %jd\n",
                file,
                line,
                a,
                b);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_eq_uint(uintmax_t a, uintmax_t b, const char *file, size_t line)
{
    if (a != b) {
        fprintf(stderr,
                "[%s:%zu] %ju != %ju\n",
                file,
                line,
                a,
                b);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_neq_uint(uintmax_t a, uintmax_t b, const char *file, size_t line)
{
    if (a == b) {
        fprintf(stderr,
                "[%s:%zu] %ju == %ju\n",
                file,
                line,
                a,
                b);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_eq_float(float a, float b, float eps, const char *file, size_t line)
{
    if (!_exam_float_cmp(a, b, eps)) {
        fprintf(stderr,
                "[%s:%zu] %f != %f\n",
                file,
                line,
                a,
                b);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_neq_float(float a, float b, float eps, const char *file, size_t line)
{
    if (_exam_float_cmp(a, b, eps)) {
        fprintf(stderr,
                "[%s:%zu] %f == %f\n",
                file,
                line,
                a,
                b);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_eq_double(double a, double b, double eps, const char *file, size_t line)
{
    if (!_exam_double_cmp(a, b, eps)) {
        fprintf(stderr,
                "[%s:%zu] %f != %f\n",
                file,
                line,
                a,
                b);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_neq_double(double a, double b, double eps, const char *file, size_t line)
{
    if (_exam_double_cmp(a, b, eps)) {
        fprintf(stderr,
                "[%s:%zu] %f == %f\n",
                file,
                line,
                a,
                b);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_eq_str(const char *a, const char *b, const char *file, size_t line)
{
    if (strcmp(a, b) != 0) {
        fprintf(stderr,
                "[%s:%zu] %s != %s\n",
                file,
                line,
                a,
                b);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_neq_str(const char *a, const char *b, const char *file, size_t line)
{
    if (strcmp(a, b) == 0) {
        fprintf(stderr,
                "[%s:%zu] %s == %s\n",
                file,
                line,
                a,
                b);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_eq_mem(const void *a, const void *b, size_t size, const char *file, size_t line)
{
    const unsigned char *expected = a;
    const unsigned char *actual = b;

    for (size_t i = 0; i < size; i ++) {
        if (expected[i] != actual[i]) {
            fprintf(stderr,
                    "[%s:%zu] memory differs at offset %zu: expected=0x%02x actual=0x%02x\n",
                    file,
                    line,
                    i,
                    expected[i],
                    actual[i]);
            exit(EXIT_FAILURE);
        }
    }
}

void _exam_assert_neq_mem(const void *a, const void *b, size_t size, const char *file, size_t line)
{
    if (memcmp(a, b, size) == 0) {
        fprintf(stderr,
                "[%s:%zu] memory regions are equal (%zu bytes)\n",
                file,
                line,
                size);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_in_range_int(intmax_t x, intmax_t min, intmax_t max, const char *file, size_t line)
{
    if (x < min || x > max) {
        fprintf(stderr,
                "[%s:%zu] %jd is not within the range [%jd, %jd]\n",
                file,
                line,
                x,
                min,
                max);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_not_in_range_int(intmax_t x, intmax_t min, intmax_t max, const char *file, size_t line)
{
    if (x >= min && x <= max) {
        fprintf(stderr,
                "[%s:%zu] %jd is within the range [%jd, %jd]\n",
                file,
                line,
                x,
                min,
                max);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_in_range_uint(uintmax_t x, uintmax_t min, uintmax_t max, const char *file, size_t line)
{
    if (x < min || x > max) {
        fprintf(stderr,
                "[%s:%zu] %ju is not within the range [%ju, %ju]\n",
                file,
                line,
                x,
                min,
                max);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_not_in_range_uint(uintmax_t x, uintmax_t min, uintmax_t max, const char *file, size_t line)
{
    if (x >= min && x <= max) {
        fprintf(stderr,
                "[%s:%zu] %ju is within the range [%ju, %ju]\n",
                file,
                line,
                x,
                min,
                max);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_in_range_float(float x, float min, float max, float eps, const char *file, size_t line)
{
    if (!_exam_float_in_range(x, min, max, eps)) {
        fprintf(stderr,
                "[%s:%zu] %f is not within the range [%f, %f]\n",
                file,
                line,
                x,
                min,
                max);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_not_in_range_float(float x, float min, float max, float eps, const char *file, size_t line)
{
    if (_exam_float_in_range(x, min, max, eps)) {
        fprintf(stderr,
                "[%s:%zu] %f is within the range [%f, %f]\n",
                file,
                line,
                x,
                min,
                max);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_in_range_double(double x, double min, double max, double eps, const char *file, size_t line)
{
    if (!_exam_double_in_range(x, min, max, eps)) {
        fprintf(stderr,
                "[%s:%zu] %f is not within the range [%f, %f]\n",
                file,
                line,
                x,
                min,
                max);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_not_in_range_double(double x, double min, double max, double eps, const char *file, size_t line)
{
    if (_exam_double_in_range(x, min, max, eps)) {
        fprintf(stderr,
                "[%s:%zu] %f is within the range [%f, %f]\n",
                file,
                line,
                x,
                min,
                max);
        exit(EXIT_FAILURE);
    }
}

void _exam_assert_in_arr_int(intmax_t x, const intmax_t *arr, size_t count, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (arr[i] == x)
            return;
    }

    fprintf(stderr,
            "[%s:%zu] %jd not in %p (count=%zu)",
            file,
            line,
            x,
            (void*)arr,
            count);
    exit(EXIT_FAILURE);
}

void _exam_assert_not_in_arr_int(intmax_t x, const intmax_t *arr, size_t count, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (arr[i] == x) {
            fprintf(stderr,
                    "[%s:%zu] %jd in %p (count=%zu)",
                    file,
                    line,
                    x,
                    (void*)arr,
                    count);
            exit(EXIT_FAILURE);
        }
    }
}

void _exam_assert_in_arr_uint(uintmax_t x, const uintmax_t *arr, size_t count, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (arr[i] == x)
            return;
    }

    fprintf(stderr,
            "[%s:%zu] %ju not in %p (count=%zu)",
            file,
            line,
            x,
            (void*)arr,
            count);
    exit(EXIT_FAILURE);
}

void _exam_assert_not_in_arr_uint(uintmax_t x, const uintmax_t *arr, size_t count, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (arr[i] == x) {
            fprintf(stderr,
                    "[%s:%zu] %ju in %p (count=%zu)",
                    file,
                    line,
                    x,
                    (void*)arr,
                    count);
            exit(EXIT_FAILURE);
        }
    }
}

void _exam_assert_in_arr_float(float x, const float *arr, size_t count, float eps, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (_exam_float_cmp(x, arr[i], eps))
            return;
    }

    fprintf(stderr,
            "[%s:%zu] %f not in %p (count=%zu)",
            file,
            line,
            x,
            (void*)arr,
            count);
    exit(EXIT_FAILURE);
}

void _exam_assert_not_in_arr_float(float x, const float *arr, size_t count, float eps, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (_exam_float_cmp(x, arr[i], eps)) {
            fprintf(stderr,
                    "[%s:%zu] %f in %p (count=%zu)",
                    file,
                    line,
                    x,
                    (void*)arr,
                    count);
            exit(EXIT_FAILURE);
        }
    }
}

void _exam_assert_in_arr_double(double x, const double *arr, size_t count, double eps, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (_exam_double_cmp(x, arr[i], eps))
            return;
    }

    fprintf(stderr,
            "[%s:%zu] %f not in %p (count=%zu)",
            file,
            line,
            x,
            (void*)arr,
            count);
    exit(EXIT_FAILURE);
}

void _exam_assert_not_in_arr_double(double x, const double *arr, size_t count, double eps, const char *file, size_t line)
{
    for (size_t i = 0; i < count; i ++) {
        if (_exam_double_cmp(x, arr[i], eps)) {
            fprintf(stderr,
                    "[%s:%zu] %f in %p (count=%zu)",
                    file,
                    line,
                    x,
                    (void*)arr,
                    count);
            exit(EXIT_FAILURE);
        }
    }
}

struct exam_test_queue
{
    struct exam_test_list *test_list;
    struct exam_filter filter;
    size_t next_test_index;
    pthread_mutex_t lock;
};

void exam_run_tests_parallel(struct exam_test_list *list, struct exam_filter filter)
{
    long cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
    if (cpu_count <= 0)
        cpu_count = 1;

    size_t worker_count = cpu_count;
    if (worker_count > list->count)
        worker_count = list->count;

    pthread_t *threads = malloc(worker_count * sizeof(*threads));
    if (threads == NULL)
        _exam_die_errno("malloc");

    struct exam_test_queue worker = {
        .test_list = list,
        .filter = filter,
        .next_test_index = 0
    };
    pthread_mutex_init(&worker.lock, NULL);

    for (size_t i = 0; i < worker_count; i ++) {
        if (pthread_create(&threads[i], NULL, _exam_run_worker, &worker) != 0)
            _exam_die_errno("pthread_create");
    }
    for (size_t i = 0; i < worker_count; i ++)
        pthread_join(threads[i], NULL);

    free(threads);
    pthread_mutex_destroy(&worker.lock);
}

void exam_run_tests(struct exam_test_list *list, struct exam_filter filter)
{
    for (size_t i = 0; i < list->count; i ++) {
        if (!exam_test_passes_filter(&list->data[i], filter))
            continue;

        exam_run_test(&list->data[i]);
    }
}

void *_exam_run_worker(void *arg)
{
    struct exam_test_queue *worker = arg;

    while (true) {
        pthread_mutex_lock(&worker->lock);
        size_t idx = worker->next_test_index;
        if (idx < worker->test_list->count)
            worker->next_test_index++;
        pthread_mutex_unlock(&worker->lock);

        if (idx >= worker->test_list->count)
            break;

        struct exam_test *test = &worker->test_list->data[idx];
        if (!exam_test_passes_filter(test, worker->filter))
            continue;

        exam_run_test(test);
    }

    return NULL;
}

void exam_run_test(struct exam_test *test)
{
    if (test->state != EXAM_TEST_NONE)
        _exam_dief("tried to run test with an unexpected state: %d\n", test->state);

    test->state = EXAM_TEST_RUNNING;

    pid_t pid = fork();
    if (pid == -1)
        _exam_die_errno("fork");

    if (pid == 0) {
        test->func();
        _exit(EXIT_SUCCESS);
    }

    int status;
    if (waitpid(pid, &status, 0) == -1)
        _exam_die_errno("waitpid");

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

void exam_list_append(struct exam_test_list *list, const struct exam_test *test)
{
    size_t idx = list->count ++;
    if (list->data == NULL || list->count > list->capacity) {
        size_t min_cap = list->count;
        if (min_cap < 4)
            min_cap = 4;
        else
            min_cap = list->capacity *= 2;

        list->capacity = min_cap;
        list->data = realloc(list->data, sizeof(*list->data) * list->capacity);
        if (list->data == NULL)
            _exam_die_errno("realloc");
    }

    list->data[idx] = *test;
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

static void _exam_dief(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

static void _exam_die_errno(const char *str)
{
    perror(str);
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

static bool _exam_float_cmp(float a, float b, float eps)
{
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
    return (_exam_float_cmp(x, min, eps) || x > min) &&
           (_exam_float_cmp(x, max, eps) || x < max);
}

static bool _exam_double_cmp(double a, double b, double eps)
{
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
    return (_exam_double_cmp(x, min, eps) || x > min) &&
           (_exam_double_cmp(x, max, eps) || x < max);
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

static void _exam_cli_cmd_run();
static void _exam_cli_cmd_ls();
static void _exam_cli_usage();
static const char *exam_cli_color(const char *color);

int exam_cli_main(int argc, char **argv)
{
    exam_list_sort(&exam_state.test_list);

    /* options */
    int command_count = 1;
    for (int i = 1; i < argc; i ++) {
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--parallel") == 0) {
            exam_cli_state.parallel = true;
        } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--test-name") == 0) {
            if (i == argc - 1 || argv[i + 1][0] == '-')
                _exam_dief("%sexpected name%s\n",
                          exam_cli_color(EXAM_CLI_RED),
                          exam_cli_color(EXAM_CLI_RESET));

            exam_cli_state.filter.test_name = argv[++i];
        } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--category") == 0) {
            if (i == argc - 1 || argv[i + 1][0] == '-')
                _exam_dief("%sexpected category%s\n",
                          exam_cli_color(EXAM_CLI_RED),
                          exam_cli_color(EXAM_CLI_RESET));

            exam_cli_state.filter.category_name = argv[++i];
        } else if (strcmp(argv[i], "--no-color") == 0) {
            exam_cli_state.no_color = true;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            _exam_cli_usage();
            exit(EXIT_SUCCESS);
        } else if (argv[i][0] == '-') {
            _exam_cli_usage();
            _exam_dief("%sunknown option '%s'%s\n",
                      exam_cli_color(EXAM_CLI_RED),
                      argv[i],
                      exam_cli_color(EXAM_CLI_RESET));
            exit(EXIT_FAILURE);
        } else {
            argv[command_count++] = argv[i];
        }
    }

    if (command_count != 2) {
        _exam_cli_usage();
        _exam_dief("%sexpected only one command, but got %d%s\n",
                  exam_cli_color(EXAM_CLI_RED),
                  command_count - 1,
                  exam_cli_color(EXAM_CLI_RESET));
    }

    /* commands */
    argc = command_count;
    for (int i = 1; i < argc; i ++) {
        if (strcmp(argv[i], "run") == 0) {
            _exam_cli_cmd_run();
        } else if (strcmp(argv[i], "ls") == 0) {
            _exam_cli_cmd_ls();
        } else {
            _exam_cli_usage();
            _exam_dief("%sunknown command '%s'%s\n",
                       exam_cli_color(EXAM_CLI_RED),
                       argv[i],
                       exam_cli_color(EXAM_CLI_RESET));
            exit(EXIT_FAILURE);
        }
    }

    exam_list_destroy(&exam_state.test_list);
    return EXIT_SUCCESS;
}

static void _exam_cli_cmd_run()
{
    if (exam_cli_state.parallel)
        exam_run_tests_parallel(&exam_state.test_list, exam_cli_state.filter);
    else
        exam_run_tests(&exam_state.test_list, exam_cli_state.filter);

    for (size_t i = 0; i < exam_state.test_list.count; i++) {
        struct exam_test *test = &exam_state.test_list.data[i];
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
                        "%s[FAIL] %s/%s%s\n",
                        exam_cli_color(EXAM_CLI_RED),
                        test->category,
                        test->name,
                        exam_cli_color(EXAM_CLI_RESET));
                break;
            case EXAM_TEST_CRASHED:
                exam_state.crashed ++;
                fprintf(stderr,
                        "%s[CRASH] %s/%s (signal %d)%s\n",
                        exam_cli_color(EXAM_CLI_YELLOW),
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

static void _exam_cli_cmd_ls()
{
    size_t found = 0;
    for (size_t i = 0; i < exam_state.test_list.count; i++) {
        const struct exam_test *test = &exam_state.test_list.data[i];
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

static void _exam_cli_usage()
{
    printf("%s"EXAM_CLI_NAME"%s - Find and run unit tests\n"
           "%susage%s:\n"
           "     %s"EXAM_CLI_NAME" run%s [-p|--parallel]\n"
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
