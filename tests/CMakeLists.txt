# make test optional. Useful also when no network connection is available
option(
        MONITORS_BUILD_TESTS
        "Build tests based on the Google Test Framework" ON
)

# do nothing if nothing should be done
if (NOT MONITORS_BUILD_TESTS)
    return()
endif ()

# includes the gtest modules
include(monitors_googletest)

# add AutoPas tests:
add_subdirectory(testMonitors)
