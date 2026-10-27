/*  exam - v0.1 - unit testing library

    This is a single-header library that provides a portable
    and easy-to-use way for writing and running unit-tests
    in C and C++.

    To use this library, do this in *one* C or C++ file:
        #define EXAM_IMPLEMENTATION
        #include "exam.h"

LICENSE
    Copyright (c) 2026 Matei-Stefan Costan

    Licensed under the MIT License.
    See LICENSE for details.

COMPILE-TIME OPTIONS

    #define EXAM_NO_SHORT_NAMES

        By default, exam exposes shorter function names. In the case
        that those collide with other symbols, you can use this flag
        to add the "EXAM_" prefix.

    #define EXAM_CALLOC(n, size) better_calloc
    #define EXAM_REALLOC(p, size) better_realloc
    #define EXAM_FREE(ptr) better_free

        Override the memory allocation functions used internally by exam.
        By default, these are calloc(), realloc(), and free().
        You must either define all three or none.

    #define EXAM_NO_AUTO_REGISTRATION

        This library automatically registers the tests when you define
        them (using compiler extensions like constructors for GCC and Clang).
        If your compiler does not support such features, you can use this
        flag to turn it off and manually register your tests.

    #define EXAM_TEST_OUTPUT_SIZE size

        The max size of the buffer that holds a test's output
        (stdout and stderr). By default this is set to 1024, but you
        can increase it or decrease it as long as it's bigger than 0.

    #define EXAM_CLI_NAME "name"

        The name shown in the CLI's help. By default it's set to "exam",
        but you can change this to the name of your executable or whatever
        you desire.

    #define EXAM_DEFAULT_TIMEOUT_MS ms

        The default milliseconds to wait before terminating a test. By default,
        it's set to 3000, but you can set it to any value as long as it's
        positive. A value of 0 means no limit.

    #define EXAM_NO_STL

        In case you are using C++, exam offers more functionality intended
        to use with the STL. To disable it, you can define this macro.

DOCUMENTATION

    Managing Tests

        DEFINE_TEST(category_name, test_name):
            Defines the test and automatically registers it if possible.
            This defines a function's signature and its body should
            follow right after. Note that category_name and test_name
            should *not* be strings, just symbols.

        REGISTER_TEST(category_name, test_name):
            If EXAM_NO_AUTO_REGISTRATION is defined, you can manually
            register them using this macro in main. As the previous one,
            category_name and test_name should *not* be strings, just symbols.

        int exam_run(const struct exam_filter *filter, size_t jobs):
            This runs all the registered tests and returns EXIT_FAILURE if at
            least one doesn't pass, crashes or times out, or EXIT_SUCCESS
            otherwise. filter is used to filter out tests (NULL = no filter,
            every test satisfies it). Jobs is the number of processes to start
            (0 = cpu count).

    Cli

        int exam_cli_main(int argc, char **argv):
            Runs the test suite using the command-line interface. It supports
            running tests in parallel, listing available tests, filtering by
            test name or category, setting per-test timeouts, and configuring
            colored output.

    Asserts

        ASSERT_TRUE(cond):
            Checks if the condition is true.

        ASSERT_FALSE(cond):
            Checks if the condition is false.

        ASSERT_EQ_PTR(a, b):
            Checks if the pointers a and b are equal.

        ASSERT_NEQ_PTR(a, b):
            Checks if the pointers a and b are not equal.

        ASSERT_NULL(ptr):
            Checks if ptr is NULL.

        ASSERT_NON_NULL(ptr):
            Checks if ptr is not NULL.

        ASSERT_EQ_INT(a, b):
            Checks if the signed integer values a and b are equal.

        ASSERT_NEQ_INT(a, b):
            Checks if the signed integer values a and b are not equal.

        ASSERT_LT_INT(a, b):
            Checks if the signed integer value a is less than b.

        ASSERT_LE_INT(a, b):
            Checks if the signed integer value a is less than or equal to b.

        ASSERT_GT_INT(a, b):
            Checks if the signed integer value a is greater than b.

        ASSERT_GE_INT(a, b):
            Checks if the signed integer value a is greater than or equal to b.

        ASSERT_EQ_UINT(a, b):
            Checks if the unsigned integer values a and b are equal.

        ASSERT_NEQ_UINT(a, b):
            Checks if the unsigned integer values a and b are not equal.

        ASSERT_LT_UINT(a, b):
            Checks if the unsigned integer value a is less than b.

        ASSERT_LE_UINT(a, b):
            Checks if the unsigned integer value a is less than or equal to b.

        ASSERT_GT_UINT(a, b):
            Checks if the unsigned integer value a is greater than b.

        ASSERT_GE_UINT(a, b):
            Checks if the unsigned integer value a is greater than or equal to b.

        ASSERT_EQ_FLOAT(a, b, eps):
            Checks if the floating-point values a and b are equal within the given epsilon.

        ASSERT_NEQ_FLOAT(a, b, eps):
            Checks if the floating-point values a and b are not equal within the given epsilon.

        ASSERT_LT_FLOAT(a, b, eps):
            Checks if the floating-point value a is less than b, accounting for the given epsilon.

        ASSERT_LE_FLOAT(a, b, eps):
            Checks if the floating-point value a is less than or equal to b, accounting for the given epsilon.

        ASSERT_GT_FLOAT(a, b, eps):
            Checks if the floating-point value a is greater than b, accounting for the given epsilon.

        ASSERT_GE_FLOAT(a, b, eps):
            Checks if the floating-point value a is greater than or equal to b, accounting for the given epsilon.

        ASSERT_EQ_DOUBLE(a, b, eps):
            Checks if the double-precision floating-point values a and b are equal within the given epsilon.

        ASSERT_NEQ_DOUBLE(a, b, eps):
            Checks if the double-precision floating-point values a and b are not equal within the given epsilon.

        ASSERT_LT_DOUBLE(a, b, eps):
            Checks if the double-precision floating-point value a is less than b, accounting for the given epsilon.

        ASSERT_LE_DOUBLE(a, b, eps):
            Checks if the double-precision floating-point value a is less than or equal to b,
            accounting for the given epsilon.

        ASSERT_GT_DOUBLE(a, b, eps):
            Checks if the double-precision floating-point value a is greater than b,
            accounting for the given epsilon.

        ASSERT_GE_DOUBLE(a, b, eps):
            Checks if the double-precision floating-point value a is greater than or equal to b,
            accounting for the given epsilon.

        ASSERT_EQ_STR(a, b):
            Checks if the null-terminated strings a and b are equal.

        ASSERT_NEQ_STR(a, b):
            Checks if the null-terminated strings a and b are not equal.

        ASSERT_EQ_MEM(a, b, size):
            Checks if the first size bytes of memory at a and b are equal.

        ASSERT_NEQ_MEM(a, b, size):
            Checks if the first size bytes of memory at a and b are not equal.

        ASSERT_IN_RANGE_INT(x, min, max):
            Checks if the signed integer x is within the inclusive range [min, max].

        ASSERT_NOT_IN_RANGE_INT(x, min, max):
            Checks if the signed integer x is outside the inclusive range [min, max].

        ASSERT_IN_RANGE_UINT(x, min, max):
            Checks if the unsigned integer x is within the inclusive range [min, max].

        ASSERT_NOT_IN_RANGE_UINT(x, min, max):
            Checks if the unsigned integer x is outside the inclusive range [min, max].

        ASSERT_IN_RANGE_FLOAT(x, min, max, eps):
            Checks if the floating-point value x is within the inclusive range [min, max],
            using eps for floating-point comparisons.

        ASSERT_NOT_IN_RANGE_FLOAT(x, min, max, eps):
            Checks if the floating-point value x is outside the inclusive range [min, max],
            using eps for floating-point comparisons.

        ASSERT_IN_RANGE_DOUBLE(x, min, max, eps):
            Checks if the double-precision floating-point value x is within the inclusive range [min, max],
            using eps for floating-point comparisons.

        ASSERT_NOT_IN_RANGE_DOUBLE(x, min, max, eps):
            Checks if the double-precision floating-point value x is outside the inclusive range [min, max],
            using eps for floating-point comparisons.

        ASSERT_IN_ARR_INT(x, arr, count):
            Checks if the signed integer x is contained in the first count elements of the integer array arr.

        ASSERT_NOT_IN_ARR_INT(x, arr, count):
            Checks if the signed integer x is not contained in the first count elements of the integer array arr.

        ASSERT_IN_ARR_UINT(x, arr, count):
            Checks if the unsigned integer x is contained in the first count elements of the
            unsigned integer array arr.

        ASSERT_NOT_IN_ARR_UINT(x, arr, count):
            Checks if the unsigned integer x is not contained in the first count elements of the
            unsigned integer array arr.

        ASSERT_IN_ARR_FLOAT(x, arr, count, eps):
            Checks if the floating-point value x is contained in the first count elements of the array arr,
            using eps for comparisons.

        ASSERT_NOT_IN_ARR_FLOAT(x, arr, count, eps):
            Checks if the floating-point value x is not contained in the first count elements of the array arr,
            using eps for comparisons.

        ASSERT_IN_ARR_DOUBLE(x, arr, count, eps):
            Checks if the double-precision floating-point value x is contained in the first count elements
            of the array arr, using eps for comparisons.

        ASSERT_NOT_IN_ARR_DOUBLE(x, arr, count, eps):
            Checks if the double-precision floating-point value x is not contained in the first count
            elements of the array arr, using eps for comparisons.

        C++ Asserts

            ASSERT_IN_CONTAINER(x, container):
                Checks whether container contains an element equal to x.

            ASSERT_NOT_IN_CONTAINER(x, container):
                Checks whether container does not contain an element equal to x.

            ASSERT_KEY_IN_MAP(k, m):
                Checks whether map m contains the key k.

            ASSERT_KEY_NOT_IN_MAP(k, m):
                Checks whether map m does not contain the key k.

            ASSERT_VAL_IN_MAP(v, m):
                Checks whether map m contains a value equal to v.

            ASSERT_VAL_NOT_IN_MAP(v, m):
                Checks whether map m does not contain a value equal to v.

            ASSERT_KEY_VAL_IN_MAP(k, v, m):
                Checks whether map m contains the key k associated with a value equal to v.
                Fails if the key is absent or its associated value differs from v.

            ASSERT_KEY_VAL_NOT_IN_MAP(k, v, m):
                Checks whether map m does not contain the key k associated with a value equal to v.
                Passes if the key is absent or its associated value differs from v.

        Custom Asserts

            DEFINE_ASSERT_FUNC(name, ...):
                Defines a custom assertion function named exam_assert_name.
                The macro appends const char *file and size_t line parameters
                to capture the assertion's call site.

            CALL_ASSERT_FUNC(name, ...):
                Calls a custom assertion function, automatically passing
                __FILE__ and __LINE__.

            On failure, use exam_fail_test(file, line, ...) to report the
            error with the correct source location.

    Notes

        Internal Functions

            All internal functions are prefixed with exam_internal, while internal macros
            use EXAM_INTERNAL. Using them from outside the library is discouraged.

        Automatic Registration

            Tests can be registered automatically using compiler-supported constructor
            attributes, allowing the test suite to be populated before main runs.
            Constructor support and behavior depend on the platform and compiler.

        Process isolation

            Each test runs in a separate process, isolating crashes and timeouts so that
            one test does not terminate the entire suite. Tests can run concurrently when
            multiple jobs are configured.
 */

#ifndef EXAM_H
#define EXAM_H

#if !defined(_WIN32) && !defined(_POSIX_C_SOURCE) && !defined(_GNU_SOURCE) && !defined(_DEFAULT_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#define EXAM_POSIX
#define EXAM_LINUX
#elif defined(__APPLE__)
#define EXAM_POSIX
#define EXAM_APPLE
#elif defined(__unix__) || defined(__unix) || defined(__CYGWIN__)
#define EXAM_POSIX
#elif defined(_WIN32)
#define EXAM_WINDOWS
#else
#define EXAM_UNKNOWN_PLATFORM
#endif

#if defined(__clang__)
#define EXAM_CLANG
#elif defined(__TINYC__)
#define EXAM_TCC
#elif defined(__GNUC__)
#define EXAM_GCC
#elif defined(_MSC_VER)
#define EXAM_MSVC
#else
#define EXAM_UNKNOWN_COMPILER
#endif

#if !defined(EXAM_CALLOC) && !defined(EXAM_REALLOC) && !defined(EXAM_FREE)
#define EXAM_CALLOC(n, size) calloc(n, size)
#define EXAM_REALLOC(p, size) realloc(p, size)
#define EXAM_FREE(p) free(p)
#elif !defined(EXAM_CALLOC) || !defined(EXAM_REALLOC) || !defined(EXAM_FREE)
#error "EXAM_CALLOC, EXAM_REALLOC and EXAM_FREE must be defined together."
#endif

#if defined(__cplusplus) && __cplusplus >= 201103L
#define EXAM_NORETURN [[noreturn]]
#elif defined(EXAM_GCC) || defined(EXAM_CLANG) || defined(EXAM_TCC)
#define EXAM_NORETURN __attribute__((noreturn))
#elif defined(EXAM_MSVC)
#define EXAM_NORETURN __declspec(noreturn)
#else
#define EXAM_NORETURN
#endif

#if defined(EXAM_GCC) || defined(EXAM_CLANG)
#define EXAM_PRINTF(fmt_idx, args_idx) __attribute__((format(printf, fmt_idx, args_idx)))
#else
#define EXAM_PRINTF(fmt_idx, args_idx)
#endif

#ifndef EXAM_NO_AUTO_REGISTRATION
#if defined(__cplusplus)
#define EXAM_CONSTRUCTOR(func_name) \
        static void func_name(void); \
        namespace { \
            struct func_name##_registrar { \
                func_name##_registrar(void) { func_name(); } \
            } func_name##_instance; \
        } \
        static void func_name(void)
#elif defined(EXAM_GCC) || defined(EXAM_CLANG) || defined(EXAM_TCC)
#define EXAM_CONSTRUCTOR(func_name) \
    static void func_name(void) __attribute__((constructor)); \
    static void func_name(void)
#elif defined(EXAM_MSVC)
#pragma section(".CRT$XCU", read)
#define EXAM_CONSTRUCTOR_IMPL(func_name, prefix) \
    static void func_name(void); \
    __declspec(allocate(".CRT$XCU")) void (*func_name##_)(void) = func_name; \
    __pragma(comment(linker, "/include:" prefix #func_name "_")) \
    static void func_name(void)
#ifdef _WIN64
#define EXAM_CONSTRUCTOR(func_name) EXAM_CONSTRUCTOR_IMPL(func_name, "")
#else
#define EXAM_CONSTRUCTOR(func_name) EXAM_CONSTRUCTOR_IMPL(func_name, "_")
#endif // _WIN64
#else
#error "Automatic registration not supported for your compiler"
#endif
#define EXAM_CONSTRUCTOR_EXPAND(func_name) EXAM_CONSTRUCTOR(func_name)
#endif // EXAM_NO_AUTO_REGISTRATION

#ifndef EXAM_TEST_OUTPUT_SIZE
#define EXAM_TEST_OUTPUT_SIZE 1024
#endif
#if EXAM_TEST_OUTPUT_SIZE < 1
#error "EXAM_TEST_OUTPUT_SIZE must be greater than zero"
#endif

#ifndef EXAM_DEFAULT_TIMEOUT_MS
#define EXAM_DEFAULT_TIMEOUT_MS 3000
#endif
#if EXAM_DEFAULT_TIMEOUT_MS < 0
#error "EXAM_DEFAULT_TIMEOUT_MS must not be negative"
#endif

#ifndef EXAM_CLI_NAME
#define EXAM_CLI_NAME "exam"
#endif

#define EXAM_DEFINE_ASSERT_FUNC(name, ...) void exam_assert_##name(__VA_ARGS__, const char *file, size_t line)
#define EXAM_CALL_ASSERT_FUNC(name, ...) exam_assert_##name(__VA_ARGS__, __FILE__, __LINE__)

#define EXAM_ASSERT_TRUE(cond) exam_assert_true((cond), #cond, __FILE__, __LINE__)
#define EXAM_ASSERT_FALSE(cond) exam_assert_false((cond), #cond, __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_PTR(a, b) exam_assert_eq_ptr((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_PTR(a, b) exam_assert_neq_ptr((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_NULL(ptr) exam_assert_eq_ptr((ptr), NULL, __FILE__, __LINE__)
#define EXAM_ASSERT_NON_NULL(ptr) exam_assert_neq_ptr((ptr), NULL, __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_INT(a, b) exam_assert_eq_int((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_INT(a, b) exam_assert_neq_int((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_LT_INT(a, b) exam_assert_lt_int((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_LE_INT(a, b) exam_assert_le_int((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_GT_INT(a, b) exam_assert_gt_int((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_GE_INT(a, b) exam_assert_ge_int((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_UINT(a, b) exam_assert_eq_uint((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_UINT(a, b) exam_assert_neq_uint((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_LT_UINT(a, b) exam_assert_lt_uint((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_LE_UINT(a, b) exam_assert_le_uint((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_GT_UINT(a, b) exam_assert_gt_uint((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_GE_UINT(a, b) exam_assert_ge_uint((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_FLOAT(a, b, eps) exam_assert_eq_float((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_FLOAT(a, b, eps) exam_assert_neq_float((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_LT_FLOAT(a, b, eps) exam_assert_lt_float((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_LE_FLOAT(a, b, eps) exam_assert_le_float((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_GT_FLOAT(a, b, eps) exam_assert_gt_float((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_GE_FLOAT(a, b, eps) exam_assert_ge_float((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_DOUBLE(a, b, eps) exam_assert_eq_double((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_DOUBLE(a, b, eps) exam_assert_neq_double((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_LT_DOUBLE(a, b, eps) exam_assert_lt_double((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_LE_DOUBLE(a, b, eps) exam_assert_le_double((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_GT_DOUBLE(a, b, eps) exam_assert_gt_double((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_GE_DOUBLE(a, b, eps) exam_assert_ge_double((a), (b), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_STR(a, b) exam_assert_eq_str((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_STR(a, b) exam_assert_neq_str((a), (b), __FILE__, __LINE__)
#define EXAM_ASSERT_EQ_MEM(a, b, size) exam_assert_eq_mem((a), (b), (size), __FILE__, __LINE__)
#define EXAM_ASSERT_NEQ_MEM(a, b, size) exam_assert_neq_mem((a), (b), (size), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_RANGE_INT(x, min, max) exam_assert_in_range_int((x), (min), (max), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_RANGE_INT(x, min, max) exam_assert_not_in_range_int((x), (min), (max), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_RANGE_UINT(x, min, max) exam_assert_in_range_uint((x), (min), (max), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_RANGE_UINT(x, min, max) exam_assert_not_in_range_uint((x), (min), (max), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_RANGE_FLOAT(x, min, max, eps) exam_assert_in_range_float((x), (min), (max), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_RANGE_FLOAT(x, min, max, eps) exam_assert_not_in_range_float((x), (min), (max), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_RANGE_DOUBLE(x, min, max, eps) exam_assert_in_range_double((x), (min), (max), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_RANGE_DOUBLE(x, min, max, eps) exam_assert_not_in_range_double((x), (min), (max), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_ARR_INT(x, arr, count) exam_assert_in_arr_int((x), (arr), (count), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_ARR_INT(x, arr, count) exam_assert_not_in_arr_int((x), (arr), (count), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_ARR_UINT(x, arr, count) exam_assert_in_arr_uint((x), (arr), (count), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_ARR_UINT(x, arr, count) exam_assert_not_in_arr_uint((x), (arr), (count), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_ARR_FLOAT(x, arr, count, eps) exam_assert_in_arr_float((x), (arr), (count), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_ARR_FLOAT(x, arr, count, eps) exam_assert_not_in_arr_float((x), (arr), (count), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_IN_ARR_DOUBLE(x, arr, count, eps) exam_assert_in_arr_double((x), (arr), (count), (eps), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_ARR_DOUBLE(x, arr, count, eps) exam_assert_not_in_arr_double((x), (arr), (count), (eps), __FILE__, __LINE__)

#if defined(__cplusplus) && !defined(EXAM_NO_STL)
#define EXAM_ASSERT_IN_CONTAINER(x, container) exam_assert_in_container((x), (container), __FILE__, __LINE__)
#define EXAM_ASSERT_NOT_IN_CONTAINER(x, container) exam_assert_not_in_container((x), (container), __FILE__, __LINE__)
#define EXAM_ASSERT_KEY_IN_MAP(k, m) exam_assert_key_in_map((k), (m), __FILE__, __LINE__)
#define EXAM_ASSERT_KEY_NOT_IN_MAP(k, m) exam_assert_key_not_in_map((k), (m), __FILE__, __LINE__)
#define EXAM_ASSERT_VAL_IN_MAP(v, m) exam_assert_val_in_map((v), (m), __FILE__, __LINE__)
#define EXAM_ASSERT_VAL_NOT_IN_MAP(v, m) exam_assert_val_not_in_map((v), (m), __FILE__, __LINE__)
#define EXAM_ASSERT_KEY_VAL_IN_MAP(k, v, m) exam_assert_key_val_in_map((k), (v), (m), __FILE__, __LINE__)
#define EXAM_ASSERT_KEY_VAL_NOT_IN_MAP(k, v, m) exam_assert_key_val_not_in_map((k), (v), (m), __FILE__, __LINE__)
#endif // defined(__cplusplus) && !defined(EXAM_NO_STL)

#define EXAM_INTERNAL_DEF_NAME(category_name, test_name) \
    exam_def_##category_name##_##test_name

#ifndef EXAM_NO_AUTO_REGISTRATION
#define EXAM_INTERNAL_REG_NAME(category_name, test_name) \
    exam_reg_category_##category_name##_name_##test_name

#define EXAM_DEFINE_TEST(category_name, test_name) \
    static void EXAM_INTERNAL_DEF_NAME(category_name, test_name)(void); \
    EXAM_CONSTRUCTOR_EXPAND(EXAM_INTERNAL_REG_NAME(category_name, test_name)) \
    { \
        struct exam_test test = {0}; \
        test.category = #category_name; \
        test.name = #test_name; \
        test.func = EXAM_INTERNAL_DEF_NAME(category_name, test_name); \
        exam_register(&test); \
    } \
    static void EXAM_INTERNAL_DEF_NAME(category_name, test_name)(void)

#else

#define EXAM_INTERNAL_STRUCT_NAME(category_name, test_name) \
    exam_test_obj_##category_name##_##test_name

#define EXAM_DEFINE_TEST(category_name, test_name) \
    static void EXAM_INTERNAL_DEF_NAME(category_name, test_name)(void); \
    static struct exam_test EXAM_INTERNAL_STRUCT_NAME(category_name, test_name) = { \
        #category_name, /* category */ \
        #test_name, /* name */ \
        EXAM_INTERNAL_DEF_NAME(category_name, test_name), /* func */ \
        \
        EXAM_TEST_NONE, /* state */ \
        0, /* exit_signal */ \
        \
        0, /* registration_index */ \
        \
        {0}, /* output */ \
        0, /* output_size */ \
        false, /* output_truncated */ \
    }; \
    static void EXAM_INTERNAL_DEF_NAME(category_name, test_name)(void)

#define EXAM_REGISTER_TEST(category_name, test_name) \
    exam_register(&EXAM_INTERNAL_STRUCT_NAME(category_name, test_name))
#endif // EXAM_NO_AUTO_REGISTRATION

enum exam_test_state
{
    EXAM_TEST_NONE = 0,
    EXAM_TEST_RUNNING,
    EXAM_TEST_PASSED,
    EXAM_TEST_FAILED,
    EXAM_TEST_CRASHED,
    EXAM_TEST_TIMEOUT,
};

struct exam_test
{
    const char *category;
    const char *name;
    void (*func)(void);

    enum exam_test_state state;
    int exit_signal;

    size_t registration_index;

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
    size_t timed_out;

    uint64_t timeout_ms;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
EXAM_NORETURN extern void exam_fail_test(const char *file, size_t line, const char *fmt, ...) EXAM_PRINTF(3, 4);

extern void exam_assert_true(bool result, const char *expression, const char *file, size_t line);
extern void exam_assert_false(bool result, const char *expression, const char *file, size_t line);
extern void exam_assert_eq_ptr(const void *a, const void *b, const char *file, size_t line);
extern void exam_assert_neq_ptr(const void *a, const void *b, const char *file, size_t line);
extern void exam_assert_eq_int(intmax_t a, intmax_t b, const char *file, size_t line);
extern void exam_assert_neq_int(intmax_t a, intmax_t b, const char *file, size_t line);
extern void exam_assert_lt_int(intmax_t a, intmax_t b, const char *file, size_t line);
extern void exam_assert_le_int(intmax_t a, intmax_t b, const char *file, size_t line);
extern void exam_assert_gt_int(intmax_t a, intmax_t b, const char *file, size_t line);
extern void exam_assert_ge_int(intmax_t a, intmax_t b, const char *file, size_t line);
extern void exam_assert_eq_uint(uintmax_t a, uintmax_t b, const char *file, size_t line);
extern void exam_assert_neq_uint(uintmax_t a, uintmax_t b, const char *file, size_t line);
extern void exam_assert_lt_uint(uintmax_t a, uintmax_t b, const char *file, size_t line);
extern void exam_assert_le_uint(uintmax_t a, uintmax_t b, const char *file, size_t line);
extern void exam_assert_gt_uint(uintmax_t a, uintmax_t b, const char *file, size_t line);
extern void exam_assert_ge_uint(uintmax_t a, uintmax_t b, const char *file, size_t line);
extern void exam_assert_eq_float(float a, float b, float eps, const char *file, size_t line);
extern void exam_assert_neq_float(float a, float b, float eps, const char *file, size_t line);
extern void exam_assert_lt_float(float a, float b, float eps, const char *file, size_t line);
extern void exam_assert_le_float(float a, float b, float eps, const char *file, size_t line);
extern void exam_assert_gt_float(float a, float b, float eps, const char *file, size_t line);
extern void exam_assert_ge_float(float a, float b, float eps, const char *file, size_t line);
extern void exam_assert_eq_double(double a, double b, double eps, const char *file, size_t line);
extern void exam_assert_neq_double(double a, double b, double eps, const char *file, size_t line);
extern void exam_assert_lt_double(double a, double b, double eps, const char *file, size_t line);
extern void exam_assert_le_double(double a, double b, double eps, const char *file, size_t line);
extern void exam_assert_gt_double(double a, double b, double eps, const char *file, size_t line);
extern void exam_assert_ge_double(double a, double b, double eps, const char *file, size_t line);
extern void exam_assert_eq_str(const char *a, const char *b, const char *file, size_t line);
extern void exam_assert_neq_str(const char *a, const char *b, const char *file, size_t line);
extern void exam_assert_neq_mem(const void *a, const void *b, size_t size, const char *file, size_t line);
extern void exam_assert_eq_mem(const void *a, const void *b, size_t size, const char *file, size_t line);
extern void exam_assert_in_range_int(intmax_t x, intmax_t min, intmax_t max, const char *file, size_t line);
extern void exam_assert_not_in_range_int(intmax_t x, intmax_t min, intmax_t max, const char *file, size_t line);
extern void exam_assert_in_range_uint(uintmax_t x, uintmax_t min, uintmax_t max, const char *file, size_t line);
extern void exam_assert_not_in_range_uint(uintmax_t x, uintmax_t min, uintmax_t max, const char *file, size_t line);
extern void exam_assert_in_range_float(float x, float min, float max, float eps, const char *file, size_t line);
extern void exam_assert_not_in_range_float(float x, float min, float max, float eps, const char *file, size_t line);
extern void exam_assert_in_range_double(double x, double min, double max, double eps, const char *file, size_t line);
extern void exam_assert_not_in_range_double(double x, double min, double max, double eps, const char *file, size_t line);
extern void exam_assert_in_arr_int(intmax_t x, const intmax_t *arr, size_t count, const char *file, size_t line);
extern void exam_assert_not_in_arr_int(intmax_t x, const intmax_t *arr, size_t count, const char *file, size_t line);
extern void exam_assert_in_arr_uint(uintmax_t x, const uintmax_t *arr, size_t count, const char *file, size_t line);
extern void exam_assert_not_in_arr_uint(uintmax_t x, const uintmax_t *arr, size_t count, const char *file, size_t line);
extern void exam_assert_in_arr_float(float x, const float *arr, size_t count, float eps, const char *file, size_t line);
extern void exam_assert_not_in_arr_float(float x, const float *arr, size_t count, float eps, const char *file, size_t line);
extern void exam_assert_in_arr_double(double x, const double *arr, size_t count, double eps, const char *file, size_t line);
extern void exam_assert_not_in_arr_double(double x, const double *arr, size_t count, double eps, const char *file, size_t line);

extern struct exam_state exam_state;
extern int exam_run(const struct exam_filter *filter, size_t jobs);
extern void exam_register(struct exam_test *test);

extern int exam_cli_main(int argc, char **argv);
#ifdef __cplusplus
}
#endif // __cplusplus

#ifdef EXAM_IMPLEMENTATION
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <math.h>

// Util
struct exam_state exam_state = {
    {0}, // test_list

    NULL, // on_start
    NULL, // on_finish
    NULL, // on_test_start
    NULL, // on_test_finish

    0, // passed
    0, // failed
    0, // crashed
    0, // timed_out

    EXAM_DEFAULT_TIMEOUT_MS, // timeout_ms
};

EXAM_NORETURN static void exam_internal_child_exit(int code);
static void exam_internal_child_exit(int code)
{
    fflush(stdout);
    fflush(stderr);
    _Exit(code);
}

static bool exam_internal_in_child = false;

EXAM_NORETURN static void exam_internal_exit(int code);
static void exam_internal_exit(int code)
{
    if (exam_internal_in_child)
        exam_internal_child_exit(code);
    exit(code);
}

EXAM_NORETURN static void exam_internal_dief(const char *fmt, ...) EXAM_PRINTF(1, 2);
EXAM_NORETURN static void exam_internal_die_perror(const char *str);

static void exam_internal_dief(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);
    exam_internal_exit(EXIT_FAILURE);
}

static void exam_internal_die_perror(const char *str)
{
    perror(str);
    exam_internal_exit(EXIT_FAILURE);
}

// Platform
enum exam_exit_kind
{
    EXAM_EXIT_NORMAL,
    EXAM_EXIT_SIGNAL,
};

struct exam_exit
{
    enum exam_exit_kind kind;
    int code;
};

enum exam_read_status
{
    EXAM_READ_DATA,
    EXAM_READ_AGAIN,
    EXAM_READ_EOF,
    EXAM_READ_ERROR,
};

struct exam_process;

static size_t exam_internal_platform_cpu_count(void);
static bool exam_internal_platform_is_tty(void);
static bool exam_internal_platform_process_start(struct exam_process *proc, struct exam_test *test);
static void exam_internal_platform_process_close(struct exam_process *proc);
static void exam_internal_platform_process_kill(struct exam_process *proc);
static bool exam_internal_platform_exit_is_kill(const struct exam_exit *ex);
static void exam_internal_platform_maybe_run_child(void);
static enum exam_read_status exam_internal_platform_process_read(struct exam_process *proc, char *buf, size_t cap, size_t *n);
static void exam_internal_platform_process_wait_io(struct exam_process *procs, size_t count);
static bool exam_internal_platform_process_try_reap(struct exam_process *proc, struct exam_exit *out);
static uint64_t exam_internal_platform_now_ms(void);

#if defined(EXAM_POSIX)

#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#ifdef EXAM_APPLE
#include <mach/mach.h>
#include <mach/mach_host.h>
#endif

struct exam_process
{
    size_t test_index;
    pid_t pid;
    int out_fd;
    bool eof;
    uint64_t start_ms;
    bool timed_out;
};

#ifdef EXAM_APPLE
static size_t exam_internal_platform_cpu_count(void)
{
    host_basic_info_data_t info;
    mach_msg_type_number_t count = HOST_BASIC_INFO_COUNT;

    kern_return_t result = host_info(
        mach_host_self(),
        HOST_BASIC_INFO,
        (host_info_t)&info,
        &count
    );

    if (result != KERN_SUCCESS || info.avail_cpus <= 0)
        return 1;

    return (size_t)info.avail_cpus;
}
#else
static size_t exam_internal_platform_cpu_count(void)
{
    long cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
    if (cpu_count <= 0)
        return 1;

    return (size_t)cpu_count;
}
#endif

static bool exam_internal_platform_is_tty(void)
{
    return isatty(STDOUT_FILENO) || isatty(STDERR_FILENO);
}

static bool exam_internal_platform_process_start(struct exam_process *proc, struct exam_test *test)
{
    int fildes[2];
    if (pipe(fildes) == -1)
        return false;

    fflush(stdout);
    fflush(stderr);
    pid_t pid = fork();
    if (pid == -1) {
        int saved = errno;
        close(fildes[0]);
        close(fildes[1]);
        errno = saved;
        return false;
    }

    if (pid == 0) {
        exam_internal_in_child = true;

        setpgid(0, 0);
        close(fildes[0]);

        if (dup2(fildes[1], STDOUT_FILENO) == -1 ||
            dup2(fildes[1], STDERR_FILENO) == -1) {
            perror("dup2");
            _exit(EXIT_FAILURE);
        }

        int nul = open("/dev/null", O_RDONLY);
        if (nul == -1)
            exam_internal_dief("failed to open /dev/null: %s", strerror(errno));
        if (dup2(nul, STDIN_FILENO) == -1)
            exam_internal_dief("failed to redirect stdin: %s", strerror(errno));
        if (nul != STDIN_FILENO)
            close(nul);

        close(fildes[1]);

        fflush(stdout);
        setvbuf(stdout, NULL, _IONBF, 0);

        test->func();
        exam_internal_child_exit(EXIT_SUCCESS);
    }

    setpgid(pid, pid);
    close(fildes[1]);
    int flags = fcntl(fildes[0], F_GETFL);
    if (flags == -1 || fcntl(fildes[0], F_SETFL, flags | O_NONBLOCK) == -1) {
        int saved = errno;
        kill(pid, SIGKILL);
        waitpid(pid, NULL, 0);
        close(fildes[0]);
        errno = saved;
        return false;
    }

    proc->pid = pid;
    proc->out_fd = fildes[0];
    proc->eof = false;
    return true;
}

static void exam_internal_platform_process_close(struct exam_process *proc)
{
    close(proc->out_fd);
}

static void exam_internal_platform_process_kill(struct exam_process *proc)
{
    if (kill(-proc->pid, SIGKILL) == -1)
        kill(proc->pid, SIGKILL);
}

static bool exam_internal_platform_exit_is_kill(const struct exam_exit *ex)
{
    return ex->kind == EXAM_EXIT_SIGNAL && ex->code == SIGKILL;
}

static void exam_internal_platform_maybe_run_child(void)
{
    // No need to implement this on Posix
}

static enum exam_read_status exam_internal_platform_process_read(struct exam_process *proc, char *buf, size_t cap, size_t *n)
{
    for (;;) {
        ssize_t r = read(proc->out_fd, buf, cap);
        if (r > 0) {
            *n = (size_t)r;
            return EXAM_READ_DATA;
        }
        if (r == 0) {
            proc->eof = true;
            return EXAM_READ_EOF;
        }

        if (errno == EINTR)
            continue;
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return EXAM_READ_AGAIN;

        return EXAM_READ_ERROR;
    }
}

static void exam_internal_platform_process_wait_io(struct exam_process *procs, size_t count)
{
    struct pollfd *fds = (struct pollfd *)EXAM_CALLOC(count, sizeof(*fds));
    if (fds == NULL)
        exam_internal_die_perror("calloc");

    size_t live = 0;
    for (size_t i = 0; i < count; i++) {
        if (procs[i].eof) {
            fds[i].fd = -1;
            fds[i].events = 0;
        } else {
            fds[i].fd = procs[i].out_fd;
            fds[i].events = POLLIN;
            live++;
        }
    }

    if (live == 0) {
        poll(NULL, 0, 1); // portable sleep for 1ms
        EXAM_FREE(fds);
        return;
    }

    int result;
    do {
        result = poll(fds, (nfds_t)count, 50);
    } while (result == -1 && errno == EINTR);

    if (result == -1) {
        int saved = errno;
        EXAM_FREE(fds);
        errno = saved;
        exam_internal_die_perror("poll");
    }

    EXAM_FREE(fds);
}

static bool exam_internal_platform_process_try_reap(struct exam_process *proc, struct exam_exit *out)
{
    int status;
    pid_t pid;
    do {
        pid = waitpid(proc->pid, &status, WNOHANG);
    } while (pid == -1 && errno == EINTR);

    if (pid == -1)
        exam_internal_die_perror("waitpid");
    if (pid == 0)
        return false;

    if (WIFEXITED(status)) {
        out->kind = EXAM_EXIT_NORMAL;
        out->code = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        out->kind = EXAM_EXIT_SIGNAL;
        out->code = WTERMSIG(status);
    } else {
        exam_internal_dief("unexpected wait status");
    }

    return true;
}

static uint64_t exam_internal_platform_now_ms(void)
{
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
        exam_internal_die_perror("clock_gettime");

    return (uint64_t)ts.tv_sec * 1000u + (uint64_t)ts.tv_nsec / 1000000u;
}
#elif defined(EXAM_WINDOWS)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#include <signal.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#define EXAM_WIN_CHILD_ENV "EXAM_CHILD"
#define EXAM_WIN_CHILD_ID_SIZE 32
#define EXAM_WIN_ABORT_STATUS 0xC0000409u
#define EXAM_WIN_KILL_STATUS 0x45584D54u

struct exam_process
{
    size_t test_index;
    bool eof;
    HANDLE process;
    HANDLE out_read;
    uint64_t start_ms;
    bool timed_out;
};

static void exam_internal_win_die(const char *operation)
{
    DWORD error = GetLastError();

    LPSTR message = NULL;
    DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
                  FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS;

    FormatMessageA(
        flags,
        NULL,
        error,
        0,
        (LPSTR)&message,
        0,
        NULL
    );

    fprintf(stderr, "%s failed (error %lu): %s\n",
            operation,
            (unsigned long)error,
            message ? message : "unknown error");

    if (message)
        LocalFree(message);

    exam_internal_exit(EXIT_FAILURE);
}

static size_t exam_internal_platform_cpu_count(void)
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    if (si.dwNumberOfProcessors <= 0)
        return 1;

    return (size_t)si.dwNumberOfProcessors;
}

static bool exam_internal_platform_is_tty(void)
{
    static int cached = -1; // negative used for not set

    if (cached < 0) {
        cached = 0;
        HANDLE handles[2] = {
            GetStdHandle(STD_OUTPUT_HANDLE),
            GetStdHandle(STD_ERROR_HANDLE)
        };

        for (int i = 0; i < 2; i++) {
            DWORD mode;
            if (GetConsoleMode(handles[i], &mode) &&
                SetConsoleMode(handles[i], mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
                cached = 1;
        }
    }

    return cached == 1;
}

static HANDLE exam_internal_win_job = NULL;
static bool exam_internal_win_job_tried = false;

static HANDLE exam_internal_win_get_job(void)
{
    if (exam_internal_win_job_tried)
        return exam_internal_win_job;
    exam_internal_win_job_tried = true;

    HANDLE job = CreateJobObjectA(NULL, NULL);
    if (job == NULL)
        return NULL;

    JOBOBJECT_EXTENDED_LIMIT_INFORMATION info;
    memset(&info, 0, sizeof(info));
    info.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
    if (!SetInformationJobObject(job, JobObjectExtendedLimitInformation,
                                 &info, sizeof(info))) {
        CloseHandle(job);
        return NULL;
    }

    exam_internal_win_job = job;
    return job;
}

static bool exam_internal_platform_process_start(struct exam_process *proc, struct exam_test *test)
{
    DWORD saved;
    BOOL created;
    HANDLE job;

    char exe[MAX_PATH];
    char cmd[MAX_PATH + 4];
    char child_id[EXAM_WIN_CHILD_ID_SIZE];

    DWORD len = GetModuleFileNameA(NULL, exe, MAX_PATH);
    if (len == 0 || len >= MAX_PATH) {
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        return false;
    }

    int written = snprintf(cmd, sizeof(cmd), "\"%s\"", exe);
    if (written < 0 || (size_t)written >= sizeof(cmd)) {
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        return false;
    }

    written = snprintf(child_id, sizeof(child_id), "%zu", test->registration_index);
    if (written < 0 || (size_t)written >= sizeof(child_id)) {
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        return false;
    }

    SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL, TRUE };
    HANDLE out_r = NULL, out_w = NULL;
    HANDLE nul = INVALID_HANDLE_VALUE;

    if (!CreatePipe(&out_r, &out_w, &sa, 0))
        return false;
    if (!SetHandleInformation(out_r, HANDLE_FLAG_INHERIT, 0))
        goto fail;

    nul = CreateFileA("NUL", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (nul == INVALID_HANDLE_VALUE)
        goto fail;

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(si));
    memset(&pi, 0, sizeof(pi));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = nul;
    si.hStdOutput = out_w;
    si.hStdError = out_w;

    if (!SetEnvironmentVariableA(EXAM_WIN_CHILD_ENV, child_id))
        goto fail;

    created = CreateProcessA(NULL, cmd, NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
    saved = GetLastError();
    SetEnvironmentVariableA(EXAM_WIN_CHILD_ENV, NULL);
    if (!created) {
        SetLastError(saved);
        goto fail;
    }

    job = exam_internal_win_get_job();
    if (job != NULL)
        AssignProcessToJobObject(job, pi.hProcess);

    if (ResumeThread(pi.hThread) == (DWORD)-1) {
        saved = GetLastError();
        TerminateProcess(pi.hProcess, 1);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        SetLastError(saved);
        goto fail;
    }

    CloseHandle(pi.hThread);
    CloseHandle(out_w);
    CloseHandle(nul);

    proc->process = pi.hProcess;
    proc->out_read = out_r;
    proc->eof = false;
    return true;

fail:
    saved = GetLastError();
    if (out_r) CloseHandle(out_r);
    if (out_w) CloseHandle(out_w);
    if (nul != INVALID_HANDLE_VALUE) CloseHandle(nul);
    SetLastError(saved);
    return false;
}

static void exam_internal_platform_process_close(struct exam_process *proc)
{
    CloseHandle(proc->out_read);
    CloseHandle(proc->process);
}

static void exam_internal_platform_process_kill(struct exam_process *proc)
{
    TerminateProcess(proc->process, EXAM_WIN_KILL_STATUS);
}

static bool exam_internal_platform_exit_is_kill(const struct exam_exit *ex)
{
    return ex->kind == EXAM_EXIT_NORMAL && (DWORD)ex->code == EXAM_WIN_KILL_STATUS;
}

static void exam_internal_win_abort_handler(int sig)
{
    (void)sig;
    TerminateProcess(GetCurrentProcess(), EXAM_WIN_ABORT_STATUS);
}

static void exam_internal_platform_maybe_run_child(void)
{
    char id[EXAM_WIN_CHILD_ID_SIZE];
    DWORD n = GetEnvironmentVariableA(EXAM_WIN_CHILD_ENV, id, sizeof(id));
    if (n == 0 || n >= sizeof(id))
        return;

    SetEnvironmentVariableA(EXAM_WIN_CHILD_ENV, NULL);

    struct exam_test_list *list = &exam_state.test_list;
    char *end;
    errno = 0;
    unsigned long long idx = strtoull(id, &end, 10);
    if (errno == ERANGE || end == id || *end != '\0' || idx >= list->count)
        exam_internal_dief("invalid %s value '%s'", EXAM_WIN_CHILD_ENV, id);

    exam_internal_in_child = true;
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
    signal(SIGABRT, exam_internal_win_abort_handler);
#if defined(_MSC_VER)
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
#endif

    fflush(stdout);
    setvbuf(stdout, NULL, _IONBF, 0);

    list->data[idx].func();
    exam_internal_child_exit(EXIT_SUCCESS);
}

static enum exam_read_status exam_internal_platform_process_read(struct exam_process *proc, char *buf, size_t cap, size_t *n)
{
    DWORD avail = 0;
    if (!PeekNamedPipe(proc->out_read, NULL, 0, NULL, &avail, NULL)) {
        if (GetLastError() == ERROR_BROKEN_PIPE) {
            proc->eof = true;
            return EXAM_READ_EOF;
        }

        return EXAM_READ_ERROR;
    }
    if (avail == 0)
        return EXAM_READ_AGAIN;

    DWORD want = avail < cap ? avail : (DWORD)cap;
    DWORD got = 0;
    if (!ReadFile(proc->out_read, buf, want, &got, NULL)) {
        if (GetLastError() == ERROR_BROKEN_PIPE) {
            proc->eof = true;
            return EXAM_READ_EOF;
        }
        return EXAM_READ_ERROR;
    }
    if (got == 0) {
        proc->eof = true;
        return EXAM_READ_EOF;
    }

    *n = (size_t)got;
    return EXAM_READ_DATA;
}

static void exam_internal_platform_process_wait_io(struct exam_process *procs, size_t count)
{
    HANDLE handles[MAXIMUM_WAIT_OBJECTS];
    DWORD n = 0;

    for (size_t i = 0; i < count; i++) {
        DWORD avail = 0;
        if (!procs[i].eof &&
            PeekNamedPipe(procs[i].out_read, NULL, 0, NULL, &avail, NULL) && avail > 0)
            return;
        if (n < MAXIMUM_WAIT_OBJECTS)
            handles[n++] = procs[i].process;
    }

    if (WaitForMultipleObjects(n, handles, FALSE, 10) == WAIT_FAILED)
        exam_internal_win_die("WaitForMultipleObjects");
}

static int exam_internal_win_code_to_signal(DWORD code)
{
    switch (code) {
        case 0xC0000005u: /* STATUS_ACCESS_VIOLATION */
        case 0xC0000006u: /* STATUS_IN_PAGE_ERROR */
        case 0xC00000FDu: /* STATUS_STACK_OVERFLOW */
        case 0xC0000008u: /* STATUS_INVALID_HANDLE */
            return SIGSEGV;
        case 0xC000008Cu: /* STATUS_ARRAY_BOUNDS_EXCEEDED */
        case 0xC000008Du: /* STATUS_FLOAT_DENORMAL_OPERAND */
        case 0xC000008Eu: /* STATUS_FLOAT_DIVIDE_BY_ZERO */
        case 0xC000008Fu: /* STATUS_FLOAT_INEXACT_RESULT */
        case 0xC0000090u: /* STATUS_FLOAT_INVALID_OPERATION */
        case 0xC0000091u: /* STATUS_FLOAT_OVERFLOW */
        case 0xC0000092u: /* STATUS_FLOAT_STACK_CHECK */
        case 0xC0000093u: /* STATUS_FLOAT_UNDERFLOW */
        case 0xC0000094u: /* STATUS_INTEGER_DIVIDE_BY_ZERO */
        case 0xC0000095u: /* STATUS_INTEGER_OVERFLOW */
            return SIGFPE;
        case 0xC000001Du: /* STATUS_ILLEGAL_INSTRUCTION */
        case 0xC0000096u: /* STATUS_PRIVILEGED_INSTRUCTION */
            return SIGILL;
        case 0xC0000409u: /* STATUS_STACK_BUFFER_OVERRUN */
        case 0xC0000374u: /* STATUS_HEAP_CORRUPTION */
            return SIGABRT;
        case 0xC000013Au: /* STATUS_CONTROL_C_EXIT */
            return SIGINT;
        default:
            return (int)code;
    }
}

static bool exam_internal_platform_process_try_reap(struct exam_process *proc, struct exam_exit *out)
{
    DWORD r = WaitForSingleObject(proc->process, 0);
    if (r == WAIT_TIMEOUT)
        return false;
    if (r != WAIT_OBJECT_0)
        exam_internal_win_die("WaitForSingleObject");

    DWORD code;
    if (!GetExitCodeProcess(proc->process, &code))
        exam_internal_win_die("GetExitCodeProcess");

    if ((code & 0xF0000000u) == 0xC0000000u) {
        out->kind = EXAM_EXIT_SIGNAL;
        out->code = exam_internal_win_code_to_signal(code);
    } else {
        out->kind = EXAM_EXIT_NORMAL;
        out->code = (int)code;
    }
    return true;
}

static uint64_t exam_internal_platform_now_ms(void)
{
    return (uint64_t)GetTickCount64();
}
#endif // EXAM_WINDOWS

// Asserts
static int exam_internal_test_cmp(const void *a, const void *b);
static bool exam_internal_str_cmp(const char *a, const char *b);

static const char *exam_internal_str_repr(const char *str);
static const char *exam_internal_str_quote(const char *str);

void exam_fail_test(const char *file, size_t line, const char *fmt, ...)
{
    if (file != NULL && line > 0)
        fprintf(stderr, "[%s:%zu] ", file, line);

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);
    exam_internal_exit(EXIT_FAILURE);
}

void exam_assert_true(bool res, const char *expression, const char *file, size_t line)
{
    if (!res)
        exam_fail_test(file, line,
                       "%s is not true",
                       expression);
}

void exam_assert_false(bool res, const char *expression, const char *file, size_t line)
{
    if (res)
        exam_fail_test(file, line,
                       "%s is not false",
                       expression);
}

#define EXAM_INTERNAL_DEF_CMP(op, sfx, type, fmt, rel, test) \
    void exam_assert_##op##_##sfx(type a, type b, const char *file, size_t line) \
    { \
        if (!(test)) \
            exam_fail_test(file, line, fmt " " rel " " fmt, a, b); \
    }

EXAM_INTERNAL_DEF_CMP(eq,  ptr, const void *, "%p", "!=", a == b)
EXAM_INTERNAL_DEF_CMP(neq, ptr, const void *, "%p", "==", a != b)

EXAM_INTERNAL_DEF_CMP(eq, int, intmax_t, "%jd", "!=", a == b)
EXAM_INTERNAL_DEF_CMP(neq, int, intmax_t, "%jd", "==", a != b)
EXAM_INTERNAL_DEF_CMP(lt, int, intmax_t, "%jd", ">=", a < b)
EXAM_INTERNAL_DEF_CMP(le, int, intmax_t, "%jd", ">", a <= b)
EXAM_INTERNAL_DEF_CMP(gt, int, intmax_t, "%jd", "<=", a > b)
EXAM_INTERNAL_DEF_CMP(ge, int, intmax_t, "%jd", "<", a >= b)
EXAM_INTERNAL_DEF_CMP(eq, uint, uintmax_t, "%ju", "!=", a == b)
EXAM_INTERNAL_DEF_CMP(neq, uint, uintmax_t, "%ju", "==", a != b)
EXAM_INTERNAL_DEF_CMP(lt, uint, uintmax_t, "%ju", ">=", a < b)
EXAM_INTERNAL_DEF_CMP(le, uint, uintmax_t, "%ju", ">", a <= b)
EXAM_INTERNAL_DEF_CMP(gt, uint, uintmax_t, "%ju", "<=", a > b)
EXAM_INTERNAL_DEF_CMP(ge, uint, uintmax_t, "%ju", "<", a >= b)

#define EXAM_INTERNAL_DEF_CMP_EPS(op, sfx, type, fmt, rel, test) \
    void exam_assert_##op##_##sfx(type a, type b, type eps, const char *file, size_t line) \
    { \
        if (!(test)) \
            exam_fail_test(file, line, fmt " " rel " " fmt, a, b); \
    }

#define EXAM_INTERNAL_DEF_FP_PREDICATES(sfx, type, fmt) \
    static bool exam_internal_##sfx##_cmp(type a, type b, type eps) \
    { \
        if (!isfinite(eps) || eps < 0) \
            exam_internal_dief("invalid epsilon: " fmt, eps); \
        \
        if (isnan(a) || isnan(b)) \
            return false; \
        if (isinf(a) && isinf(b)) \
            return (a < 0) == (b < 0); \
        \
        type diff = a - b; \
        diff = (diff > 0 ? diff : -diff); \
        if (isnan(diff) || isinf(diff)) \
            return false; \
        if (diff <= eps) \
            return true; \
        \
        type abs_a = (a > 0 ? a : -a); \
        type abs_b = (b > 0 ? b : -b); \
        type largest = (abs_a > abs_b ? abs_a : abs_b); \
        return diff <= eps * largest; \
    } \
    static bool exam_internal_##sfx##_in_range(type x, type min, type max, type eps) \
    { \
        return (exam_internal_##sfx##_cmp(x, min, eps) || x > min) && \
               (exam_internal_##sfx##_cmp(x, max, eps) || x < max); \
    } \
    static bool exam_internal_##sfx##_lt(type a, type b, type eps) \
    { \
        return a < b && !exam_internal_##sfx##_cmp(a, b, eps); \
    } \
    static bool exam_internal_##sfx##_le(type a, type b, type eps) \
    { \
        return a < b || (!isnan(a) && exam_internal_##sfx##_cmp(a, b, eps)); \
    }

EXAM_INTERNAL_DEF_FP_PREDICATES(float, float, "%.9g")
EXAM_INTERNAL_DEF_CMP_EPS(eq, float, float, "%.9g", "!=", exam_internal_float_cmp(a, b, eps))
EXAM_INTERNAL_DEF_CMP_EPS(neq, float, float, "%.9g", "==", !exam_internal_float_cmp(a, b, eps))
EXAM_INTERNAL_DEF_CMP_EPS(lt, float, float, "%.9g", ">=", exam_internal_float_lt(a, b, eps))
EXAM_INTERNAL_DEF_CMP_EPS(le, float, float, "%.9g", ">", exam_internal_float_le(a, b, eps))
EXAM_INTERNAL_DEF_CMP_EPS(gt, float, float, "%.9g", "<=", exam_internal_float_lt(b, a, eps))
EXAM_INTERNAL_DEF_CMP_EPS(ge, float, float, "%.9g", "<", exam_internal_float_le(b, a, eps))
EXAM_INTERNAL_DEF_FP_PREDICATES(double, double, "%.17g")
EXAM_INTERNAL_DEF_CMP_EPS(eq, double, double, "%.17g", "!=", exam_internal_double_cmp(a, b, eps))
EXAM_INTERNAL_DEF_CMP_EPS(neq, double, double, "%.17g", "==", !exam_internal_double_cmp(a, b, eps))
EXAM_INTERNAL_DEF_CMP_EPS(lt, double, double, "%.17g", ">=", exam_internal_double_lt(a, b, eps))
EXAM_INTERNAL_DEF_CMP_EPS(le, double, double, "%.17g", ">", exam_internal_double_le(a, b, eps))
EXAM_INTERNAL_DEF_CMP_EPS(gt, double, double, "%.17g", "<=", exam_internal_double_lt(b, a, eps))
EXAM_INTERNAL_DEF_CMP_EPS(ge, double, double, "%.17g", "<", exam_internal_double_le(b, a, eps))

void exam_assert_eq_str(const char *a, const char *b, const char *file, size_t line)
{
    if (!exam_internal_str_cmp(a, b))
        exam_fail_test(file, line,
                       "%s%s%s != %s%s%s",
                       exam_internal_str_quote(a), exam_internal_str_repr(a), exam_internal_str_quote(a),
                       exam_internal_str_quote(b), exam_internal_str_repr(b), exam_internal_str_quote(b));
}

void exam_assert_neq_str(const char *a, const char *b, const char *file, size_t line)
{
    if (exam_internal_str_cmp(a, b))
        exam_fail_test(file, line,
                       "%s%s%s == %s%s%s",
                       exam_internal_str_quote(a), exam_internal_str_repr(a), exam_internal_str_quote(a),
                       exam_internal_str_quote(b), exam_internal_str_repr(b), exam_internal_str_quote(b));
}

void exam_assert_eq_mem(const void *a, const void *b, size_t size, const char *file, size_t line)
{
    if (size == 0 || memcmp(a, b, size) == 0)
        return;

    const unsigned char *expected = (const unsigned char *)a;
    const unsigned char *actual = (const unsigned char *)b;

    size_t i = 0;
    while (expected[i] == actual[i])
        i++;

    exam_fail_test(file, line,
                   "memory differs at offset %zu: expected=0x%02x actual=0x%02x",
                   i, expected[i], actual[i]);
}

void exam_assert_neq_mem(const void *a, const void *b, size_t size, const char *file, size_t line)
{
    if (size == 0)
        return;

    if (memcmp(a, b, size) == 0)
        exam_fail_test(file, line,
                       "memory regions are equal (%zu bytes)",
                       size);
}

#define EXAM_INTERNAL_DEF_RANGE(sfx, type, fmt, inside) \
    void exam_assert_in_range_##sfx(type x, type min, type max, const char *file, size_t line) \
    { \
        if (min > max) \
            exam_internal_dief("invalid range [" fmt ", " fmt "]", min, max); \
        if (!(inside)) \
            exam_fail_test(file, line, \
                           fmt " is not within the range [" fmt ", " fmt "]", \
                           x, min, max); \
    } \
    void exam_assert_not_in_range_##sfx(type x, type min, type max, const char *file, size_t line) \
    { \
        if (min > max) \
            exam_internal_dief("invalid range [" fmt ", " fmt "]", min, max); \
        if ((inside)) \
            exam_fail_test(file, line, \
                           fmt " is within the range [" fmt ", " fmt "]", \
                           x, min, max); \
    }

EXAM_INTERNAL_DEF_RANGE(int,  intmax_t,  "%jd", x >= min && x <= max)
EXAM_INTERNAL_DEF_RANGE(uint, uintmax_t, "%ju", x >= min && x <= max)

#define EXAM_INTERNAL_DEF_RANGE_EPS(sfx, type, fmt, inside) \
    void exam_assert_in_range_##sfx(type x, type min, type max, type eps, const char *file, size_t line) \
    { \
        if (min > max) \
            exam_internal_dief("invalid range [" fmt ", " fmt "]", min, max); \
        if (!(inside)) \
            exam_fail_test(file, line, \
                           fmt " is not within the range [" fmt ", " fmt "]", \
                           x, min, max); \
    } \
    void exam_assert_not_in_range_##sfx(type x, type min, type max, type eps, const char *file, size_t line) \
    { \
        if (min > max) \
            exam_internal_dief("invalid range [" fmt ", " fmt "]", min, max); \
        if ((inside)) \
            exam_fail_test(file, line, \
                           fmt " is within the range [" fmt ", " fmt "]", \
                           x, min, max); \
    }

EXAM_INTERNAL_DEF_RANGE_EPS(float,  float,  "%.9g",  exam_internal_float_in_range(x, min, max, eps))
EXAM_INTERNAL_DEF_RANGE_EPS(double, double, "%.17g", exam_internal_double_in_range(x, min, max, eps))

#define EXAM_INTERNAL_DEF_ARR(sfx, type, fmt, match) \
    void exam_assert_in_arr_##sfx(type x, const type *arr, size_t count, const char *file, size_t line) \
    { \
        for (size_t i = 0; i < count; i++) { \
            if ((match)) \
                return; \
        } \
        exam_fail_test(file, line, \
                       fmt " not in %p (count=%zu)", \
                       x, (const void *)arr, count); \
    } \
    void exam_assert_not_in_arr_##sfx(type x, const type *arr, size_t count, const char *file, size_t line) \
    { \
        for (size_t i = 0; i < count; i++) { \
            if ((match)) \
                exam_fail_test(file, line, \
                               fmt " in %p (count=%zu)", \
                               x, (const void *)arr, count); \
        } \
    }

EXAM_INTERNAL_DEF_ARR(int,  intmax_t,  "%jd", arr[i] == x)
EXAM_INTERNAL_DEF_ARR(uint, uintmax_t, "%ju", arr[i] == x)

#define EXAM_INTERNAL_DEF_ARR_EPS(sfx, type, fmt, match) \
    void exam_assert_in_arr_##sfx(type x, const type *arr, size_t count, type eps, const char *file, size_t line) \
    { \
        for (size_t i = 0; i < count; i++) { \
            if ((match)) \
                return; \
        } \
        exam_fail_test(file, line, \
                       fmt " not in %p (count=%zu)", \
                       x, (const void *)arr, count); \
    } \
    void exam_assert_not_in_arr_##sfx(type x, const type *arr, size_t count, type eps, const char *file, size_t line) \
    { \
        for (size_t i = 0; i < count; i++) { \
            if ((match)) \
                exam_fail_test(file, line, \
                               fmt " in %p (count=%zu)", \
                               x, (const void *)arr, count); \
        } \
    }

EXAM_INTERNAL_DEF_ARR_EPS(float,  float,  "%.9g",  exam_internal_float_cmp(x, arr[i], eps))
EXAM_INTERNAL_DEF_ARR_EPS(double, double, "%.17g", exam_internal_double_cmp(x, arr[i], eps))

static int exam_internal_test_cmp(const void *a, const void *b)
{
    const struct exam_test *test_a = (const struct exam_test *)a;
    const struct exam_test *test_b = (const struct exam_test *)b;
    int result = strcmp(test_a->category, test_b->category);
    if (result == 0)
        result = strcmp(test_a->name, test_b->name);
    return result;
}

static bool exam_internal_str_cmp(const char *a, const char *b)
{
    if (a == NULL || b == NULL)
        return a == b;

    return strcmp(a, b) == 0;
}


static const char *exam_internal_str_repr(const char *str)
{
    if (str == NULL)
        return "NULL";

    return str;
}

static const char *exam_internal_str_quote(const char *str)
{
    if (str == NULL)
        return "";

    return "\"";
}

// Runner
static bool exam_internal_check_filter(const struct exam_test *test, const struct exam_filter *filter);

static void exam_internal_list_append(struct exam_test_list *list, const struct exam_test *test);
static void exam_internal_list_destroy(struct exam_test_list *list);
static void exam_internal_list_sort(struct exam_test_list *list);

static void exam_internal_reset_tests(void);

static void exam_internal_run_tests(struct exam_test_list *list, const struct exam_filter *filter, size_t jobs);
static struct exam_process exam_internal_start_test(struct exam_test *test, size_t idx);
static void exam_internal_finish_test(struct exam_test *test, const struct exam_exit *ex, bool timed_out);
static void exam_internal_read_output(struct exam_test *test, struct exam_process *proc);

int exam_run(const struct exam_filter *filter, size_t jobs)
{
    exam_internal_platform_maybe_run_child();

    exam_state.passed = 0;
    exam_state.failed = 0;
    exam_state.crashed = 0;
    exam_state.timed_out = 0;
    exam_internal_reset_tests();

    if (exam_state.on_start)
        exam_state.on_start();

    struct exam_test_list *list = &exam_state.test_list;
    exam_internal_run_tests(list, filter, jobs);

    if (exam_state.on_finish)
        exam_state.on_finish();

    if (exam_state.failed > 0 || exam_state.crashed > 0 || exam_state.timed_out > 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void exam_register(struct exam_test *test)
{
    if (test == NULL ||
        test->category == NULL ||
        test->name == NULL ||
        test->func == NULL)
        exam_internal_dief("tried to register invalid test");

    exam_internal_list_append(&exam_state.test_list, test);
}

static bool exam_internal_check_filter(const struct exam_test *test, const struct exam_filter *filter)
{
    if (filter == NULL)
        return true;

    bool out = true;

    const char *category_name = filter->category_name;
    if (category_name != NULL)
        out = out && (test->category != NULL &&
                      strcmp(test->category, category_name) == 0);

    const char *test_name = filter->test_name;
    if (test_name != NULL)
        out = out && (test->name != NULL &&
                     strcmp(test->name, test_name) == 0);

    return out;
}

static void exam_internal_list_append(struct exam_test_list *list, const struct exam_test *test)
{
    if (list->count == SIZE_MAX)
        exam_internal_dief("test list too large");

    size_t new_count = list->count + 1;
    if (list->data == NULL || new_count > list->capacity) {
        size_t new_cap = list->capacity;
        if (new_cap < 4) {
            new_cap = 4;
        } else {
            if (new_cap > SIZE_MAX / 2)
                exam_internal_dief("test list too large");

            new_cap *= 2;
        }
        if (new_cap < new_count)
            new_cap = new_count;
        if (new_cap > SIZE_MAX / sizeof(*list->data))
            exam_internal_dief("test list too large");

        struct exam_test *data = (struct exam_test *)EXAM_REALLOC(list->data, sizeof(*list->data) * new_cap);
        if (data == NULL)
            exam_internal_die_perror("EXAM_REALLOC");

        list->data = data;
        list->capacity = new_cap;
    }

    list->data[list->count] = *test;
    list->data[list->count].registration_index = list->count;
    list->count++;
}

static void exam_internal_list_destroy(struct exam_test_list *list)
{
    if (list->data == NULL)
        return;

    EXAM_FREE(list->data);
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

static void exam_internal_list_sort(struct exam_test_list *list)
{
    if (list->count <= 1)
        return;

    qsort(list->data, list->count, sizeof(*list->data), exam_internal_test_cmp);
}

static void exam_internal_reset_tests(void)
{
    struct exam_test_list *list = &exam_state.test_list;
    for (size_t i = 0; i < list->count; i++) {
        struct exam_test *test = &list->data[i];
        test->state = EXAM_TEST_NONE;
        test->exit_signal = 0;
        test->output_size = 0;
        test->output_truncated = false;
        test->output[0] = '\0';
    }
}

static void exam_internal_run_tests(struct exam_test_list *list, const struct exam_filter *filter, size_t jobs)
{
    if (list->count == 0)
        return;

    if (jobs == 0)
        jobs = exam_internal_platform_cpu_count();
    if (jobs > list->count)
        jobs = list->count;

    struct exam_process *running = (struct exam_process *)EXAM_CALLOC(jobs, sizeof(*running));
    if (running == NULL)
        exam_internal_die_perror("calloc");

    size_t next_idx = 0;
    size_t running_count = 0;
    while (next_idx < list->count || running_count > 0) {
        while (running_count < jobs && next_idx < list->count) {
            size_t idx = next_idx++;
            struct exam_test *test = &list->data[idx];
            if (!exam_internal_check_filter(test, filter))
                continue;

            running[running_count++] = exam_internal_start_test(test, idx);
        }

        if (running_count == 0)
            break;

        exam_internal_platform_process_wait_io(running, running_count);

        for (size_t i = 0; i < running_count; ++i)
            exam_internal_read_output(&list->data[running[i].test_index], &running[i]);

        for (size_t i = 0; i < running_count;) {
            struct exam_exit ex;
            if (!exam_internal_platform_process_try_reap(&running[i], &ex)) {
                i++;
                continue;
            }

            struct exam_test *test = &list->data[running[i].test_index];
            exam_internal_read_output(test, &running[i]);
            exam_internal_finish_test(test, &ex, running[i].timed_out);
            exam_internal_platform_process_close(&running[i]);

            running[i] = running[--running_count];
        }

        if (exam_state.timeout_ms > 0) {
            uint64_t now = exam_internal_platform_now_ms();
            for (size_t i = 0; i < running_count; i++) {
                if (running[i].timed_out)
                    continue;

                if (now - running[i].start_ms >= exam_state.timeout_ms) {
                    running[i].timed_out = true;
                    exam_internal_platform_process_kill(&running[i]);
                }
            }
        }
    }

    EXAM_FREE(running);
}

static struct exam_process exam_internal_start_test(struct exam_test *test, size_t idx)
{
    if (test->state != EXAM_TEST_NONE)
        exam_internal_dief("tried to run test with an unexpected state: %d",
                   test->state);

    test->state = EXAM_TEST_RUNNING;
    test->output[0] = '\0';
    test->output_size = 0;
    test->output_truncated = false;

    if (exam_state.on_test_start)
        exam_state.on_test_start(test);

    struct exam_process proc = {0};
    proc.test_index = idx;
    if (!exam_internal_platform_process_start(&proc, test))
        exam_internal_dief("failed to start test");

    proc.start_ms = exam_internal_platform_now_ms();
    return proc;
}

static void exam_internal_finish_test(struct exam_test *test, const struct exam_exit *ex, bool timed_out)
{
    if (timed_out && exam_internal_platform_exit_is_kill(ex)) {
        test->state = EXAM_TEST_TIMEOUT;
    } else if (ex->kind == EXAM_EXIT_NORMAL) {
        test->state = (ex->code == EXIT_SUCCESS) ? EXAM_TEST_PASSED
                                                 : EXAM_TEST_FAILED;
    } else {
        test->state = EXAM_TEST_CRASHED;
        test->exit_signal = ex->code;
    }

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
        case EXAM_TEST_TIMEOUT:
            exam_state.timed_out++;
            break;
        default:
            exam_internal_dief("test finished with unexpected state: %d",
                               test->state);
    }

    if (exam_state.on_test_finish)
        exam_state.on_test_finish(test);
}

static void exam_internal_read_output(struct exam_test *test, struct exam_process *proc)
{
    char buf[256];
    for (;;) {
        size_t n = 0;
        enum exam_read_status status = exam_internal_platform_process_read(proc, buf, sizeof(buf), &n);
        if (status == EXAM_READ_AGAIN || status == EXAM_READ_EOF)
            return;
        if (status == EXAM_READ_ERROR)
            exam_internal_die_perror("read");

        size_t remaining = EXAM_TEST_OUTPUT_SIZE - test->output_size;
        size_t copy = n < remaining ? n : remaining;
        if (copy > 0) {
            memcpy(test->output + test->output_size, buf, copy);
            test->output_size += copy;
            test->output[test->output_size] = '\0';
        }

        if (n > copy)
            test->output_truncated = true;
    }
}

// Cli
#define EXAM_CLI_RESET  "\033[0m"
#define EXAM_CLI_RED    "\033[31m"
#define EXAM_CLI_GREEN  "\033[32m"
#define EXAM_CLI_YELLOW "\033[33m"
#define EXAM_CLI_CYAN   "\033[36m"

enum exam_cli_color
{
    EXAM_COLOR_AUTO = 0,
    EXAM_COLOR_ALWAYS,
    EXAM_COLOR_NEVER,
};

enum exam_cli_action
{
    EXAM_ACTION_RUN = 0,
    EXAM_ACTION_LIST,
};

static struct {
    size_t jobs;
    enum exam_cli_action action;
    enum exam_cli_color color;
    struct exam_filter filter;
} exam_cli_state = {0};

static int exam_internal_cli_run(void);
static int exam_internal_cli_list(void);
static void exam_internal_cli_usage(FILE *stream);

static void exam_internal_cli_on_finish(void);
static void exam_internal_cli_on_test_finish(const struct exam_test *test);

static void exam_internal_cli_test_output(const struct exam_test *test);
static const char *exam_internal_cli_color(const char *color);
static bool exam_internal_cli_is_option(const char *str, const char *short_name, const char *long_name);
static bool exam_internal_cli_is_color(void);

int exam_cli_main(int argc, char **argv)
{
    // Init
    exam_cli_state.jobs = 1;
    exam_cli_state.action = EXAM_ACTION_RUN;
    exam_cli_state.color = EXAM_COLOR_AUTO;
    exam_cli_state.filter.category_name = NULL;
    exam_cli_state.filter.test_name = NULL;

    exam_state.on_finish = exam_internal_cli_on_finish;
    exam_state.on_test_finish = exam_internal_cli_on_test_finish;

    // Options
    int rc = EXIT_SUCCESS;
    for (int i = 1; i < argc; ++i) {
        if (exam_internal_cli_is_option(argv[i], "-j", "--jobs")) {
            size_t value = 0;

            if (i + 1 < argc && argv[i + 1][0] != '-') {
                const char *jobs_str = argv[++i];

                errno = 0;
                char *end;
                unsigned long long parsed = strtoull(jobs_str, &end, 10);
                if (errno == ERANGE || end == jobs_str || *end != '\0' || (size_t)parsed != parsed) {
                    fprintf(stderr, "invalid jobs count '%s'\n", jobs_str);
                    rc = EXIT_FAILURE;
                    goto cleanup;
                }

                value = (size_t)parsed;
            }

            exam_cli_state.jobs = value;
        } else if (exam_internal_cli_is_option(argv[i], "-l", "--list")) {
            exam_cli_state.action = EXAM_ACTION_LIST;
        } else if (exam_internal_cli_is_option(argv[i], "-t", "--timeout")) {
            if (i == argc - 1) {
                fprintf(stderr, "usage: --timeout SECS\n");
                rc = EXIT_FAILURE;
                goto cleanup;
            }

            const char *timeout_str = argv[++i];
            if (timeout_str[0] == '-') {
                fprintf(stderr, "usage: --timeout SECS\n");
                rc = EXIT_FAILURE;
                goto cleanup;
            }

            errno = 0;
            char *end;
            unsigned long long parsed = strtoull(timeout_str, &end, 10);
            if (errno == ERANGE || end == timeout_str || *end != '\0' ||
                parsed > UINT64_MAX / 1000) {
                fprintf(stderr, "invalid timeout '%s'\n", timeout_str);
                rc = EXIT_FAILURE;
                goto cleanup;
            }

            exam_state.timeout_ms = (uint64_t)parsed * 1000u;
        } else if (exam_internal_cli_is_option(argv[i], NULL, "--color")) {
            if (i == argc - 1) {
                fprintf(stderr, "usage: --color WHEN (can be auto, always or never)\n");
                rc = EXIT_FAILURE;
                goto cleanup;
            }

            const char *color_str = argv[++i];
            if (color_str[0] == '-') {
                fprintf(stderr, "usage: --color WHEN (can be auto, always or never)\n");
                rc = EXIT_FAILURE;
                goto cleanup;
            }

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
        } else if (exam_internal_cli_is_option(argv[i], "-n", "--name")) {
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
        } else if (exam_internal_cli_is_option(argv[i], "-c", "--category")) {
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
        } else if (exam_internal_cli_is_option(argv[i], "-h", "--help")) {
            rc = EXIT_SUCCESS;
            exam_internal_cli_usage(stdout);
            goto cleanup;
        } else {
            fprintf(stderr, "unknown option '%s'\n", argv[i]);
            exam_internal_cli_usage(stderr);
            rc = EXIT_FAILURE;
            goto cleanup;
        }
    }

    switch (exam_cli_state.action) {
        case EXAM_ACTION_RUN:
            rc = exam_internal_cli_run();
            break;
        case EXAM_ACTION_LIST:
            rc = exam_internal_cli_list();
            break;
        default:
            rc = EXIT_FAILURE;
            fprintf(stderr, "unexpected action %d\n", exam_cli_state.action);
            break;
    }

cleanup:
    exam_internal_list_destroy(&exam_state.test_list);
    return rc;
}

static int exam_internal_cli_run(void)
{
    int rc = exam_run(&exam_cli_state.filter, exam_cli_state.jobs);

    size_t ran = exam_state.passed + exam_state.failed +
                 exam_state.crashed + exam_state.timed_out;
    bool filtered = exam_cli_state.filter.category_name != NULL ||
                    exam_cli_state.filter.test_name != NULL;

    if (ran == 0 && filtered)
        return EXIT_SUCCESS;
    return rc;
}

static int exam_internal_cli_list(void)
{
    exam_internal_list_sort(&exam_state.test_list);

    size_t found = 0;
    for (size_t i = 0; i < exam_state.test_list.count; ++i) {
        const struct exam_test *test = &exam_state.test_list.data[i];
        if (!exam_internal_check_filter(test, &exam_cli_state.filter))
            continue;

        printf("%s%s%s/%s\n",
                exam_internal_cli_color(EXAM_CLI_CYAN),
                test->category,
                exam_internal_cli_color(EXAM_CLI_RESET),
                test->name);

        found ++;
    }

    printf("%zu tests found\n", found);
    return EXIT_SUCCESS;
}

static void exam_internal_cli_usage(FILE *stream)
{
    fprintf(stream,
           "usage: " EXAM_CLI_NAME " [options]\n"
           "options:\n"
           "    -j, --jobs N        run up to N tests at once (default: 1);\n"
           "                        without N, use the number of CPUs\n"
           "    -l, --list          list available tests\n"
           "    -t, --timeout SECS  kill tests running longer than SECS (default: 3);\n"
           "                        0 means no limit\n"
           "        --color WHEN    colorize output: auto, always, never\n"
           "    -h, --help          show this message\n"
           "filters (combine them to narrow the selection):\n"
           "    -n, --name NAME          test name\n"
           "    -c, --category CATEGORY  category name\n");
}

static void exam_internal_cli_on_finish(void)
{
    bool previous = false;

    if (exam_state.passed > 0) {
        printf("%zu passed", exam_state.passed);
        previous = true;
    }

    if (exam_state.failed > 0) {
        if (previous) printf(", ");
        printf("%zu failed", exam_state.failed);
        previous = true;
    }

    if (exam_state.crashed > 0) {
        if (previous) printf(", ");
        printf("%zu crashed", exam_state.crashed);
        previous = true;
    }

    if (exam_state.timed_out > 0) {
        if (previous) printf(", ");
        printf("%zu timed out", exam_state.timed_out);
        previous = true;
    }

    if (!previous)
        printf("no tests ran");

    printf("\n");
}

static void exam_internal_cli_on_test_finish(const struct exam_test *test)
{
    switch(test->state) {
        case EXAM_TEST_PASSED:
            fprintf(stdout,
                    "%s[PASS] %s/%s%s\n",
                    exam_internal_cli_color(EXAM_CLI_GREEN),
                    test->category,
                    test->name,
                    exam_internal_cli_color(EXAM_CLI_RESET));
            break;
        case EXAM_TEST_FAILED:
            fprintf(stderr,
                    "%s[FAIL] %s/%s%s\n",
                    exam_internal_cli_color(EXAM_CLI_RED),
                    test->category,
                    test->name,
                    exam_internal_cli_color(EXAM_CLI_RESET));
            exam_internal_cli_test_output(test);
            break;
        case EXAM_TEST_CRASHED:
            fprintf(stderr,
                    "%s[CRASH] %s/%s (signal %d)%s\n",
                    exam_internal_cli_color(EXAM_CLI_YELLOW),
                    test->category,
                    test->name,
                    test->exit_signal,
                    exam_internal_cli_color(EXAM_CLI_RESET));
            exam_internal_cli_test_output(test);
            break;
        case EXAM_TEST_TIMEOUT:
            fprintf(stderr,
                    "%s[TIMEOUT] %s/%s%s\n",
                    exam_internal_cli_color(EXAM_CLI_YELLOW),
                    test->category,
                    test->name,
                    exam_internal_cli_color(EXAM_CLI_RESET));
            exam_internal_cli_test_output(test);
            break;
        default:
            fprintf(stderr,
                    "%s unexpected state (%d)\n",
                    test->name,
                    test->state);
            break;
    }

}

static void exam_internal_cli_test_output(const struct exam_test *test)
{
    if (test->output_size == 0)
        return;

    const char *color = EXAM_CLI_RED;
    if (test->state == EXAM_TEST_CRASHED || test->state == EXAM_TEST_TIMEOUT)
        color = EXAM_CLI_YELLOW;

    fputs(exam_internal_cli_color(color), stderr);
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

    fputs(exam_internal_cli_color(EXAM_CLI_RESET), stderr);
}

static const char *exam_internal_cli_color(const char *color)
{
    if (exam_internal_cli_is_color())
        return color;

    return "";
}

static bool exam_internal_cli_is_option(const char *str, const char *short_name, const char *long_name)
{
    if (str == NULL)
        return false;

    if (short_name != NULL && strcmp(str, short_name) == 0)
        return true;
    if (long_name != NULL && strcmp(str, long_name) == 0)
        return true;

    return false;
}

static bool exam_internal_cli_is_color(void)
{
    if (exam_cli_state.color == EXAM_COLOR_NEVER)
        return false;
    if (exam_cli_state.color == EXAM_COLOR_ALWAYS)
        return true;

    return exam_internal_platform_is_tty();
}
#endif // EXAM_IMPLEMENTATION

#if defined(__cplusplus) && !defined(EXAM_NO_STL)
#include <algorithm>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

template <typename T, typename = void>
struct exam_internal_is_streamable : std::false_type {};

template <typename T>
struct exam_internal_is_streamable<
    T,
    decltype(void(std::declval<std::ostream &>() << std::declval<const T &>()))>
    : std::true_type {};

template <typename T>
typename std::enable_if<exam_internal_is_streamable<T>::value, std::string>::type
exam_internal_to_string(const T &value)
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

template <typename T>
typename std::enable_if<!exam_internal_is_streamable<T>::value && std::is_enum<T>::value, std::string>::type
exam_internal_to_string(const T &value)
{
    std::ostringstream stream;
    stream << +static_cast<typename std::underlying_type<T>::type>(value);
    return stream.str();
}

template <typename T>
typename std::enable_if<!exam_internal_is_streamable<T>::value && !std::is_enum<T>::value, std::string>::type
exam_internal_to_string(const T &)
{
    return "<unprintable>";
}

template <typename Container, typename Value>
void exam_assert_in_container(const Value &x, const Container &container, const char *file, size_t line)
{
    if (std::find(container.begin(), container.end(), x) == container.end())
        exam_fail_test(file, line,
                       "\"%s\" not in container",
                       exam_internal_to_string(x).c_str());
}

template <typename Container, typename Value>
void exam_assert_not_in_container(const Value &x, const Container &container, const char *file, size_t line)
{
    if (std::find(container.begin(), container.end(), x) != container.end())
        exam_fail_test(file, line,
                       "\"%s\" in container",
                       exam_internal_to_string(x).c_str());
}

template <typename K, typename Map>
void exam_assert_key_in_map(const K &key, const Map &map, const char *file, size_t line)
{
    if (map.find(key) == map.end())
        exam_fail_test(file, line,
                       "key \"%s\" not in map",
                       exam_internal_to_string(key).c_str());
}

template <typename K, typename Map>
void exam_assert_key_not_in_map(const K &key, const Map &map, const char *file, size_t line)
{
    if (map.find(key) != map.end())
        exam_fail_test(file, line,
                       "key \"%s\" in map",
                       exam_internal_to_string(key).c_str());
}

template <typename V, typename Map>
void exam_assert_val_in_map(const V &val, const Map &map, const char *file, size_t line)
{
    for (const auto &entry : map)
        if (entry.second == val)
            return;

    exam_fail_test(file, line,
                   "value \"%s\" not in map",
                   exam_internal_to_string(val).c_str());
}

template <typename V, typename Map>
void exam_assert_val_not_in_map(const V &val, const Map &map, const char *file, size_t line)
{
    for (const auto &entry : map)
        if (entry.second == val)
            exam_fail_test(file, line,
                           "value \"%s\" in map",
                           exam_internal_to_string(val).c_str());
}

template <typename K, typename V, typename Map>
void exam_assert_key_val_in_map(const K &key, const V &val, const Map &map, const char *file, size_t line)
{
    auto it = map.find(key);
    if (it == map.end())
        exam_fail_test(file, line,
                       "key \"%s\" not in map",
                       exam_internal_to_string(key).c_str());

    if (!(it->second == val))
        exam_fail_test(file, line,
                       "value at key \"%s\" is not \"%s\" in map",
                       exam_internal_to_string(key).c_str(), exam_internal_to_string(val).c_str());
}

template <typename K, typename V, typename Map>
void exam_assert_key_val_not_in_map(const K &key, const V &val, const Map &map, const char *file, size_t line)
{
    auto it = map.find(key);
    if (it == map.end())
        return;

    if (it->second == val)
        exam_fail_test(file, line,
                       "value at key \"%s\" is \"%s\" in map",
                       exam_internal_to_string(key).c_str(), exam_internal_to_string(val).c_str());
}
#endif // defined(__cplusplus) && !defined(EXAM_NO_STL)

#ifndef EXAM_NO_SHORT_NAMES
#define DEFINE_ASSERT_FUNC EXAM_DEFINE_ASSERT_FUNC
#define CALL_ASSERT_FUNC EXAM_CALL_ASSERT_FUNC

#define ASSERT_TRUE EXAM_ASSERT_TRUE
#define ASSERT_FALSE EXAM_ASSERT_FALSE
#define ASSERT_EQ_PTR EXAM_ASSERT_EQ_PTR
#define ASSERT_NEQ_PTR EXAM_ASSERT_NEQ_PTR
#define ASSERT_NULL EXAM_ASSERT_NULL
#define ASSERT_NON_NULL EXAM_ASSERT_NON_NULL
#define ASSERT_EQ_INT EXAM_ASSERT_EQ_INT
#define ASSERT_NEQ_INT EXAM_ASSERT_NEQ_INT
#define ASSERT_LT_INT EXAM_ASSERT_LT_INT
#define ASSERT_LE_INT EXAM_ASSERT_LE_INT
#define ASSERT_GT_INT EXAM_ASSERT_GT_INT
#define ASSERT_GE_INT EXAM_ASSERT_GE_INT
#define ASSERT_EQ_UINT EXAM_ASSERT_EQ_UINT
#define ASSERT_NEQ_UINT EXAM_ASSERT_NEQ_UINT
#define ASSERT_LT_UINT EXAM_ASSERT_LT_UINT
#define ASSERT_LE_UINT EXAM_ASSERT_LE_UINT
#define ASSERT_GT_UINT EXAM_ASSERT_GT_UINT
#define ASSERT_GE_UINT EXAM_ASSERT_GE_UINT
#define ASSERT_EQ_FLOAT EXAM_ASSERT_EQ_FLOAT
#define ASSERT_NEQ_FLOAT EXAM_ASSERT_NEQ_FLOAT
#define ASSERT_LT_FLOAT EXAM_ASSERT_LT_FLOAT
#define ASSERT_LE_FLOAT EXAM_ASSERT_LE_FLOAT
#define ASSERT_GT_FLOAT EXAM_ASSERT_GT_FLOAT
#define ASSERT_GE_FLOAT EXAM_ASSERT_GE_FLOAT
#define ASSERT_EQ_DOUBLE EXAM_ASSERT_EQ_DOUBLE
#define ASSERT_NEQ_DOUBLE EXAM_ASSERT_NEQ_DOUBLE
#define ASSERT_LT_DOUBLE EXAM_ASSERT_LT_DOUBLE
#define ASSERT_LE_DOUBLE EXAM_ASSERT_LE_DOUBLE
#define ASSERT_GT_DOUBLE EXAM_ASSERT_GT_DOUBLE
#define ASSERT_GE_DOUBLE EXAM_ASSERT_GE_DOUBLE
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

#if defined(__cplusplus) && !defined(EXAM_NO_STL)
#define ASSERT_IN_CONTAINER EXAM_ASSERT_IN_CONTAINER
#define ASSERT_NOT_IN_CONTAINER EXAM_ASSERT_NOT_IN_CONTAINER
#define ASSERT_KEY_IN_MAP EXAM_ASSERT_KEY_IN_MAP
#define ASSERT_KEY_NOT_IN_MAP EXAM_ASSERT_KEY_NOT_IN_MAP
#define ASSERT_VAL_IN_MAP EXAM_ASSERT_VAL_IN_MAP
#define ASSERT_VAL_NOT_IN_MAP EXAM_ASSERT_VAL_NOT_IN_MAP
#define ASSERT_KEY_VAL_IN_MAP EXAM_ASSERT_KEY_VAL_IN_MAP
#define ASSERT_KEY_VAL_NOT_IN_MAP EXAM_ASSERT_KEY_VAL_NOT_IN_MAP
#endif // defined(__cplusplus) && !defined(EXAM_NO_STL)

#define DEFINE_TEST EXAM_DEFINE_TEST
#define REGISTER_TEST EXAM_REGISTER_TEST
#endif // EXAM_NO_SHORT_NAMES
#endif // EXAM_H
