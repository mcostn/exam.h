#define EXAM_IMPLEMENTATION
#define EXAM_UNIT_TESTS
#define EXAM_NO_AUTO_REGISTRATION
#include "exam.h"

int main(int argc, char **argv)
{
    exam_register_unit_tests();
    return exam_cli_main(argc, argv);
}
