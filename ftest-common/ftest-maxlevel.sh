#!/bin/bash

inputDir="images"
expectedOutputDir="expectedOutputs"
actualOutputDir="actualOut"


mkdir -p "$actualOutputDir"

run_test() {
  local inputFile="$1"
  local outputFile="$2"
  local expectedFile="$3"
  local maxlevelVal="$4"

  imtool-release/imtool-aos/imtool-aos "$inputFile" "$outputFile" maxlevel "$maxlevelVal"

  cmp -s "$outputFile" "$expectedFile"
  local ret_cmp=$?

  if [ $ret_cmp == 0 ]; then
    echo "Test passed"
  else
    echo "Test failed"
  fi
}

#Example
run_test "$inputDir/deer_small.ppm" "$actualOutputDir/deer-small-255" "$expectedOutputDir/deer-small-255" "255"

run_test "$inputDir/deer_small.ppm" "$actualOutputDir/deer-small-65535" "$expectedOutputDir/deer-small-65535" "65535"

run_test "$inputDir/lake_small.ppm" "$actualOutputDir/lake-small-255" "$expectedOutputDir/lake-small-255" "255"

run_test "$inputDir/lake_small.ppm" "$actualOutputDir/lake-small-65535" "$expectedOutputDir/lake-small-65535" "65535"

run_test "$inputDir/deer_small.ppm" "$actualOutputDir/deer-small-100" "$expectedOutputDir/deer-small-100" "100"

run_test "$inputDir/deer_small.ppm" "$actualOutputDir/deer-small-1000" "$expectedOutputDir/deer-small-1000" "1000"



rm -rf "$actualOutputDir"