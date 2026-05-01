.PHONY: cmake-clean cmake-init cmake-build test check-with-tidy

DIRECTORY_BUILD = build/
BUILD_SYSTEM="Ninja"
BUILD_SYSTEM_COMMAND=ninja

cmake-clean:
	rm -rf ${DIRECTORY_BUILD}

cmake-init: cmake-clean
	cmake -S . -B ${DIRECTORY_BUILD} -G ${BUILD_SYSTEM}

cmake-build:
	cd ${DIRECTORY_BUILD} && ${BUILD_SYSTEM_COMMAND}

test: cmake-build
	cd ${DIRECTORY_BUILD} && ${BUILD_SYSTEM_COMMAND} run_tests

check-with-tidy: cmake-build
	git push --dry-run
