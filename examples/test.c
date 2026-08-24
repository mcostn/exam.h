#define EXAM_SHORT_NAMES
#define EXAM_SOURCE
#include "exam.h"

DEFINE_TEST(math, add)
{
    ASSERT_EQ_INT(1 + 2, 3);
    ASSERT_EQ_UINT(10 + 20, 30);
}

DEFINE_TEST(math, sub)
{
    ASSERT_EQ_INT(1 - 2, -1);
    ASSERT_EQ_UINT(20 - 10, 10);
}

int main(void)
{
    return 0;
}
