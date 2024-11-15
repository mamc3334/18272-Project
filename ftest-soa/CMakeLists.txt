# Executable for all unit tests with list of sources
# For example, you may have one ∗_test.cpp for each ∗.cpp in common
add_executable(ftest-soa
        resize_ftests.cpp
)
# Library dependencies
target_link_libraries (ftest-soa
        PRIVATE
        imgsoa
        GTest::gtest_main
        GTest::gtest
)

target_include_directories(ftest-soa
        PRIVATE
        ${CMAKE_SOURCE_DIR}/ftest-soa
)

add_test(ResizeFuncTestSOA ftest-soa COMMAND ftest-soa)
