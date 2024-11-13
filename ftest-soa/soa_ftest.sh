#!/bin/bash

# Define paths
BUILD_DIR="../cmake-build-debug/imtool-soa"      # Replace with the path to your CMake build directory
SOURCE_DIR="../"    # Replace with the path to your CMake project source directory
EXECUTABLE="./imtool-soa"            # Name of the executable after building
# Step 1: Create and navigate to the build directory
mkdir -p "$BUILD_DIR"  # Create build directory if it doesn't exist
cd "$BUILD_DIR" || { echo "Failed to cd into $BUILD_DIR"; exit 1; }

# Step 2: Run CMake and build the project
cmake "$SOURCE_DIR" || { echo "CMake configuration failed"; exit 1; }
cmake --build . || { echo "Build failed"; exit 1; }

pwd

# Step 4: Run the executable
if [ -x "$EXECUTABLE" ]; then
    #Start time
    START_TIME=$(date +%s.%3N)
    "$EXECUTABLE" "$@"
    EXEC_STATUS=$?
    END_TIME=$(date +%s.%3N)
    if [ $EXEC_STATUS -ne 0 ]; then
        echo "Executable failed with exit status $EXEC_STATUS"
    else
        echo "Executable ran successfully."
    fi
    #Display Execution time
    EXEC_TIME=$(echo "$END_TIME $START_TIME" | awk '{print $1 - $2}')
    echo "Execution time: ${EXEC_TIME} seconds"
else
    echo "Executable $EXECUTABLE not found or is not executable"
    exit 1
fi
