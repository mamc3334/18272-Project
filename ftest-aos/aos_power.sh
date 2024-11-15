#!/bin/bash

EXECUTE="$(pwd)/build/imtool-aos/imtool-aos"

perf stat -e power/energy-pkg/ "$EXECUTE" "$@"
EXEC_STATUS=$?

if [ $EXEC_STATUS -ne 0 ]; then
    echo "Executable failed with exit status $EXEC_STATUS"
else
    echo "Executable ran successfully."
fi
