# Add to this list all files related to common library
add_library(common
        progargs.cpp
        binaryio.cpp
        utility.cpp
        intensityscaling.cpp
        intensityscaling.h
)
# Use this line only if you have dependencies from this library to GSL
#target_link_libraries (common PRIVATE Microsoft.GSL::GSL)