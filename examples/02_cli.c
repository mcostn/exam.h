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

int main(int argc, char **argv)
{
    return exam_cli_main(argc, argv);
}
