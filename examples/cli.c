#define EXAM_SHORT_NAMES
#define EXAM_SOURCE
#include "exam.h"

DEFINE_TEST(math, add)
{
    ASSERT_EQ_INT(2 + 1, 3);
}

DEFINE_TEST(math, sub)
{
    ASSERT_EQ_INT(2 - 1, 1);
}

DEFINE_TEST(strings, equal)
{
    ASSERT_EQ_STR("str1", "str1");
}

int main(int argc, char **argv)
{
    return exam_cli_main(argc, argv);
}
