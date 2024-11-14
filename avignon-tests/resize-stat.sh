#!/bin/bash

perf stat build/imtool-aos/imtool-aos test-data/lake-small-100.ppm lake-small-resize-1000.ppm resize 1000 1000
perf stat build/imtool-aos/imtool-aos test-data/lake-small-1000.ppm lake-small-resize-100.ppm resize 100 100
perf stat build/imtool-aos/imtool-aos test-data/lake-small-1000.ppm lake-small-resize-1000.ppm resize 8000 8000