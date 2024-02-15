.ONESHELL: # make all commands executable in one shell
.SHELLFLAGS += -e

CreateBuildLib:
	mkdir PiCalculating_build
	cd PiCalculating_build
	cmake ../PiCalculating

BuildCmakeRelease:
	cd PiCalculating_build
	# can't use cd in another target - not one shell

	cmake ../PiCalculating -DPRINT_TIME_INFO=OFF -DSetDebugBuildType=OFF -DEnableCoverage=OFF
	cmake --build .

BuildRunCmakeDebug:
	cd PiCalculating_build
	cmake ../PiCalculating  -DPRINT_TIME_INFO=ON  -DSetDebugBuildType=ON -DEnableCoverage=OFF
	cmake --build .

	./PiCalculatingTest
	./LongMath/LongMathTest

BuildRunCmakeCoverage:
	cd PiCalculating_build
	lcov --directory . --capture --output-file ./code_coverage.info -rc lcov_branch_coverage=1

	cmake ../PiCalculating  -DPRINT_TIME_INFO=ON  -DSetDebugBuildType=ON -DEnableCoverage=ON
	cmake --build .

	./PiCalculatingTest
	./LongMath/LongMathTest

	genhtml code_coverage.info --branch-coverage --output-directory ./code_coverage_report/
