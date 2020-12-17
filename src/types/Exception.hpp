#pragma once

#include <exception>
#include <string>
#include <stdint.h>

class Exception : public std::exception
{
public:
    explicit Exception(const std::string& errMessage = "Try Exception");
    explicit Exception(const std::exception& e);

    const char* what() const noexcept override { return errMessage.c_str(); }

private:
    std::string errMessage;
};
