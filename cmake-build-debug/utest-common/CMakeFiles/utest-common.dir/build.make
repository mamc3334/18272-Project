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
include utest-common/CMakeFiles/utest-common.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include utest-common/CMakeFiles/utest-common.dir/compiler_depend.make

# Include the progress variables for this target.
include utest-common/CMakeFiles/utest-common.dir/progress.make

# Include the compile flags for this target's objects.
include utest-common/CMakeFiles/utest-common.dir/flags.make

utest-common/CMakeFiles/utest-common.dir/one_test.cpp.o: utest-common/CMakeFiles/utest-common.dir/flags.make
utest-common/CMakeFiles/utest-common.dir/one_test.cpp.o: /home/mamc3334/UC3M/18272-Project/utest-common/one_test.cpp
utest-common/CMakeFiles/utest-common.dir/one_test.cpp.o: utest-common/CMakeFiles/utest-common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object utest-common/CMakeFiles/utest-common.dir/one_test.cpp.o"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-debug/utest-common && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-format-style=file;-header-filter=.;--extra-arg-before=--driver-mode=g++" --source=/home/mamc3334/UC3M/18272-Project/utest-common/one_test.cpp -- /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT utest-common/CMakeFiles/utest-common.dir/one_test.cpp.o -MF CMakeFiles/utest-common.dir/one_test.cpp.o.d -o CMakeFiles/utest-common.dir/one_test.cpp.o -c /home/mamc3334/UC3M/18272-Project/utest-common/one_test.cpp

utest-common/CMakeFiles/utest-common.dir/one_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/utest-common.dir/one_test.cpp.i"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-debug/utest-common && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mamc3334/UC3M/18272-Project/utest-common/one_test.cpp > CMakeFiles/utest-common.dir/one_test.cpp.i

utest-common/CMakeFiles/utest-common.dir/one_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/utest-common.dir/one_test.cpp.s"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-debug/utest-common && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mamc3334/UC3M/18272-Project/utest-common/one_test.cpp -o CMakeFiles/utest-common.dir/one_test.cpp.s

# Object files for target utest-common
utest__common_OBJECTS = \
"CMakeFiles/utest-common.dir/one_test.cpp.o"

# External object files for target utest-common
utest__common_EXTERNAL_OBJECTS =

utest-common/utest-common: utest-common/CMakeFiles/utest-common.dir/one_test.cpp.o
utest-common/utest-common: utest-common/CMakeFiles/utest-common.dir/build.make
utest-common/utest-common: utest-common/CMakeFiles/utest-common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable utest-common"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-debug/utest-common && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utest-common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utest-common/CMakeFiles/utest-common.dir/build: utest-common/utest-common
.PHONY : utest-common/CMakeFiles/utest-common.dir/build

utest-common/CMakeFiles/utest-common.dir/clean:
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-debug/utest-common && $(CMAKE_COMMAND) -P CMakeFiles/utest-common.dir/cmake_clean.cmake
.PHONY : utest-common/CMakeFiles/utest-common.dir/clean

utest-common/CMakeFiles/utest-common.dir/depend:
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mamc3334/UC3M/18272-Project /home/mamc3334/UC3M/18272-Project/utest-common /home/mamc3334/UC3M/18272-Project/cmake-build-debug /home/mamc3334/UC3M/18272-Project/cmake-build-debug/utest-common /home/mamc3334/UC3M/18272-Project/cmake-build-debug/utest-common/CMakeFiles/utest-common.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : utest-common/CMakeFiles/utest-common.dir/depend

