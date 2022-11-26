get_filename_component(PACKAGE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set (TEST_EXECUTABLE "${PACKAGE_NAME}_test")

project(
    ${PACKAGE_NAME}
    VERSION 1
)

add_library(
    ${PACKAGE_NAME} STATIC
    solution.cxx
)

target_include_directories(
    ${PACKAGE_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    ${TEST_EXECUTABLE}
    solution.cxx
    solution_test.cxx
)

target_link_libraries(
    ${TEST_EXECUTABLE}
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TEST_EXECUTABLE})
