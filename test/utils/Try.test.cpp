#include "gtest/gtest.h"
#include "utils/Try.hpp"

class TryTest : public testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(TryTest, isSuccess) {
    auto t = Try<std::string>::Of([]() { return "hello"; });
    EXPECT_EQ(t.IsSuccess(), true);
}

TEST_F(TryTest, isFailure) {
    auto t = Try<std::string>::Of([]() {
        throw std::exception();
        return "";
    });
    EXPECT_EQ(t.IsFailure(), true);
}


