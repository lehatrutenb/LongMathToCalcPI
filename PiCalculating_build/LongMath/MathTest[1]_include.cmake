if(EXISTS "/Users/lehatrutenb/Desktop/hse/C++/LongMathToCalcPI/PiCalculating_build/LongMath/MathTest[1]_tests.cmake")
  include("/Users/lehatrutenb/Desktop/hse/C++/LongMathToCalcPI/PiCalculating_build/LongMath/MathTest[1]_tests.cmake")
else()
  add_test(MathTest_NOT_BUILT MathTest_NOT_BUILT)
endif()