# Executable for all unit tests with list of sources
# For example, you may have one ∗_test.cpp for each ∗.cpp in imgsoa
add_executable(utest-imgsoa
        soacompress_utest.cpp
        soainfrequentcolor_utest.cpp
        soasize_utest.cpp
        imagesoa_utest.cpp
)
# Library dependencies
target_link_libraries (utest-imgsoa
        PRIVATE
        imgsoa
        GTest::gtest_main
        GTest::gtest
)

target_include_directories(utest-imgsoa
        PRIVATE
        ${CMAKE_SOURCE_DIR}/utest-imgsoa
)

add_test(soaSizeTests utest-imgsoa COMMAND utest-imgsoa)
add_test(soaCompressTests utest-imgsoa COMMAND utest-imgsoa)
add_test(soaCutFreqTests utest-imgsoa COMMAND utest-imgsoa)
add_test(ImagesoaTests utest-imgsoa COMMAND utest-imgsoa)
add_test(SoAInfrequentColorTest utest-imgsoa COMMAND utest-imgsoa)