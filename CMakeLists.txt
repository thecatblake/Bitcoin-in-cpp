cmake_minimum_required(VERSION 3.26)
project(Bitcoin_in_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(Bitcoin
        BigInt.cpp
        FiniteElement.cpp
        FiniteElement.h
)

add_executable(main main.cpp)
target_link_libraries(main Bitcoin)
add_executable(finite_element_set_explorer finite_element_set_explorer.cpp)
target_link_libraries(finite_element_set_explorer Bitcoin)

add_executable(test test/test.cpp
        test/test_FiniteElement.h)
target_link_libraries(test Bitcoin GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test)
