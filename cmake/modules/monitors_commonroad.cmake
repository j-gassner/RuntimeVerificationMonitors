set(
        CRENV_LIBRARY_DIR
        ""
        CACHE
        STRING "Path to the CommonRoad Environment Model directory."
)

if (NOT IS_DIRECTORY "${CRENV_LIBRARY_DIR}")
    message(SEND_ERROR "Can't find the CommonRoad Environment Model in ${CRENV_LIBRARY_DIR}")
endif ()
set(ENV_MODEL_LIBRARY ${CRENV_LIBRARY_DIR}/libenv_model.a)
if (NOT EXISTS "${ENV_MODEL_LIBRARY}")
    message(SEND_ERROR "Library ${ENV_MODEL_LIBRARY} does not exist!")
endif ()

set(
        CRCCOSY_LIBRARY_DIR
        ""
        CACHE
        STRING "Path to the folder that should contain the CommonRoad-Curvilinear-Coordinate System library."
)
if (NOT IS_DIRECTORY "${CRCCOSY_LIBRARY_DIR}")
    message(SEND_ERROR "Can't find the CommonRoad-Curvilinear-Coordinate System library in ${CRCCOSY_LIBRARY_DIR}")
endif ()
set(CRCCOSY_LIBRARY ${CRCCOSY_LIBRARY_DIR}/libcrccosy.a)
if (NOT EXISTS "${CRCCOSY_LIBRARY}")
    message(SEND_ERROR "Library ${CRCCOSY_LIBRARY} does not exist!")
endif ()

# include CommonRoad environment model, boost eigen3, and openMP
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

find_package(Boost REQUIRED COMPONENTS filesystem program_options)

find_package(OpenMP REQUIRED)

#set_property(TARGET ${EXECUTABLE_NAME}_lib PROPERTY POSITION_INDEPENDENT_CODE ON)
set(CRENV_INCLUDES ${CRENV_LIBRARY_DIR})
if (NOT IS_DIRECTORY "${CRENV_INCLUDES}")
    message(SEND_ERROR "Include directory ${CRENV_LIBRARY_DIR} does not exist!")
endif ()
set(CRCCOSY_INCLUDES ${CRCCOSY_LIBRARY_DIR}/cpp)
if (NOT IS_DIRECTORY "${CRCCOSY_INCLUDES}")
    message(SEND_ERROR "Include directory ${CRCCOSY_LIBRARY_DIR}/cpp does not exist!")
endif ()

target_include_directories(${EXECUTABLE_NAME}_lib
        # Suppress warnings from third party sources
        SYSTEM
        PUBLIC
        ${CRENV_INCLUDES}
        ${CRCCOSY_INCLUDES}
        )

