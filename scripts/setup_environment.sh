#!/bin/sh

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
export REPO_DIR=${SCRIPT_DIR}/..

# ARM GNU Toolchain
ARM=/opt2/arm/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi

# JLink executables needs to be executed with full path.
# Adding directory to PATH doesn't work :(
export JLINK_FLASHER=/opt/SEGGER/JLink_Linux_V816_x86_64/JFlashExe

# Update PATH
export PATH=${ARM}/bin:${PATH}
