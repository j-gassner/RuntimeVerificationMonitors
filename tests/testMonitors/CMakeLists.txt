file(
        GLOB_RECURSE
        MY_SRC
        "*.cpp"
        "*.h"
)


add_executable(runTests ${MY_SRC})

target_compile_definitions(runTests PRIVATE)

target_include_directories(
        runTests
        PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        )

target_link_libraries(
        runTests
        PUBLIC
        ${EXECUTABLE_NAME}_lib
        gmock # gmock includes the gtest target, so we don't need it here.
)

include(GoogleTest)
# queries the compiled executable for tests, this requires the executable to be runnable. if you are
# cross compiling, make sure to properly set CMAKE_CROSSCOMPILING_EMULATOR.
gtest_discover_tests(
        runTests TEST_PREFIX "testMonitors/"
        # increase the discovery timeout for `runTests --gtest_list_tests`
        DISCOVERY_TIMEOUT 60
)
