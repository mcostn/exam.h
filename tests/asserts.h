#include "exam.h"

DEFINE_TEST(assert, true)
{
    ASSERT_TRUE(true);
}

DEFINE_TEST(assert, false)
{
    ASSERT_FALSE(false);
}

DEFINE_TEST(assert, true_expression)
{
    int a = 10;
    int b = 20;
    ASSERT_TRUE(a < b);
}

DEFINE_TEST(assert, false_expression)
{
    int a = 10;
    int b = 20;
    ASSERT_FALSE(a > b);
}

DEFINE_TEST(assert, ptr_equal_same)
{
    int value = 0;
    ASSERT_EQ_PTR(&value, &value);
}

DEFINE_TEST(assert, ptr_not_equal)
{
    int a = 0;
    int b = 0;
    ASSERT_NEQ_PTR(&a, &b);
}

DEFINE_TEST(assert, ptr_null_null)
{
    ASSERT_EQ_PTR(NULL, NULL);
}

DEFINE_TEST(assert, ptr_null)
{
    ASSERT_NULL(NULL);
}

DEFINE_TEST(assert, ptr_non_null)
{
    int value = 0;
    ASSERT_NON_NULL(&value);
}

DEFINE_TEST(assert, ptr_null_non_null)
{
    int value = 0;
    ASSERT_NEQ_PTR(NULL, &value);
    ASSERT_NEQ_PTR(&value, NULL);
}

DEFINE_TEST(assert, int_equal_zero)
{
    ASSERT_EQ_INT(0, 0);
}

DEFINE_TEST(assert, int_equal_positive)
{
    ASSERT_EQ_INT(42, 42);
}

DEFINE_TEST(assert, int_equal_negative)
{
    ASSERT_EQ_INT(-42, -42);
}

DEFINE_TEST(assert, int_not_equal)
{
    ASSERT_NEQ_INT(1, 2);
}

DEFINE_TEST(assert, int_min)
{
    ASSERT_EQ_INT(INTMAX_MIN, INTMAX_MIN);
}

DEFINE_TEST(assert, int_max)
{
    ASSERT_EQ_INT(INTMAX_MAX, INTMAX_MAX);
}

DEFINE_TEST(assert, int_min_max_differ)
{
    ASSERT_NEQ_INT(INTMAX_MIN, INTMAX_MAX);
}

DEFINE_TEST(assert, int_negative_zero)
{
    ASSERT_EQ_INT(0, -0);
}

DEFINE_TEST(assert, uint_equal_zero)
{
    ASSERT_EQ_UINT(0, 0);
}

DEFINE_TEST(assert, uint_equal_positive)
{
    ASSERT_EQ_UINT(42, 42);
}

DEFINE_TEST(assert, uint_not_equal)
{
    ASSERT_NEQ_UINT(1, 2);
}

DEFINE_TEST(assert, uint_max)
{
    ASSERT_EQ_UINT(UINTMAX_MAX, UINTMAX_MAX);
}

DEFINE_TEST(assert, uint_zero_max_differ)
{
    ASSERT_NEQ_UINT(0, UINTMAX_MAX);
}

DEFINE_TEST(assert, str_equal)
{
    ASSERT_EQ_STR("hello", "hello");
}

DEFINE_TEST(assert, str_not_equal)
{
    ASSERT_NEQ_STR("hello", "world");
}

DEFINE_TEST(assert, str_empty)
{
    ASSERT_EQ_STR("", "");
}

DEFINE_TEST(assert, str_equal_different_buffers)
{
    char a[] = "hello";
    char b[] = "hello";
    ASSERT_EQ_STR(a, b);
}

DEFINE_TEST(assert, str_different_buffers_are_not_ptr_equal)
{
    char a[] = "hello";
    char b[] = "hello";
    ASSERT_NEQ_PTR(a, b);
    ASSERT_EQ_STR(a, b);
}

DEFINE_TEST(assert, str_null_null)
{
    ASSERT_EQ_STR(NULL, NULL);
}

DEFINE_TEST(assert, str_null)
{
    ASSERT_EQ_STR(NULL, NULL);
}

DEFINE_TEST(assert, str_null_non_null)
{
    ASSERT_NEQ_STR(NULL, "hello");
}

DEFINE_TEST(assert, str_non_null_null)
{
    ASSERT_NEQ_STR("hello", NULL);
}

DEFINE_TEST(assert, str_single_character)
{
    ASSERT_EQ_STR("a", "a");
}

DEFINE_TEST(assert, str_long)
{
    ASSERT_EQ_STR(
        "this is a somewhat longer string used for testing",
        "this is a somewhat longer string used for testing"
    );
}

DEFINE_TEST(assert, mem_equal)
{
    const unsigned char a[] = { 1, 2, 3, 4 };
    const unsigned char b[] = { 1, 2, 3, 4 };
    ASSERT_EQ_MEM(a, b, sizeof(a));
}

DEFINE_TEST(assert, mem_not_equal)
{
    const unsigned char a[] = { 1, 2, 3, 4 };
    const unsigned char b[] = { 1, 2, 3, 5 };
    ASSERT_NEQ_MEM(a, b, sizeof(a));
}

DEFINE_TEST(assert, mem_difference_at_first_byte)
{
    const unsigned char a[] = { 1, 2, 3, 4 };
    const unsigned char b[] = { 5, 2, 3, 4 };
    ASSERT_NEQ_MEM(a, b, sizeof(a));
}

DEFINE_TEST(assert, mem_difference_at_last_byte)
{
    const unsigned char a[] = { 1, 2, 3, 4 };
    const unsigned char b[] = { 1, 2, 3, 5 };
    ASSERT_NEQ_MEM(a, b, sizeof(a));
}

DEFINE_TEST(assert, mem_single_byte)
{
    const unsigned char a[] = { 0xab };
    const unsigned char b[] = { 0xab };
    ASSERT_EQ_MEM(a, b, 1);
}

DEFINE_TEST(assert, mem_zero_size_equal)
{
    ASSERT_EQ_MEM(NULL, NULL, 0);
}

DEFINE_TEST(assert, mem_zero_size_different)
{
    int a = 1;
    int b = 2;
    ASSERT_EQ_MEM(&a, &b, 0);
}

DEFINE_TEST(assert, mem_large)
{
    unsigned char a[256];
    unsigned char b[256];
    for (size_t i = 0; i < sizeof(a); ++i) {
        a[i] = (unsigned char)i;
        b[i] = (unsigned char)i;
    }
    ASSERT_EQ_MEM(a, b, sizeof(a));
}

DEFINE_TEST(assert, float_equal)
{
    ASSERT_EQ_FLOAT(1.0f, 1.0f, 0.0f);
}

DEFINE_TEST(assert, float_not_equal)
{
    ASSERT_NEQ_FLOAT(1.0f, 2.0f, 0.0f);
}

DEFINE_TEST(assert, float_zero)
{
    ASSERT_EQ_FLOAT(0.0f, 0.0f, 0.0f);
}

DEFINE_TEST(assert, float_negative_zero)
{
    ASSERT_EQ_FLOAT(0.0f, -0.0f, 0.0f);
}

DEFINE_TEST(assert, float_absolute_epsilon)
{
    ASSERT_EQ_FLOAT(1.0f, 1.0001f, 0.001f);
}

DEFINE_TEST(assert, float_outside_epsilon)
{
    ASSERT_NEQ_FLOAT(1.0f, 1.1f, 0.001f);
}
DEFINE_TEST(assert, float_exact_epsilon)
{
    ASSERT_EQ_FLOAT(1.0f, 1.001f, 0.001f);
}

DEFINE_TEST(assert, float_relative_epsilon)
{
    ASSERT_EQ_FLOAT(1000000.0f, 1000000.5f, 0.000001f);
}

DEFINE_TEST(assert, float_nan_equal)
{
    ASSERT_EQ_FLOAT(NAN, NAN, 0.0f);
}

DEFINE_TEST(assert, float_inf_equal)
{
    ASSERT_EQ_FLOAT(INFINITY, INFINITY, 0.0f);
}

DEFINE_TEST(assert, float_negative_inf_equal)
{
    ASSERT_EQ_FLOAT(-INFINITY, -INFINITY, 0.0f);
}

DEFINE_TEST(assert, float_positive_negative_inf)
{
    ASSERT_NEQ_FLOAT(INFINITY, -INFINITY, 0.0f);
}

DEFINE_TEST(assert, float_nan_not_equal_number)
{
    ASSERT_NEQ_FLOAT(NAN, 1.0f, 0.0f);
}

DEFINE_TEST(assert, float_number_not_equal_nan)
{
    ASSERT_NEQ_FLOAT(1.0f, NAN, 0.0f);
}

DEFINE_TEST(assert, float_inf_not_equal_number)
{
    ASSERT_NEQ_FLOAT(INFINITY, 1.0f, 0.0f);
}

DEFINE_TEST(assert, int_range_middle)
{
    ASSERT_IN_RANGE_INT(5, 0, 10);
}

DEFINE_TEST(assert, int_range_min)
{
    ASSERT_IN_RANGE_INT(0, 0, 10);
}

DEFINE_TEST(assert, int_range_max)
{
    ASSERT_IN_RANGE_INT(10, 0, 10);
}

DEFINE_TEST(assert, int_range_single_value)
{
    ASSERT_IN_RANGE_INT(5, 5, 5);
}

DEFINE_TEST(assert, int_not_in_range_below)
{
    ASSERT_NOT_IN_RANGE_INT(-1, 0, 10);
}

DEFINE_TEST(assert, int_not_in_range_above)
{
    ASSERT_NOT_IN_RANGE_INT(11, 0, 10);
}

DEFINE_TEST(assert, int_range_negative)
{
    ASSERT_IN_RANGE_INT(-5, -10, 0);
}

DEFINE_TEST(assert, int_range_intmax)
{
    ASSERT_IN_RANGE_INT(INTMAX_MAX, INTMAX_MAX, INTMAX_MAX);
}

DEFINE_TEST(assert, int_range_intmin)
{
    ASSERT_IN_RANGE_INT(INTMAX_MIN, INTMAX_MIN, INTMAX_MIN);
}

DEFINE_TEST(assert, uint_range_middle)
{
    ASSERT_IN_RANGE_UINT(5, 0, 10);
}

DEFINE_TEST(assert, uint_range_min)
{
    ASSERT_IN_RANGE_UINT(0, 0, 10);
}

DEFINE_TEST(assert, uint_range_max)
{
    ASSERT_IN_RANGE_UINT(10, 0, 10);
}

DEFINE_TEST(assert, uint_range_single_value)
{
    ASSERT_IN_RANGE_UINT(5, 5, 5);
}

DEFINE_TEST(assert, uint_not_in_range_below)
{
    ASSERT_NOT_IN_RANGE_UINT(0, 1, 10);
}

DEFINE_TEST(assert, uint_not_in_range_above)
{
    ASSERT_NOT_IN_RANGE_UINT(11, 0, 10);
}

DEFINE_TEST(assert, uint_range_max_value)
{
    ASSERT_IN_RANGE_UINT(UINTMAX_MAX, UINTMAX_MAX, UINTMAX_MAX);
}

DEFINE_TEST(assert, float_range_middle)
{
    ASSERT_IN_RANGE_FLOAT(5.0f, 0.0f, 10.0f, 0.0f);
}

DEFINE_TEST(assert, float_range_min)
{
    ASSERT_IN_RANGE_FLOAT(0.0f, 0.0f, 10.0f, 0.0f);
}

DEFINE_TEST(assert, float_range_max)
{
    ASSERT_IN_RANGE_FLOAT(10.0f, 0.0f, 10.0f, 0.0f);
}

DEFINE_TEST(assert, float_range_single_value)
{
    ASSERT_IN_RANGE_FLOAT(5.0f, 5.0f, 5.0f, 0.0f);
}

DEFINE_TEST(assert, float_not_in_range_below)
{
    ASSERT_NOT_IN_RANGE_FLOAT(-1.0f, 0.0f, 10.0f, 0.0f);
}

DEFINE_TEST(assert, float_not_in_range_above)
{
    ASSERT_NOT_IN_RANGE_FLOAT(11.0f, 0.0f, 10.0f, 0.0f);
}

DEFINE_TEST(assert, float_range_epsilon_below)
{
    ASSERT_IN_RANGE_FLOAT(-0.0001f, 0.0f, 10.0f, 0.001f);
}

DEFINE_TEST(assert, float_range_epsilon_above)
{
    ASSERT_IN_RANGE_FLOAT(10.0001f, 0.0f, 10.0f, 0.001f);
}

DEFINE_TEST(assert, double_range_middle)
{
    ASSERT_IN_RANGE_DOUBLE(5.0, 0.0, 10.0, 0.0);
}

DEFINE_TEST(assert, double_range_min)
{
    ASSERT_IN_RANGE_DOUBLE(0.0, 0.0, 10.0, 0.0);
}

DEFINE_TEST(assert, double_range_max)
{
    ASSERT_IN_RANGE_DOUBLE(10.0, 0.0, 10.0, 0.0);
}

DEFINE_TEST(assert, double_range_single_value)
{
    ASSERT_IN_RANGE_DOUBLE(5.0, 5.0, 5.0, 0.0);
}

DEFINE_TEST(assert, double_not_in_range_below)
{
    ASSERT_NOT_IN_RANGE_DOUBLE(-1.0, 0.0, 10.0, 0.0);
}

DEFINE_TEST(assert, double_not_in_range_above)
{
    ASSERT_NOT_IN_RANGE_DOUBLE(11.0, 0.0, 10.0, 0.0);
}

DEFINE_TEST(assert, double_range_epsilon_below)
{
    ASSERT_IN_RANGE_DOUBLE(-0.0001, 0.0, 10.0, 0.001);
}

DEFINE_TEST(assert, double_range_epsilon_above)
{
    ASSERT_IN_RANGE_DOUBLE(10.0001, 0.0, 10.0, 0.001);
}

DEFINE_TEST(assert, int_array_first)
{
    const intmax_t values[] = { 10, 20, 30 };
    ASSERT_IN_ARR_INT(10, values, 3);
}

DEFINE_TEST(assert, int_array_middle)
{
    const intmax_t values[] = { 10, 20, 30 };
    ASSERT_IN_ARR_INT(20, values, 3);
}

DEFINE_TEST(assert, int_array_last)
{
    const intmax_t values[] = { 10, 20, 30 };
    ASSERT_IN_ARR_INT(30, values, 3);
}

DEFINE_TEST(assert, int_array_not_present)
{
    const intmax_t values[] = { 10, 20, 30 };
    ASSERT_NOT_IN_ARR_INT(40, values, 3);
}

DEFINE_TEST(assert, int_array_single)
{
    const intmax_t values[] = { 42 };
    ASSERT_IN_ARR_INT(42, values, 1);
    ASSERT_NOT_IN_ARR_INT(41, values, 1);
}

DEFINE_TEST(assert, int_array_empty)
{
    const intmax_t values[] = { 10, 20, 30 };
    ASSERT_NOT_IN_ARR_INT(10, values, 0);
}

DEFINE_TEST(assert, int_array_negative)
{
    const intmax_t values[] = { -10, -20, -30 };
    ASSERT_IN_ARR_INT(-20, values, 3);
}

DEFINE_TEST(assert, uint_array_first)
{
    const uintmax_t values[] = { 10, 20, 30 };
    ASSERT_IN_ARR_UINT(10, values, 3);
}

DEFINE_TEST(assert, uint_array_middle)
{
    const uintmax_t values[] = { 10, 20, 30 };
    ASSERT_IN_ARR_UINT(20, values, 3);
}

DEFINE_TEST(assert, uint_array_last)
{
    const uintmax_t values[] = { 10, 20, 30 };
    ASSERT_IN_ARR_UINT(30, values, 3);
}

DEFINE_TEST(assert, uint_array_not_present)
{
    const uintmax_t values[] = { 10, 20, 30 };
    ASSERT_NOT_IN_ARR_UINT(40, values, 3);
}

DEFINE_TEST(assert, uint_array_single)
{
    const uintmax_t values[] = { 42 };
    ASSERT_IN_ARR_UINT(42, values, 1);
    ASSERT_NOT_IN_ARR_UINT(41, values, 1);
}

DEFINE_TEST(assert, uint_array_empty)
{
    const uintmax_t values[] = { 10, 20, 30 };
    ASSERT_NOT_IN_ARR_UINT(10, values, 0);
}

DEFINE_TEST(assert, uint_array_max)
{
    const uintmax_t values[] = { 0, UINTMAX_MAX };
    ASSERT_IN_ARR_UINT(UINTMAX_MAX, values, 2);
}

DEFINE_TEST(assert, float_array_first)
{
    const float values[] = { 1.0f, 2.0f, 3.0f };
    ASSERT_IN_ARR_FLOAT(1.0f, values, 3, 0.0f);
}

DEFINE_TEST(assert, float_array_middle)
{
    const float values[] = { 1.0f, 2.0f, 3.0f };
    ASSERT_IN_ARR_FLOAT(2.0f, values, 3, 0.0f);
}

DEFINE_TEST(assert, float_array_last)
{
    const float values[] = { 1.0f, 2.0f, 3.0f };
    ASSERT_IN_ARR_FLOAT(3.0f, values, 3, 0.0f);
}

DEFINE_TEST(assert, float_array_not_present)
{
    const float values[] = { 1.0f, 2.0f, 3.0f };
    ASSERT_NOT_IN_ARR_FLOAT(4.0f, values, 3, 0.0f);
}

DEFINE_TEST(assert, float_array_epsilon)
{
    const float values[] = { 1.0f, 2.0f, 3.0f };
    ASSERT_IN_ARR_FLOAT(1.0001f, values, 3, 0.001f);
}

DEFINE_TEST(assert, float_array_outside_epsilon)
{
    const float values[] = { 1.0f, 2.0f, 3.0f };
    ASSERT_NOT_IN_ARR_FLOAT(1.1f, values, 3, 0.001f);
}

DEFINE_TEST(assert, float_array_empty)
{
    const float values[] = { 1.0f, 2.0f, 3.0f };
    ASSERT_NOT_IN_ARR_FLOAT(1.0f, values, 0, 0.0f);
}

DEFINE_TEST(assert, float_array_nan)
{
    const float values[] = { NAN };
    ASSERT_IN_ARR_FLOAT(NAN, values, 1, 0.0f);
}

DEFINE_TEST(assert, float_array_inf)
{
    const float values[] = { INFINITY };
    ASSERT_IN_ARR_FLOAT(INFINITY, values, 1, 0.0f);
}

DEFINE_TEST(assert, double_array_first)
{
    const double values[] = { 1.0, 2.0, 3.0 };
    ASSERT_IN_ARR_DOUBLE(1.0, values, 3, 0.0);
}

DEFINE_TEST(assert, double_array_middle)
{
    const double values[] = { 1.0, 2.0, 3.0 };
    ASSERT_IN_ARR_DOUBLE(2.0, values, 3, 0.0);
}

DEFINE_TEST(assert, double_array_last)
{
    const double values[] = { 1.0, 2.0, 3.0 };
    ASSERT_IN_ARR_DOUBLE(3.0, values, 3, 0.0);
}

DEFINE_TEST(assert, double_array_not_present)
{
    const double values[] = { 1.0, 2.0, 3.0 };
    ASSERT_NOT_IN_ARR_DOUBLE(4.0, values, 3, 0.0);
}

DEFINE_TEST(assert, double_array_epsilon)
{
    const double values[] = { 1.0, 2.0, 3.0 };
    ASSERT_IN_ARR_DOUBLE(1.0000001, values, 3, 0.000001);
}

DEFINE_TEST(assert, double_array_outside_epsilon)
{
    const double values[] = { 1.0, 2.0, 3.0 };
    ASSERT_NOT_IN_ARR_DOUBLE(1.1, values, 3, 0.000001);
}

DEFINE_TEST(assert, double_array_empty)
{
    const double values[] = { 1.0, 2.0, 3.0 };
    ASSERT_NOT_IN_ARR_DOUBLE(1.0, values, 0, 0.0);
}

DEFINE_TEST(assert, double_array_nan)
{
    const double values[] = { NAN };
    ASSERT_IN_ARR_DOUBLE(NAN, values, 1, 0.0);
}

DEFINE_TEST(assert, double_array_inf)
{
    const double values[] = { INFINITY };
    ASSERT_IN_ARR_DOUBLE(INFINITY, values, 1, 0.0);
}
