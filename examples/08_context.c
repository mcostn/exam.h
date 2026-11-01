#define EXAM_IMPLEMENTATION
#include "exam.h"

#include <ctype.h>

static int count_words(const char *s)
{
    int words = 0, in_word = 0;
    for (; *s; s++) {
        if (isspace((unsigned char)*s)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }
    return words;
}

struct word_case
{
    const char *input;
    int expected;
};


DEFINE_TEST(words, table)
{
    static const struct word_case cases[] = {
        { "hello",          1 },
        { "hello world",    2 },
        { "  padded  ",     1 },
        { "tab\tseparated", 2 },
        { "a b c d",        3 }, //  should be 4
        { "",               0 },
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        WITH_CONTEXT("case %zu: \"%s\"", i, cases[i].input) {
            ASSERT_EQ_INT(count_words(cases[i].input), cases[i].expected);
        }
    }

    // No context here, so a failure on this line is not mislabeled.
    ASSERT_EQ_INT(count_words("one two"), 2);
}

int main(int argc, char **argv)
{
    return exam_cli_main(argc, argv);
}
