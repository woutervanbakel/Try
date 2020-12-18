cmake_minimum_required(VERSION 3.15)

project (Try CXX)
SET(CMAKE_CXX_STANDARD 11)

# Add googletest GIT submodule
add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(test)