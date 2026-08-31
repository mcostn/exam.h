#define EXAM_SHORT_NAMES
#define EXAM_SOURCE
#define EXAM_CLI_NAME "cli"
#include "exam.h"

DEFINE_TEST(math, equal)
{
    ASSERT_EQ_INT(1, 1);
}

DEFINE_TEST(strings, equal)
{
    ASSERT_EQ_STR("str1", "str2");
}

DEFINE_TEST(math, add)
{
    ASSERT_EQ_INT(2 + 1, 3);
}

DEFINE_TEST(memory, ptr)
{
    int *p = NULL;
    *p = 10;
}

DEFINE_TEST(math, sub)
{
    ASSERT_EQ_INT(2 - 1, 1);
}

int main(int argc, char **argv)
{
    return exam_cli_main(argc, argv);
}
