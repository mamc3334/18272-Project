# Add to this list all files related to common library
add_library(common
        progargs.cpp
        progargs.hpp
        binaryio.cpp
        binaryio.hpp
        utility.cpp
        utility.hpp
        intensityscaling.cpp
        intensityscaling.hpp
)
# Use this line only if you have dependencies from this library to GSL
target_link_libraries (common PRIVATE Microsoft.GSL::GSL)

target_include_directories(common
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)