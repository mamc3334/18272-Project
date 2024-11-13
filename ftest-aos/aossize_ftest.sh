#!/bin/bash

# Load the main executable path and parameters from config.sh
source "$(dirname "$0")/config.sh"
## Build the project (optional)
#cmake --build ../build

# Run executable with resize params
if [ -x "$MAIN_EXECUTABLE_PATH" ]; then
  -x "$MAIN_EXECUTABLE_PATH$ ../test-data/lake-small-100.ppm lake-small-1000-output.ppm 1000 1000";
  # TODO: evaluate outputs

else
  echo "Main executable not found or executable"
  exit 1
fi