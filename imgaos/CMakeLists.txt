# Add to this list all files related to imgaos library
add_library(imgaos
        imageaos.cpp
        imageaos.hpp
        aossize.cpp
        aossize.hpp
        aosinfrequentcolor.cpp
        aosinfrequentcolor.hpp
        aoscompress.cpp
        aoscompress.hpp
)
# Use this line only if you have dependencies from this library to GSL
#target_link_libraries (imgaos PRIVATE common Microsoft.GSL::GSL)