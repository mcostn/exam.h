# exam

A minimal, single-header unit testing library for C and C++.


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

int main(int argc, char **argv)
{
    return exam_cli_main(argc, argv);
}
```

Compile and run with:

```bash
cc -o test test.c
./test
```

## Integration

Put `exam.h` somewhere in your project and define `EXAM_IMPLEMENTATION` in **one** source file before including it:

```c
#define EXAM_IMPLEMENTATION
#include "exam.h"
```

In other source files, simply include it normally.

## Compatibility

exam is designed to work across a wide range of environments. It has been tested on Linux, macOS and Windows with GCC, Clang, TCC and MSVC, in both C and C++.

## License

exam is released under the MIT License. See the `LICENSE` file for details.
