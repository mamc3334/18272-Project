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
CMAKE_BINARY_DIR = /home/mamc3334/UC3M/18272-Project/cmake-build-release

# Include any dependencies generated for this target.
include imtool-aos/CMakeFiles/imtool-aos.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include imtool-aos/CMakeFiles/imtool-aos.dir/compiler_depend.make

# Include the progress variables for this target.
include imtool-aos/CMakeFiles/imtool-aos.dir/progress.make

# Include the compile flags for this target's objects.
include imtool-aos/CMakeFiles/imtool-aos.dir/flags.make

imtool-aos/CMakeFiles/imtool-aos.dir/main.cpp.o: imtool-aos/CMakeFiles/imtool-aos.dir/flags.make
imtool-aos/CMakeFiles/imtool-aos.dir/main.cpp.o: /home/mamc3334/UC3M/18272-Project/imtool-aos/main.cpp
imtool-aos/CMakeFiles/imtool-aos.dir/main.cpp.o: imtool-aos/CMakeFiles/imtool-aos.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object imtool-aos/CMakeFiles/imtool-aos.dir/main.cpp.o"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/imtool-aos && $(CMAKE_COMMAND) -E __run_co_compile --tidy="clang-tidy;-format-style=file;-header-filter=.;--extra-arg-before=--driver-mode=g++" --source=/home/mamc3334/UC3M/18272-Project/imtool-aos/main.cpp -- /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imtool-aos/CMakeFiles/imtool-aos.dir/main.cpp.o -MF CMakeFiles/imtool-aos.dir/main.cpp.o.d -o CMakeFiles/imtool-aos.dir/main.cpp.o -c /home/mamc3334/UC3M/18272-Project/imtool-aos/main.cpp

imtool-aos/CMakeFiles/imtool-aos.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imtool-aos.dir/main.cpp.i"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/imtool-aos && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mamc3334/UC3M/18272-Project/imtool-aos/main.cpp > CMakeFiles/imtool-aos.dir/main.cpp.i

imtool-aos/CMakeFiles/imtool-aos.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imtool-aos.dir/main.cpp.s"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/imtool-aos && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mamc3334/UC3M/18272-Project/imtool-aos/main.cpp -o CMakeFiles/imtool-aos.dir/main.cpp.s

# Object files for target imtool-aos
imtool__aos_OBJECTS = \
"CMakeFiles/imtool-aos.dir/main.cpp.o"

# External object files for target imtool-aos
imtool__aos_EXTERNAL_OBJECTS =

imtool-aos/imtool-aos: imtool-aos/CMakeFiles/imtool-aos.dir/main.cpp.o
imtool-aos/imtool-aos: imtool-aos/CMakeFiles/imtool-aos.dir/build.make
imtool-aos/imtool-aos: imgaos/libimgaos.a
imtool-aos/imtool-aos: common/libcommon.a
imtool-aos/imtool-aos: imtool-aos/CMakeFiles/imtool-aos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable imtool-aos"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/imtool-aos && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imtool-aos.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
imtool-aos/CMakeFiles/imtool-aos.dir/build: imtool-aos/imtool-aos
.PHONY : imtool-aos/CMakeFiles/imtool-aos.dir/build

imtool-aos/CMakeFiles/imtool-aos.dir/clean:
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/imtool-aos && $(CMAKE_COMMAND) -P CMakeFiles/imtool-aos.dir/cmake_clean.cmake
.PHONY : imtool-aos/CMakeFiles/imtool-aos.dir/clean

imtool-aos/CMakeFiles/imtool-aos.dir/depend:
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mamc3334/UC3M/18272-Project /home/mamc3334/UC3M/18272-Project/imtool-aos /home/mamc3334/UC3M/18272-Project/cmake-build-release /home/mamc3334/UC3M/18272-Project/cmake-build-release/imtool-aos /home/mamc3334/UC3M/18272-Project/cmake-build-release/imtool-aos/CMakeFiles/imtool-aos.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : imtool-aos/CMakeFiles/imtool-aos.dir/depend

