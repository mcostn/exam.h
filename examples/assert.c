#define EXAM_SHORT_NAMES
#define EXAM_SOURCE
#include "exam.h"

int main(void)
{
    /* long names */
    EXAM_ASSERT_TRUE(1 != 1);
    EXAM_ASSERT_TRUE(true);
    EXAM_ASSERT_FALSE(false);
    EXAM_ASSERT_NULL(NULL);
    EXAM_ASSERT_NON_NULL((void *)1);
    EXAM_ASSERT_EQ_INT(-1, -1);
    EXAM_ASSERT_EQ_UINT(1, 1);
    EXAM_ASSERT_EQ_FLOAT(1.2f, 1.2f);
    EXAM_ASSERT_EQ_DOUBLE(1.2, 1.2);

    /* short names */
    ASSERT_TRUE(1 == 1);
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
    ASSERT_NULL(NULL);
    ASSERT_NON_NULL((void *)1);
    ASSERT_EQ_INT(-1, -1);
    ASSERT_EQ_UINT(1, 1);
    ASSERT_EQ_FLOAT(1.2f, 1.2f);
    ASSERT_EQ_DOUBLE(1.2, 1.2);

    return 0;
}
