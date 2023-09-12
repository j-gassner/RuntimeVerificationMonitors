cmake_minimum_required(VERSION 3.16)
project(Monitors)

#SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wno-ignored-attributes)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/)

set(ANTLR4CPP_JAR_LOCATION ${CMAKE_SOURCE_DIR}/libs/antlr.jar)

set(EXECUTABLE_NAME "Monitors")

file(
        GLOB_RECURSE
        SRC_GEN
        "src/*.cpp"
        "src/*.h"
)

# create library of this project
add_library(${EXECUTABLE_NAME}_lib STATIC ${SRC_GEN})

target_include_directories(${EXECUTABLE_NAME}_lib
        PUBLIC
        src
        )

include(monitors_commonroad)
include(monitors_sanitizers)
# get antlr4 as external project
include(monitors_antlr4cpp)
# Doxygen
include(doxygen)



target_link_libraries(${EXECUTABLE_NAME}_lib
        antlr4cpp
        Boost::filesystem
        Boost::program_options
        OpenMP::OpenMP_CXX
        ${ENV_MODEL_LIBRARY}
        ${CRCCOSY_LIBRARY}
        )

# create executable by linking against the library
add_executable(${EXECUTABLE_NAME} src/main.cpp)
target_link_libraries(${EXECUTABLE_NAME} ${EXECUTABLE_NAME}_lib)

# add unit testing
enable_testing()
add_subdirectory(tests)
