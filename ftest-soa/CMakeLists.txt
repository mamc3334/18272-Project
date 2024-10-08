# Executable for all functional tests with list of sources
# For example, you may have one ∗_test.cpp for each ∗.cpp in common
add_executable(ftest-soa
        one_test.cpp
#        other1_test.cpp
#        other2_test.cpp
        )
# Library dependencies
#target_link_libraries (ftest-soa
#        PRIVATE
#        common
#        GTest::gtest_main
#        Microsoft.GSL::GSL)