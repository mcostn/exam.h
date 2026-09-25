#define EXAM_SOURCE
#define EXAM_NO_AUTO_REGISTRATION
#include "../exam.h"

EXAM_DEFINE_TEST(math, addition)
{
    EXAM_ASSERT_EQ_INT(2 + 2, 4);
}

EXAM_DEFINE_TEST(math, subtraction)
{
    EXAM_ASSERT_EQ_INT(10 - 3, 7);
}

int main(void)
{
    EXAM_REGISTER_TEST(math, addition);
    EXAM_REGISTER_TEST(math, subtraction);

    return exam_run(NULL, 1);
}
