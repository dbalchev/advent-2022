cmake_minimum_required(VERSION 3.10)
project(
    advent-common-lib
    VERSION 1
)

add_library(
    advent-common-lib STATIC
    registry.cxx
)

# target_include_directories(
#     advent-common-lib
#     PUBLIC ${PROJECT_SOURCE_DIR}/include
# )

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    registry_test
    registry.cxx
    registry_test.cxx
)

target_link_libraries(
    registry_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(registry_test)
