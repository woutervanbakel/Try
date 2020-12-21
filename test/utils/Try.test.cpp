#include "gtest/gtest.h"
#include "utils/Try.hpp"

class TryTest : public testing::Test {
protected:
    void SetUp() override {
    }
};

const int number42() {
    return 42;
}

const int lessThan42(const int &v) {
    if (v >= number42()) { 
        throw std::domain_error("Bigger than 42");
    }
    return v;
}

const int multiply(const int &v) {
    return (v * 2);
}


TEST_F(TryTest, isSuccess) {
    auto t = Try<std::string>::Of([]() { return "hello"; });
    EXPECT_EQ(t.IsSuccess(), true);
    EXPECT_EQ(t.IsFailure(), false);
}

TEST_F(TryTest, isFailure) {
    auto t = Try<std::string>::Of([]() {
        throw Exception();
        return "";
    });
    EXPECT_EQ(t.IsFailure(), true);
    EXPECT_EQ(t.IsSuccess(), false);
}

TEST_F(TryTest, valueOfFailureThrows) {
    auto t = Try<int>::Of([]() {
        throw Exception("This fails");
        return -1;
    });
    EXPECT_THROW(t.Value(), Exception);
}

TEST_F(TryTest, ErrorOnFailingTry) {
    const auto error = "error";
    auto t = Try<std::string>::Of([error]() {
        throw Exception(error);
        return "";
    });
    EXPECT_STREQ(t.Error().what(), error);
}

TEST_F(TryTest, ErrorOfSuccessThrows) {
    auto t = Try<bool>::Of([]() { return true; });
    EXPECT_THROW(t.Error(), std::exception);
}

TEST_F(TryTest, TryWithStandardExceptionContainsMessage) {
    const auto error42 = "Domain error 42";
    auto t = Try<std::string>::Of([error42]() {
        throw std::domain_error(error42);
        return "";
    });
    EXPECT_STREQ(t.Error().what(), error42);
}

TEST_F(TryTest, mapWithLambda) {
    const int number = 42;
    auto t = Try<int>::Of([]() { return number; })
                .Map<int>([](const int &n) { return (n * 2); });
    EXPECT_EQ(t.Value(), (number * 2));
}

TEST_F(TryTest, mapWithFunctions) {
    auto t = Try<int>::Of(number42)
                .Map(multiply);
    EXPECT_EQ(t.Value(), multiply(number42()));
}

TEST_F(TryTest, TryWithMultipleMaps) {
    auto t = Try<int>::Of(number42)
                .Map(multiply)
                .Map(multiply);
    EXPECT_EQ(t.Value(), multiply(multiply(number42())));
}

TEST_F(TryTest, TryWithMapAndOrElse) {
    auto t = Try<int>::Of(number42)
                .Map(multiply)
                .Map(lessThan42)
                .OrElse(24);
    EXPECT_EQ(t, 24);
}



