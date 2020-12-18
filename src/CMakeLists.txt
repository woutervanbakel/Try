set(PROJECT_SOURCES
    types/Exception.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${PROJECT_SOURCES})

# Build the application target as a library so the test target can load it with gcov library
# Has to be done here because the project sources are only available in this dir
add_library(${PROJECT_NAME}_coverage ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME}_coverage ${CONAN_LIBS} gcov)
target_include_directories(${PROJECT_NAME}_coverage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME}_coverage PROPERTIES COMPILE_FLAGS --coverage)
