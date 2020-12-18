#include <iostream>
#include "gtest/gtest.h"
#include "types/Exception.hpp"

TEST(Excpetion, initialTest) {
	EXPECT_EQ(0, 0);
}

TEST(ExceptionTest, ShouldReturnErrAsJson) {
    Exception ex("Exception desc");
    EXPECT_STREQ(ex.what(), "Exception desc");
}
