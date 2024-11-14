#!/bin/bash
# Run info test cases
# Case 1: Expected use
./aos_ftest.sh ../../test-data/lake-small-100.ppm lake-small-output-info.ppm info

# Run maxlevel test cases
./aos-ftest.sh ../../test-data/lake-small-100.ppm lake-small-output-maxlevel.ppm maxlevel 10000

# Run resize test cases
# Case 1: resize 8byte RGB 1000x1000 to 8000x8000
./aos-ftest.sh ../../test-data/lake-small-1000.ppm lake-small-output-resize.ppm resize 8000 8000

# Run cutfreq case
./aos-ftest.sh ../../test-data/lake-small-1000.ppm lake-small-output-cutfreq.ppm cutfreq 15
