#include <gtest/gtest.h>

#include "example.h"

TEST(example_test, func_sum) {
    ASSERT_EQ(3, sum(1, 2));
}