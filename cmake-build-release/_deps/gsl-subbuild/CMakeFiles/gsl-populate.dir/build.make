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
CMAKE_SOURCE_DIR = /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild

# Utility rule file for gsl-populate.

# Include any custom commands dependencies for this target.
include CMakeFiles/gsl-populate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gsl-populate.dir/progress.make

CMakeFiles/gsl-populate: CMakeFiles/gsl-populate-complete

CMakeFiles/gsl-populate-complete: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-install
CMakeFiles/gsl-populate-complete: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-mkdir
CMakeFiles/gsl-populate-complete: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-download
CMakeFiles/gsl-populate-complete: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-update
CMakeFiles/gsl-populate-complete: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-patch
CMakeFiles/gsl-populate-complete: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-configure
CMakeFiles/gsl-populate-complete: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-build
CMakeFiles/gsl-populate-complete: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-install
CMakeFiles/gsl-populate-complete: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'gsl-populate'"
	/usr/local/bin/cmake -E make_directory /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/CMakeFiles
	/usr/local/bin/cmake -E touch /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/CMakeFiles/gsl-populate-complete
	/usr/local/bin/cmake -E touch /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-done

gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-update:
.PHONY : gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-update

gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-build: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'gsl-populate'"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-build && /usr/local/bin/cmake -E echo_append
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-build && /usr/local/bin/cmake -E touch /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-build

gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-configure: gsl-populate-prefix/tmp/gsl-populate-cfgcmd.txt
gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-configure: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'gsl-populate'"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-build && /usr/local/bin/cmake -E echo_append
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-build && /usr/local/bin/cmake -E touch /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-configure

gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-download: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-gitinfo.txt
gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-download: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'gsl-populate'"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps && /usr/local/bin/cmake -P /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/gsl-populate-prefix/tmp/gsl-populate-gitclone.cmake
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps && /usr/local/bin/cmake -E touch /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-download

gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-install: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'gsl-populate'"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-build && /usr/local/bin/cmake -E echo_append
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-build && /usr/local/bin/cmake -E touch /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-install

gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'gsl-populate'"
	/usr/local/bin/cmake -Dcfgdir= -P /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/gsl-populate-prefix/tmp/gsl-populate-mkdirs.cmake
	/usr/local/bin/cmake -E touch /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-mkdir

gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-patch: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-patch-info.txt
gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-patch: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'gsl-populate'"
	/usr/local/bin/cmake -E echo_append
	/usr/local/bin/cmake -E touch /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-patch

gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-update:
.PHONY : gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-update

gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-test: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'gsl-populate'"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-build && /usr/local/bin/cmake -E echo_append
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-build && /usr/local/bin/cmake -E touch /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-test

gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-update: gsl-populate-prefix/tmp/gsl-populate-gitupdate.cmake
gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-update: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-update-info.txt
gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-update: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Performing update step for 'gsl-populate'"
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-src && /usr/local/bin/cmake -Dcan_fetch=YES -P /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/gsl-populate-prefix/tmp/gsl-populate-gitupdate.cmake

gsl-populate: CMakeFiles/gsl-populate
gsl-populate: CMakeFiles/gsl-populate-complete
gsl-populate: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-build
gsl-populate: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-configure
gsl-populate: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-download
gsl-populate: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-install
gsl-populate: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-mkdir
gsl-populate: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-patch
gsl-populate: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-test
gsl-populate: gsl-populate-prefix/src/gsl-populate-stamp/gsl-populate-update
gsl-populate: CMakeFiles/gsl-populate.dir/build.make
.PHONY : gsl-populate

# Rule to build all files generated by this target.
CMakeFiles/gsl-populate.dir/build: gsl-populate
.PHONY : CMakeFiles/gsl-populate.dir/build

CMakeFiles/gsl-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gsl-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gsl-populate.dir/clean

CMakeFiles/gsl-populate.dir/depend:
	cd /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild /home/mamc3334/UC3M/18272-Project/cmake-build-release/_deps/gsl-subbuild/CMakeFiles/gsl-populate.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/gsl-populate.dir/depend
