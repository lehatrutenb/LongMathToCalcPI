add_library(LongMath src/long_math.cpp)
option(EnableCoverage "Set on if want to collect coverage info" OFF)

if (EnableCoverage)
    SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
    SET(GCC_COVERAGE_LINK_FLAGS "-lgcov")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
endif()

add_executable(LongMathTest test/test.cpp)

target_link_libraries(LongMathTest GTest::gtest_main)

gtest_discover_tests(LongMathTest)