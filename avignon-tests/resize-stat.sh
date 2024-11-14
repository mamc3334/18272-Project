#!/bin/bash

perf stat build/imtool-aos/imtool-aos images/lake-small.ppm lake-small-resize-1000.ppm resize 1000 1000
perf stat build/imtool-aos/imtool-aos images/lake-small.ppm lake-small-resize-100.ppm resize 100 100
perf stat build/imtool-aos/imtool-aos images/lake-small.ppm lake-small-resize-8000.ppm resize 8000 8000