In order to use this script:
1) Move into the ftest-soa directory. 
    
    cd ftest-soa
3) Run executable with parameters. Be conscious of file locations

Examples:
    
    ./soa-ftest.sh ../../test-data/lake-small-100.ppm lake-small-output-info.ppm info
    ./soa-ftest.sh ../../test-data/lake-small-100.ppm lake-small-output-maxlevel.ppm maxlevel 10000
    ./soa-ftest.sh ../../test-data/lake-small-1000.ppm lake-small-output-resize.ppm resize 8000 8000
    ./soa-ftest.sh ../../test-data/lake-small-1000.ppm lake-small-output-cutfreq.ppm cutfreq 15


This tests if there are errors and displays execution time.

Test passes if executable runs successfully and execution time is within reason. 