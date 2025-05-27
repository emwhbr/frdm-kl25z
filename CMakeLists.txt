cmake_minimum_required(VERSION 3.13)

# Specifying root cmake path for internal use.
set(ROOT_CMAKE "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "" FORCE)

# By target it means the entity the project should run on.
# Since the TARGET is predefined literal for the CMAKE build
# generator, we shall use TARGET_HW from now on internally.
set(TARGET_HW ${TARGET})
set(TARGET_HW_EXT "elf")

include(cmake/build_type.cmake)
include(cmake/colors.cmake)
include(cmake/targets.cmake)
include(cmake/toolchain.cmake)

verify_build_type()

if (NOT DEFINED TARGET_HW)
    set(TARGET_HW ${DEFAULT_TARGET})
    message(STATUS "${Yellow}Using default target: ${TARGET_HW}, specify -DTARGET= if necessary${ColorReset}")
else()
    message(STATUS "Target: ${Green}${TARGET_HW}${ColorReset}")
endif()

# List the languages the project based on, so the compiler doesn't get confused
project(frdm-kl25z LANGUAGES CXX C ASM)

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Libraries, packages and include file locations are within the project folder hierarchy
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# NXP SDK, predefined path
set(NXP_SDK "nxp_sdk" CACHE INTERNAL "")

# Target to be used for the project, predefined path
set(PROJECT_TARGET     "targets/${TARGET_HW}" CACHE INTERNAL "")
set(PROJECT_TARGET_EXT "${TARGET_HW_EXT}" CACHE INTERNAL "")

set(deps_list
    ${NXP_SDK}
    ${PROJECT_TARGET}
)

# Adds all dependency list to the build system queue
macro(add_deps)
foreach(Deps IN LISTS deps_list)
    add_subdirectory(${Deps})
endforeach()
endmacro()

add_deps()
