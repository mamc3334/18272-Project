#include "../common/binaryio.hpp"
#include "../common/utility.hpp"

#include <gtest/gtest.h>
using namespace std;

//We assume cmake has been built and is within 18272-Project/cmake-build-debug
//We assume that these tests are being executed by cmake application configuration in 18272-Project/cmake-build-debug/ftest-soa
int resize(string one, string two){
  ifstream expected(one);
  ifstream actual(two);

  if(!(actual.is_open()&&expected.is_open())){
    cout << "Error opening files" << endl;
    return -1;
  }
  Image_Attributes actualData = get_image_metadata(actual);
  Image_Attributes expectedData = get_image_metadata(expected);

  int count = 0;
  for(int i = 0; i < 100*100; i++) {
    int act = read_binary8(actual);
    int exp = read_binary8(expected);
    int low = exp-6;
    // ReSharper disable once CppTooWideScopeInitStatement
    int high = exp+6;
    if(act < low || act > high){
      count++;
    }
  }
  actual.close();
  expected.close();
  return count;
}

TEST(ResizeFuncTestSOA, LakeSmall100){
  // ReSharper disable once CppDFAUnusedValue
  // NOLINTNEXTLINE(*-env33-c)
  const int exec_status = system("../imtool-soa/imtool-soa ../../images/lake-small.ppm lake-small-resize-100.ppm resize 100 100");

  if (exec_status != 0) {
    cout << "Executable did not run as expected." << endl;
    FAIL();
  }

  int pass = resize("lake-small-resize-100.ppm", "../../expected-output/resize/lake-small-100.ppm");
  ASSERT_EQ(pass, 0);
}

TEST(ResizeFuncTestSOA, LakeSmall1000){
  // ReSharper disable once CppDFAUnusedValue
  // NOLINTNEXTLINE(*-env33-c)
  const int exec_status = system("../imtool-soa/imtool-soa ../../images/lake-small.ppm lake-small-resize-1000.ppm resize 1000 1000");

  if (exec_status != 0) {
    cout << "Executable did not run as expected." << endl;
    FAIL();
  }

  int pass = resize("lake-small-resize-1000.ppm", "../../expected-output/resize/lake-small-1000.ppm");
  ASSERT_EQ(pass, 0);
}

TEST(ResizeFuncTestSOA, LakeLarge100){
  // ReSharper disable once CppDFAUnusedValue
  // NOLINTNEXTLINE(*-env33-c)
  const int exec_status = system("../imtool-soa/imtool-soa ../../images/lake-large.ppm lake-large-resize-100.ppm resize 100 100");

  if (exec_status != 0) {
    cout << "Executable did not run as expected." << endl;
    FAIL();
  }

  int pass = resize("lake-large-resize-100.ppm", "../../expected-output/resize/lake-large-100.ppm");
  ASSERT_EQ(pass, 0);
}

TEST(ResizeFuncTestSOA, LakeLarge1000){
  // ReSharper disable once CppDFAUnusedValue
  // NOLINTNEXTLINE(*-env33-c)
  const int exec_status = system("../imtool-soa/imtool-soa ../../images/lake-large.ppm lake-large-resize-1000.ppm resize 1000 1000");

  if (exec_status != 0) {
    cout << "Executable did not run as expected." << endl;
    FAIL();
  }

  int pass = resize("lake-large-resize-1000.ppm", "../../expected-output/resize/lake-large-1000.ppm");
  ASSERT_EQ(pass, 0);
}

TEST(ResizeFuncTestSOA, DeerSmall100){
  // ReSharper disable once CppDFAUnusedValue
  // NOLINTNEXTLINE(*-env33-c)
  const int exec_status = system("../imtool-soa/imtool-soa ../../images/deer-small.ppm deer-small-resize-100.ppm resize 100 100");

  if (exec_status != 0) {
    cout << "Executable did not run as expected." << endl;
    FAIL();
  }

  int pass = resize("deer-small-resize-100.ppm", "../../expected-output/resize/deer-small-100.ppm");
  ASSERT_EQ(pass, 0);
}

TEST(ResizeFuncTestSOA, DeerSmall1000){
  // ReSharper disable once CppDFAUnusedValue
  // NOLINTNEXTLINE(*-env33-c)
  const int exec_status = system("../imtool-soa/imtool-soa ../../images/deer-small.ppm deer-small-resize-1000.ppm resize 1000 1000");

  if (exec_status != 0) {
    cout << "Executable did not run as expected." << endl;
    FAIL();
  }

  int pass = resize("deer-small-resize-1000.ppm", "../../expected-output/resize/deer-small-1000.ppm");
  ASSERT_EQ(pass, 0);
}

TEST(ResizeFuncTestSOA, DeerLarge100){
  // ReSharper disable once CppDFAUnusedValue
  // NOLINTNEXTLINE(*-env33-c)
  const int exec_status = system("../imtool-soa/imtool-soa ../../images/deer-large.ppm deer-large-resize-100.ppm resize 100 100");

  if (exec_status != 0) {
    cout << "Executable did not run as expected." << endl;
    FAIL();
  }

  int pass = resize("deer-large-resize-100.ppm", "../../expected-output/resize/deer-large-100.ppm");
  ASSERT_EQ(pass, 0);
}

TEST(ResizeFuncTestSOA, DeerLarge1000){
  // ReSharper disable once CppDFAUnusedValue
  // NOLINTNEXTLINE(*-env33-c)
  const int exec_status = system("../imtool-soa/imtool-soa ../../images/deer-large.ppm deer-large-resize-1000.ppm resize 1000 1000");

  if (exec_status != 0) {
    cout << "Executable did not run as expected." << endl;
    FAIL();
  }

  int pass = resize("deer-large-resize-1000.ppm", "../../expected-output/resize/deer-large-1000.ppm");
  ASSERT_EQ(pass, 0);
}
