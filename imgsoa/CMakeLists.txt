# Add to this list all files related to imgsoa library
add_library(imgsoa
        imagesoa.cpp
        imagesoa.hpp
        soasize.cpp
        soasize.hpp
        soainfrequentcolor.cpp
        soainfrequentcolor.hpp
        soacompress.cpp
        soacompress.hpp
        soacommon.cpp
        soacommon.hpp
        #        other1.cpp
#        other2.cpp
)
# Use this line only if you have dependencies from this library to GSL
#target_link_libraries (imgsoa PRIVATE common Microsoft.GSL::GSL)