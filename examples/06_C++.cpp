#include <iostream>

#define EXAM_IMPLEMENTATION
#include "exam.h"

DEFINE_TEST(math, add)
{
    ASSERT_EQ_INT(1 + 1, 3);
}

DEFINE_TEST(string, compare)
{
    ASSERT_EQ_STR("abc", "abc");
}

int main()
{
    int rc = exam_run(NULL, 0);
    std::cout << (rc ? "Failed" : "Passed") << std::endl;
    return 0;
}
