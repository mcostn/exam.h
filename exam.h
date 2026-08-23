#ifndef EXAM_H
#define EXAM_H

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

#define DEFINE_TEST EXAM_DEFINE_TEST
#endif /* EXAM_SHORT_NAMES */

#ifdef __cplusplus
extern "C" {
#endif
extern struct exam_state exam_state;
#ifdef __cplusplus
}
#endif

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
        exam_state.tests[idx].name = #test_name; \
        exam_state.tests[idx].func = exam_def_##category_name##_##test_name; \
        exam_state.tests[idx].file = __FILE__; \
        exam_state.tests[idx].line = __LINE__; \
    } \
    static void exam_def_##category_name##_##test_name(void)

struct exam_test
{
    char *name;
    void (*func)(void);
    char *file;
    size_t line;
};

struct exam_state
{
    struct exam_test *tests;
    size_t tests_count;
    size_t tests_capacity;
};
#endif /* EXAM_H */

#ifdef EXAM_SOURCE
struct exam_state exam_state = {0};
#endif /* EXAM_SOURCE */
