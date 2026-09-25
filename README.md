# exam

A minimal, single-header unit testing library written in C99.


## Example

```c
#define EXAM_IMPLEMENTATION
#include "exam.h"

DEFINE_TEST(math, addition)
{
    ASSERT_EQ_INT(1 + 1, 2);
}

DEFINE_TEST(math, subtraction)
{
    ASSERT_EQ_INT(5 - 2, 1);
}

int main(void)
{
    return exam_run(NULL, 0);
}
```

Compile and run with:

```bash
cc -std=c99 -o test test.c
./test
```

## Integration

Put `exam.h` somewhere in your project and define `EXAM_IMPLEMENTATION` in **one** source file before including it:

```c
#define EXAM_IMPLEMENTATION
#include "exam.h"
```

In other source files, simply include the header normally:

```c
#include "exam.h"
```

