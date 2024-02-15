cmake_minimum_required (VERSION 3.8)
project (PiCalculating)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_BUILD_TYPE Release)

add_compile_options(-O2)

include(cmake/Core.cmake)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_subdirectory(LongMath)

file(COPY ${PROJECT_SOURCE_DIR}/test/pi.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(PiCalculatingTest test/test.cpp)

option(PRINT_TIME_INFO "Print every iteration duration in testing of cacling pi if ON" OFF)
configure_file(${PROJECT_SOURCE_DIR}/include/calc_pi.h.in ${PROJECT_SOURCE_DIR}/include/calc_pi.h)
target_include_directories(PiCalculatingTest PUBLIC ${PROJECT_BINARY_DIR}/include)

target_link_libraries(PiCalculatingTest GTest::gtest_main)

gtest_discover_tests(PiCalculatingTest)
