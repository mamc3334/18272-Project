# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mamc3334/UC3M/18272-Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mamc3334/UC3M/18272-Project/cmake-build-debug

# Include any dependencies generated for this target.
include ftest-aos/CMakeFiles/ftest-aos.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include ftest-aos/CMakeFiles/ftest-aos.dir/compiler_depend.make

# Include the progress variables for this target.
include ftest-aos/CMakeFiles/ftest-aos.dir/progress.make

# Include the compile flags for this target's objects.
include ftest-aos/CMakeFiles/ftest-aos.dir/flags.make

ftest-aos/CMakeFiles/ftest-aos.dir/one_test.cpp.o: ftest-aos/CMakeFiles/ftest-aos.dir/flags.make
ftest-aos/CMakeFiles/ftest-aos.dir/one_test.cpp.o: /home/mamc3334/UC3M/18272-Project/ftest-aos/one_test.cpp
ftest-aos/CMakeFiles/ftest-aos.dir/one_test.cpp.o: ftest-aos/CMakeFiles/ftest-aos.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ftest-aos/CMakeFiles/ftest-aos.dir/one_test.cpp.o"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-debug/ftest-aos && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-format-style=file;-header-filter=.;--extra-arg-before=--driver-mode=g++" --source=/home/mamc3334/UC3M/18272-Project/ftest-aos/one_test.cpp -- /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ftest-aos/CMakeFiles/ftest-aos.dir/one_test.cpp.o -MF CMakeFiles/ftest-aos.dir/one_test.cpp.o.d -o CMakeFiles/ftest-aos.dir/one_test.cpp.o -c /home/mamc3334/UC3M/18272-Project/ftest-aos/one_test.cpp

ftest-aos/CMakeFiles/ftest-aos.dir/one_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ftest-aos.dir/one_test.cpp.i"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-debug/ftest-aos && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mamc3334/UC3M/18272-Project/ftest-aos/one_test.cpp > CMakeFiles/ftest-aos.dir/one_test.cpp.i

ftest-aos/CMakeFiles/ftest-aos.dir/one_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ftest-aos.dir/one_test.cpp.s"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-debug/ftest-aos && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mamc3334/UC3M/18272-Project/ftest-aos/one_test.cpp -o CMakeFiles/ftest-aos.dir/one_test.cpp.s

# Object files for target ftest-aos
ftest__aos_OBJECTS = \
"CMakeFiles/ftest-aos.dir/one_test.cpp.o"

# External object files for target ftest-aos
ftest__aos_EXTERNAL_OBJECTS =

ftest-aos/ftest-aos: ftest-aos/CMakeFiles/ftest-aos.dir/one_test.cpp.o
ftest-aos/ftest-aos: ftest-aos/CMakeFiles/ftest-aos.dir/build.make
ftest-aos/ftest-aos: ftest-aos/CMakeFiles/ftest-aos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ftest-aos"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-debug/ftest-aos && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ftest-aos.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ftest-aos/CMakeFiles/ftest-aos.dir/build: ftest-aos/ftest-aos
.PHONY : ftest-aos/CMakeFiles/ftest-aos.dir/build

ftest-aos/CMakeFiles/ftest-aos.dir/clean:
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-debug/ftest-aos && $(CMAKE_COMMAND) -P CMakeFiles/ftest-aos.dir/cmake_clean.cmake
.PHONY : ftest-aos/CMakeFiles/ftest-aos.dir/clean

ftest-aos/CMakeFiles/ftest-aos.dir/depend:
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mamc3334/UC3M/18272-Project /home/mamc3334/UC3M/18272-Project/ftest-aos /home/mamc3334/UC3M/18272-Project/cmake-build-debug /home/mamc3334/UC3M/18272-Project/cmake-build-debug/ftest-aos /home/mamc3334/UC3M/18272-Project/cmake-build-debug/ftest-aos/CMakeFiles/ftest-aos.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : ftest-aos/CMakeFiles/ftest-aos.dir/depend

