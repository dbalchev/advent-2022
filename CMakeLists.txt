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
find_package(gflags)

include_directories($<TARGET_PROPERTY:gflags,INTERFACE_INCLUDE_DIRECTORIES>)

add_executable(
    advent
    main.cxx
)
target_link_libraries(advent gflags::gflags)
