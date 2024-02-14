add_test([=[ExampleTest.First]=]  [==[/Users/lehatrutenb/Desktop/hse/C++/LongMathToCalcPI/PiCalculating_build/LongMath/MathTest]==] [==[--gtest_filter=ExampleTest.First]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExampleTest.First]=]  PROPERTIES WORKING_DIRECTORY [==[/Users/lehatrutenb/Desktop/hse/C++/LongMathToCalcPI/PiCalculating_build/LongMath]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  MathTest_TESTS ExampleTest.First)
