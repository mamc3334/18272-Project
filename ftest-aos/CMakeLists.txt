# Library dependencies
add_executable(ftest-aos
        aossize_ftest.sh
)
target_link_libraries (ftest-aos
        PRIVATE
        imgaos
        GTest::gtest_main
        GTest::gtest
)

add_dependencies(ftest-aos imtool-aos)
set(MAIN_EXECUTABLE_PATH $<TARGET_FILE:${CMAKE_CURRENT_SOURCE_DIR}/imtool-aos>)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.sh ${CMAKE_CURRENT_BINARY_DIR}/config.sh @ONLY)
