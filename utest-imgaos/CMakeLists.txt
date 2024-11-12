# Executable for all unit tests with list of sources
# For example, you may have one ∗_test.cpp for each ∗.cpp in img-aos
add_executable(utest-imgaos
        aoscompress_utest.cpp
        aosinfrequentcolor_utest.cpp
        aossize_utest.cpp
        imageaos_utest.cpp
)
# Library dependencies
target_link_libraries (utest-imgaos
        PRIVATE
        imgaos
        GTest::gtest_main
        GTest::gtest
)

target_include_directories(utest-imgaos
        PRIVATE
        ${CMAKE_SOURCE_DIR}/imgaos
)

add_test(AOSCompressTests utest-imgaos COMMAND utest-imgaos)