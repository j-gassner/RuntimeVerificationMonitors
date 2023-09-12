message(STATUS "gtest - using bundled version")
find_package(Threads REQUIRED)

# Enable FetchContent CMake module
include(FetchContent)

# Build GoogleTest and make the cmake targets available
FetchContent_Declare(
        gtest
        URL ${PROJECT_SOURCE_DIR}/libs/googletest/googletest-master.zip
        URL_HASH MD5=3df855f5e150dc1cb5d68d15f2ad462b
)

option(INSTALL_GTEST "" OFF)

# hide options from ccmake
mark_as_advanced(BUILD_GMOCK INSTALL_GTEST)

FetchContent_GetProperties(gtest)
if (NOT gtest_POPULATED)
    FetchContent_Populate(gtest)
    add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()