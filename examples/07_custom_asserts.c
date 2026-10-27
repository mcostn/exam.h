#define EXAM_IMPLEMENTATION
#include "exam.h"

#include <stdlib.h>

struct stack
{
    int *data;
    size_t len, cap;
};

static void stack_init(struct stack *s)
{
    s->data = NULL;
    s->len = s->cap = 0;
}

static void stack_push(struct stack *s, int v)
{
    if (s->len == s->cap) {
        s->cap = s->cap ? s->cap * 2 : 4;
        s->data = (int *)realloc(s->data, s->cap * sizeof(int));
    }
    s->data[s->len++] = v;
}

static void stack_free(struct stack *s)
{
    free(s->data);
    stack_init(s);
}

// Custom Asserts
DEFINE_ASSERT_FUNC(assert_stack_len, const struct stack *s, size_t len)
{
    if (s->len != len)
        exam_fail_test(file, line,
                       "stack has %zu items, expected %zu",
                       s->len, len);
}

#define ASSERT_STACK_LEN(stack, len) CALL_ASSERT_FUNC(assert_stack_len, (stack), (len))

DEFINE_ASSERT_FUNC(stack_contains, const struct stack *s, int v)
{
    for (size_t i = 0; i < s->len; i++) {
        if (s->data[i] == v)
            return;
    }

    exam_fail_test(file, line,
                   "stack does not have %d",
                   v);
}

#define ASSERT_STACK_CONTAINS(stack, v) CALL_ASSERT_FUNC(stack_contains, (stack), (v))

// Tests that should pass
EXAM_DEFINE_TEST(stack, length)
{
    struct stack s;
    stack_init(&s);

    ASSERT_STACK_LEN(&s, 0);
    stack_push(&s, 10);
    stack_push(&s, 20);
    ASSERT_STACK_LEN(&s, 2);

    stack_free(&s);
}

EXAM_DEFINE_TEST(stack, contains)
{
    struct stack s;
    stack_init(&s);
    stack_push(&s, 10);
    stack_push(&s, 20);

    ASSERT_STACK_CONTAINS(&s, 10);
    ASSERT_STACK_CONTAINS(&s, 20);

    stack_free(&s);
}

// Tests that should fail
EXAM_DEFINE_TEST(failures, length)
{
    struct stack s;
    stack_init(&s);
    stack_push(&s, 1);
    ASSERT_STACK_LEN(&s, 3);
}

EXAM_DEFINE_TEST(failures, contains)
{
    struct stack s;
    stack_init(&s);
    stack_push(&s, 1);
    ASSERT_STACK_CONTAINS(&s, 99);
}

int main(int argc, char **argv)
{
    return exam_cli_main(argc, argv);
}
