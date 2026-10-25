#define EXAM_IMPLEMENTATION
#include "exam.h"

#include <stdlib.h>

#define ASSERT_STACK_LEN(stack_expr, expected_expr) \
    do { \
        const struct stack *stack_ = (stack_expr); \
        size_t expected_ = (size_t)(expected_expr); \
        EXAM_ASSERT_MSG(stack_->len == expected_, \
                        "stack has %zu items, expected %zu", \
                        stack_->len, expected_); \
    } while (0)

#define ASSERT_STACK_CONTAINS(s, value) \
    do { \
        int found = 0; \
        for (size_t i_ = 0; i_ < (s)->len; i_++) \
            if ((s)->data[i_] == (value)) \
                found = 1; \
        if (!found) \
            EXAM_FAIL("stack does not contain %d", (int)(value)); \
    } while (0)

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
