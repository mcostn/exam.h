#define EXAM_SOURCE
#include "exam.h"

#include <stdio.h>

static void on_start(void)
{
    printf("Starting tests...\n");
}

static void on_finish(void)
{
    printf(
        "Finished: %zu passed, %zu failed, %zu crashed\n",
        exam_state.passed,
        exam_state.failed,
        exam_state.crashed
    );
}

static void on_test_start(const struct exam_test *test)
{
    printf("Running %s/%s...\n", test->category, test->name);
}

static void on_test_finish(const struct exam_test *test)
{
    printf(
        "Finished %s/%s (state=%d)\n",
        test->category,
        test->name,
        test->state
    );
}

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
    exam_state.on_start = on_start;
    exam_state.on_finish = on_finish;
    exam_state.on_test_start = on_test_start;
    exam_state.on_test_finish = on_test_finish;

    return exam_run(NULL, 1);
}
