set(PROJECT_SOURCES
    types/Exception.test.cpp
)

add_executable(${PROJECT_NAME}_test ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME}_test gtest gtest_main)