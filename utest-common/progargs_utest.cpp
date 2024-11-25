//
// Created by eloim on 10/11/2024.
//

#include "utility.hpp"
#include "../common/progargs.hpp"

#include <gtest/gtest.h>

TEST(ProgArgsTest, ProgInfoTest_Valid) {
  EXPECT_NO_THROW(prog_info(InfoArgs));
}

TEST(ProgArgsTest, ProgInfoTest_Invalid) {
  EXPECT_EXIT(prog_info(10), ::testing::ExitedWithCode(1), "Error:\tInvalid extra arguments for info:\t-6\n");
}

TEST(ProgArgsTest, ProgMaxLevel_Valid) {
  EXPECT_NO_THROW(prog_maxlevel(MaxLevelArgs, {"file1", "file2", "maxlevel", "255"}));
}

TEST(ProgArgsTest, ProgMaxLevel_InvalidArgc) {
  EXPECT_EXIT(prog_maxlevel(10, {"irrelevant"}), ::testing::ExitedWithCode(1), "Error:\tInvalid extra arguments for maxlevel:\t-5\n");
}

TEST(ProgArgsTest, ProgMaxLevel_InvalidMaxIntensity) {
  EXPECT_EXIT(prog_maxlevel(MaxLevelArgs, {"file1", "file2", "maxlevel", "65536"}), ::testing::ExitedWithCode(1), "Error:\tInvalid maxlevel: 65536\n");
}

TEST(ProgArgsTest, ProgResize_Valid) {
  EXPECT_NO_THROW(prog_resize(ResizeArgs, {"file1", "file2", "resize", "100", "100"}));
}

TEST(ProgArgsTest, ProgResize_InvalidArgc) {
  EXPECT_EXIT(prog_resize(ResizeArgs+1, {"file1", "file2", "resize", "100", "100"}), ::testing::ExitedWithCode(1), "Error:\tInvalid extra arguments for resize:\t-1\n");
}

TEST(ProgArgsTest, ProgResize_InvalidWidth) {
  EXPECT_EXIT(prog_resize(ResizeArgs, {"file1", "file2", "resize", "-1", "100"}), ::testing::ExitedWithCode(1), "Error:\tInvalid resize width: -1\n");
}

TEST(ProgArgsTest, ProgResize_InvalidHeight) {
  EXPECT_EXIT(prog_resize(ResizeArgs, {"file1", "file2", "resize", "100", "-1"}), ::testing::ExitedWithCode(1), "Error:\tInvalid resize height: -1\n");
}

TEST(ProgArgsTest, ProgCutFreq) {
  EXPECT_NO_THROW(prog_cutfreq(CutFreqArgs, {"file1", "file2", "cutfreq", "100"}));
}

TEST(ProgArgsTest, ProgCutFreq_InvalidArgc) {
  EXPECT_EXIT(prog_cutfreq(CutFreqArgs+1, {"file1", "file2", "cutfreq", "100"}), ::testing::ExitedWithCode(1), "Error:\tInvalid extra arguments for cutfreq:\t-1\n");
}

TEST(ProgArgsTest, ProgCutFreq_InvalidNum) {
  EXPECT_EXIT(prog_cutfreq(CutFreqArgs, {"file1", "file2", "cutfreq", "-1"}), ::testing::ExitedWithCode(1), "Error:\tInvalid cutfreq:\t-1\n");
}

TEST(ProgArgsTest, ProgCompress_Valid) {
  EXPECT_NO_THROW(prog_compress(CompressArgs));
}

TEST(ProgArgsTest, ProgCompress_InvalidArgc) {
  EXPECT_EXIT(prog_compress(CompressArgs+1), ::testing::ExitedWithCode(1), "Error:\tInvalid extra arguments for compress:\t-1\n");
}