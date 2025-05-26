# Printing build type status message
macro(verify_build_type)
if (NOT DEFINED CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Release" CACHE INTERNAL "" FORCE)
    # The default build type is yellow as a warning if not explicitly set
    message(STATUS "${Yellow}Build type: ${CMAKE_BUILD_TYPE}, use: -DCMAKE_BUILD_TYPE=Debug if necessary${ColorReset}")
# Screening wrong values.
elseif (CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE MATCHES "Release")
    # The build type is green if defined by user
    message(STATUS "Build type: ${Green}${CMAKE_BUILD_TYPE}${ColorReset}")
else()
    message(FATAL_ERROR "Build type: >>> ${CMAKE_BUILD_TYPE} <<<${Red} Only Release and Debug are legit. (Case sensitive)${ColorReset}")
endif()
endmacro()
