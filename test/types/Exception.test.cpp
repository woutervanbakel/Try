#include <iostream>
#include "gtest/gtest.h"
#include "types/Exception.hpp"

class ExceptionTest : public testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(ExceptionTest, WhatReturnTheMessage) {
    Exception ex("Exception 42");
    EXPECT_STREQ(ex.what(), "Exception 42");
}

TEST_F(ExceptionTest, ExceptionFromStdException) {
    EXPECT_NO_THROW(Exception ex(std::exception()));
}
