# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mea/projstm32f090empty

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mea/projstm32f090empty

# Utility rule file for gdbserver.

# Include any custom commands dependencies for this target.
include CMakeFiles/gdbserver.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gdbserver.dir/progress.make

CMakeFiles/gdbserver:
	openocd -s /usr/share/openocd/scripts -f interface/stlink.cfg -f target/stm32f0x.cfg -c adapter\ speed\ 2000

gdbserver: CMakeFiles/gdbserver
gdbserver: CMakeFiles/gdbserver.dir/build.make
.PHONY : gdbserver

# Rule to build all files generated by this target.
CMakeFiles/gdbserver.dir/build: gdbserver
.PHONY : CMakeFiles/gdbserver.dir/build

CMakeFiles/gdbserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gdbserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gdbserver.dir/clean

CMakeFiles/gdbserver.dir/depend:
	cd /home/mea/projstm32f090empty && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mea/projstm32f090empty /home/mea/projstm32f090empty /home/mea/projstm32f090empty /home/mea/projstm32f090empty /home/mea/projstm32f090empty/CMakeFiles/gdbserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gdbserver.dir/depend

