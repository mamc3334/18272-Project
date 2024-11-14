In order to use this script:
1) Move into the ftest-aos directory.

   cd ftest-aos
3) Run executable with parameters. Be conscious of file locations

Examples:

    ./aos-ftest.sh ../../test-data/lake-small-100.ppm lake-small-output-info.ppm info
    ./aos-ftest.sh ../../test-data/lake-small-100.ppm lake-small-output-maxlevel.ppm maxlevel 10000
    ./aos-ftest.sh ../../test-data/lake-small-1000.ppm lake-small-output-resize.ppm resize 8000 8000
    ./aos-ftest.sh ../../test-data/lake-small-1000.ppm lake-small-output-cutfreq.ppm cutfreq 15


This test ensures no errors and displays execution time.

Test passes if executable runs successfully and execution time is within reason. 