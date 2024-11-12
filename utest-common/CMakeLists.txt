# Executable for all unit tests with list of sources
# For example, you may have one ∗_test.cpp for each ∗.cpp in common
add_executable(utest-common
        one_test.cpp
        utest-helpers.cpp
        utest-helpers.hpp
        #intensityscaling_utest.cpp
        #utility-utest.cpp
        #progargs_utest.cpp
        #        other1_test.cpp
#        other2_test.cpp
        )
# Library dependencies
target_link_libraries (utest-common
        PRIVATE
        common
        GTest::gtest_main
        GTest::gtest
)

target_include_directories(utest-common
        PRIVATE
        ${CMAKE_SOURCE_DIR}/common
)

add_test(IntensityScalingTests utest-common COMMAND utest-common)