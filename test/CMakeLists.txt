set(PROJECT_SOURCES
    types/Exception.test.cpp
)

add_executable(${PROJECT_NAME}_test ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME}_coverage gcov gtest gtest_main)
add_definitions(--coverage)
