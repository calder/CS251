#!/bin/bash

# Change to the root directory
dir=`dirname ${0}`
current=$(pwd)
cd "${dir}/.."

# Count lines
cat */*.c */*.h */*/*.c */*/*.h | wc -l

# Change back to original directory
cd "${current}"