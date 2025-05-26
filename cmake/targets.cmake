# This file contains all the targets used in this repo

set(DEFAULT_TARGET "target_1" CACHE INTERNAL "" FORCE)

# The list of available targets
set(Targets
    "target_1"
    "target_2"

    CACHE INTERNAL "" FORCE
)

# Create a new list called available_targets
set(available_targets "")

# Iterate through the Targets list and add all targets to available_targets list
foreach(target IN LISTS Targets)
    if(NOT target STREQUAL "tests")
        list(APPEND available_targets ${target})
    endif()
endforeach()

add_custom_target(show_targets COMMAND echo ${available_targets})
