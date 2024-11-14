#!/bin/bash
# Run info test cases
# Case 1: Expected use for small file
./aos_ftest.sh ../../images/lake-small.ppm lake-small-output-info.ppm info
# Case 1: Expected use for large file
./aos_ftest.sh ../../images/lake-large.ppm lake-large-output-info.ppm info


# Run maxlevel test cases
# Case 1: Change max intensity for small file
./aos-ftest.sh ../../images/lake-small.ppm lake-small-output-maxlevel-10000.ppm maxlevel 10000
# Case 2: Change max intensity for large file
./aos-ftest.sh ../../images/lake-large.ppm lake-large-output-maxlevel-10000.ppm maxlevel 10000

# Run resize test cases
# Case 1: resize 8byte RGB 133x100 to 100x100
./aos-ftest.sh ../../images/lake-small.ppm lake-small-output-resize-100.ppm resize 100 100
# Case 2: resize 8byte RGB 4000x3000 to 1000x1000
./aos-ftest.sh ../../images/lake-small.ppm lake-small-output-resize-1000.ppm resize 1000 1000
# Case 1: resize 8byte RGB 133x100 to 8000x8000
./aos-ftest.sh ../../images/lake-small.ppm lake-small-output-resize-8000.ppm resize 8000 8000

# Run cutfreq case
# Case 1: Remove 15 infrequent colors for small file
./aos-ftest.sh ../../images/lake-small.ppm lake-small-output-cutfreq-15.ppm cutfreq 15