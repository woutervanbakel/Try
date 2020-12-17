#include "Exception.hpp"

Exception::Exception(const std::string &errMessage) :
    errMessage(errMessage) {}

Exception::Exception(const std::exception& e) :
    errMessage(e.what()) {}
