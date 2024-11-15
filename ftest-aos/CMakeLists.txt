# Executable for all unit tests with list of sources
# For example, you may have one ∗_test.cpp for each ∗.cpp in common
add_executable(ftest-aos
        resize_ftests.cpp
)
# Library dependencies
target_link_libraries (ftest-aos
        PRIVATE
        imgaos
        GTest::gtest_main
        GTest::gtest
)

target_include_directories(ftest-aos
        PRIVATE
        ${CMAKE_SOURCE_DIR}/ftest-aos
)

add_test(ResizeFuncTestAOS ftest-aos COMMAND ftest-aos)
