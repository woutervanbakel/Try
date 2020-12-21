#include <iostream>
#include <stdexcept>
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
    Exception ex(std::invalid_argument("Invalid argument"));
    EXPECT_STREQ(ex.what(), "Invalid argument");
}
