CreateBuildLib:
	mkdir PiCalculating_build
	cp Makefile PiCalculating/Makefile
	cd PiCalculating_build
	cmake ../PiCalculating

BuildCmakeRelease:
	cmake ../PiCalculating -DPRINT_TIME_INFO=OFF -DSetDebugBuildType=OFF
	cmake --build .

BuildRunCmakeDebug:
	cmake ../PiCalculating  -DPRINT_TIME_INFO=ON  -DSetDebugBuildType=ON
	cmake --build

	./PiCalculatingTest
	./LongMath/LongMathTest

BuildRunCmakeCoverage:
	lcov --directory ./build/ --capture --output-file ./code_coverage.info -rc lcov_branch_coverage=1

	cmake ../PiCalculating  -DPRINT_TIME_INFO=ON  -DSetDebugBuildType=ON -DEnableCoverage
	cmake --build .

	./PiCalculatingTest
	./LongMath/LongMathTest

	genhtml code_coverage.info --branch-coverage --output-directory ./code_coverage_report/
