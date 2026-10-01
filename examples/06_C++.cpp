#include <iostream>
#include <vector>
#include <unordered_map>

#define EXAM_IMPLEMENTATION
#include "exam.h"

DEFINE_TEST(stl, vec)
{
    std::vector<int> nums {-1, 20, 5, 3};

    ASSERT_IN_CONTAINER(-1, nums);
    ASSERT_IN_CONTAINER(20, nums);
    ASSERT_IN_CONTAINER(5, nums);
    ASSERT_IN_CONTAINER(3, nums);

    ASSERT_NOT_IN_CONTAINER(0, nums);
    ASSERT_NOT_IN_CONTAINER(10, nums);
    ASSERT_NOT_IN_CONTAINER(42, nums);
}

DEFINE_TEST(stl, unordered_map)
{
    std::unordered_map<std::string, int> nums {
        {"first", 1},
        {"second", 2},
        {"third", 3}
    };

    ASSERT_KEY_IN_MAP("first", nums);
    ASSERT_KEY_IN_MAP("third", nums);
    ASSERT_KEY_NOT_IN_MAP("fourth", nums);

    ASSERT_VAL_IN_MAP(1, nums);
    ASSERT_VAL_IN_MAP(3, nums);
    ASSERT_VAL_NOT_IN_MAP(0, nums);
    ASSERT_VAL_NOT_IN_MAP(4, nums);

    ASSERT_KEY_VAL_IN_MAP("first", 1, nums);
    ASSERT_KEY_VAL_IN_MAP("second", 2, nums);

    ASSERT_KEY_VAL_NOT_IN_MAP("first", 2, nums);
    ASSERT_KEY_VAL_NOT_IN_MAP("fourth", 4, nums);
}

int main(int argc, char **argv)
{
    return exam_cli_main(argc, argv);
}
