#define EXAM_NO_SHORT_NAMES
#define EXAM_SOURCE
#include "exam.h"

EXAM_DEFINE_TEST(math, addition)
{
    EXAM_ASSERT_EQ_INT(1 + 1, 2);
}

EXAM_DEFINE_TEST(math, subtraction)
{
    EXAM_ASSERT_EQ_INT(5 - 2, 3);
}

int main(int argc, char **argv)
{
    return exam_cli_main(argc, argv);
}
