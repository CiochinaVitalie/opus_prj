# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/vitalii/opus_prj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vitalii/opus_prj/build

# Include any dependencies generated for this target.
include CMakeFiles/target.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/target.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/target.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/target.dir/flags.make

CMakeFiles/target.dir/main.c.o: CMakeFiles/target.dir/flags.make
CMakeFiles/target.dir/main.c.o: ../main.c
CMakeFiles/target.dir/main.c.o: CMakeFiles/target.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vitalii/opus_prj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/target.dir/main.c.o"
	/usr/bin/gcc-12 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/target.dir/main.c.o -MF CMakeFiles/target.dir/main.c.o.d -o CMakeFiles/target.dir/main.c.o -c /home/vitalii/opus_prj/main.c

CMakeFiles/target.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/target.dir/main.c.i"
	/usr/bin/gcc-12 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vitalii/opus_prj/main.c > CMakeFiles/target.dir/main.c.i

CMakeFiles/target.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/target.dir/main.c.s"
	/usr/bin/gcc-12 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vitalii/opus_prj/main.c -o CMakeFiles/target.dir/main.c.s

# Object files for target target
target_OBJECTS = \
"CMakeFiles/target.dir/main.c.o"

# External object files for target target
target_EXTERNAL_OBJECTS =

target: CMakeFiles/target.dir/main.c.o
target: CMakeFiles/target.dir/build.make
target: CMakeFiles/target.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vitalii/opus_prj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable target"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/target.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/target.dir/build: target
.PHONY : CMakeFiles/target.dir/build

CMakeFiles/target.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/target.dir/cmake_clean.cmake
.PHONY : CMakeFiles/target.dir/clean

CMakeFiles/target.dir/depend:
	cd /home/vitalii/opus_prj/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vitalii/opus_prj /home/vitalii/opus_prj /home/vitalii/opus_prj/build /home/vitalii/opus_prj/build /home/vitalii/opus_prj/build/CMakeFiles/target.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/target.dir/depend

