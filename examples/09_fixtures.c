#define EXAM_IMPLEMENTATION
#include "exam.h"

struct vec_fixture { int *data; size_t n; };

DEFINE_FIXTURE_SETUP(vec_fixture)
{
    exam_fixture->n = 4;
    exam_fixture->data = (int *)calloc(exam_fixture->n, sizeof(int));
    ASSERT_NON_NULL(exam_fixture->data);
}

DEFINE_FIXTURE_TEARDOWN(vec_fixture)
{
    free(exam_fixture->data);
}

DEFINE_FIXTURE_TEST(vec_fixture, starts_zeroed)
{
    ASSERT_EQ_INT(exam_fixture->data[0], 0);
}

DEFINE_FIXTURE_TEST(vec_fixture, is_writable)
{
    exam_fixture->data[1] = 7;
    ASSERT_EQ_INT(exam_fixture->data[1], 7);
}

int main(int argc, char **argv)
{
    return exam_cli_main(argc, argv);
}
