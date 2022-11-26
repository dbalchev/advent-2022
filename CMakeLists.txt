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
enable_testing()

include_directories($<TARGET_PROPERTY:gflags,INTERFACE_INCLUDE_DIRECTORIES>)

set(
    DAYS_TO_ADD
    day_0
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
