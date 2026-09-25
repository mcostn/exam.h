#define EXAM_SOURCE
#include "../exam.h"

EXAM_DEFINE_TEST(math, addition)
{
    EXAM_ASSERT_EQ_INT(2 + 2, 4);
}

EXAM_DEFINE_TEST(math, multiplication)
{
    EXAM_ASSERT_EQ_INT(6 * 7, 42);
}

int main(void)
{
    return exam_run(NULL, 1);
}

