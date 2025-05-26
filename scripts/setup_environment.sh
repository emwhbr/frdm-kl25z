#!/bin/sh

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
export REPO_DIR=${SCRIPT_DIR}/..

# ARM GNU Toolchain
ARM=/opt2/arm/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi

# OpenOCD
OPENOCD=/opt2/openocd

# Update PATH
export PATH=${ARM}/bin:${OPENOCD}/bin:${PATH}
