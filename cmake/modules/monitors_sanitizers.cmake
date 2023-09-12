option(ENABLE_ADDRESS_SANITIZER "Enable clang or gcc address sanitizer" OFF)
#Check for memory leaks
if (ENABLE_ADDRESS_SANITIZER)
    target_compile_options(${EXECUTABLE_NAME}_lib
            PUBLIC
            -fno-omit-frame-pointer
            -fsanitize=address
            )
    target_link_options(${EXECUTABLE_NAME}_lib
            PUBLIC
            -fno-omit-frame-pointer
            -fsanitize=address
            )
    message(STATUS "Address sanitizer enabled")
endif ()