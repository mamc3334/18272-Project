# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/mamc3334/UC3M/18272-Project/cmake-build-debug/_deps/gsl-src"
  "/home/mamc3334/UC3M/18272-Project/cmake-build-debug/_deps/gsl-build"
  "/home/mamc3334/UC3M/18272-Project/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix"
  "/home/mamc3334/UC3M/18272-Project/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix/tmp"
  "/home/mamc3334/UC3M/18272-Project/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp"
  "/home/mamc3334/UC3M/18272-Project/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix/src"
  "/home/mamc3334/UC3M/18272-Project/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/mamc3334/UC3M/18272-Project/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/mamc3334/UC3M/18272-Project/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
