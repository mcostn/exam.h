#ifndef EXAM_H
#define EXAM_H

#include <stdlib.h> /* for exit() */
#include <string.h> /* for strcmp() */
#include <stdbool.h>

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
#endif /* EXAM_SHORT_NAMES */

#endif /* EXAM_H */
