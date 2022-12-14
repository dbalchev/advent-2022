cmake_minimum_required(VERSION 3.10)

project(
    advent-2022
    VERSION 1
)

set(
    CMAKE_CXX_STANDARD 20
)
set (
    CXX_STANDARD_REQUIRED True
)

include(FetchContent)

FetchContent_Declare(
    gflags
    GIT_REPOSITORY https://github.com/gflags/gflags.git
    GIT_TAG v2.2.2
)
FetchContent_MakeAvailable(
    gflags
)

FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(
    GoogleTest
)

FetchContent_Declare(
    RangeV3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_TAG 0.12.0
)
FetchContent_MakeAvailable(
    RangeV3
)
enable_testing()

include_directories($<TARGET_PROPERTY:gflags,INTERFACE_INCLUDE_DIRECTORIES>)

file(
    GLOB DAYS_TO_ADD LIST_DIRECTORIES true RELATIVE ${PROJECT_SOURCE_DIR} day_*
)

foreach(DAY IN LISTS DAYS_TO_ADD)
    add_subdirectory(${DAY})
    include_directories($<TARGET_PROPERTY:${DAY},INTERFACE_INCLUDE_DIRECTORIES>)
    link_libraries(${DAY})
endforeach()
add_executable(
    advent
    main.cxx
)
target_link_libraries(advent gflags::gflags)


add_executable(
    setup_day
    setup_day.cxx
)
target_link_libraries(setup_day gflags::gflags)
