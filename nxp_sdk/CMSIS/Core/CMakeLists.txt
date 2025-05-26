# The library (PROJECT_NAME = CMSIS-Core)
project(CMSIS-Core LANGUAGES C)

# Adding path for the library include directory
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include)

# We want a header-only library
add_library(${PROJECT_NAME} INTERFACE)

# Expose the include folder for the library
target_include_directories(${PROJECT_NAME}
    INTERFACE
    ${PROJECT_INCLUDE_DIR}
)
