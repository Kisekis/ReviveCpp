# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_SOURCE_DIR = /home/cs144/revivecpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cs144/revivecpp/build

# Include any dependencies generated for this target.
include CMakeFiles/Revive.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Revive.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Revive.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Revive.dir/flags.make

CMakeFiles/Revive.dir/Revive.cpp.o: CMakeFiles/Revive.dir/flags.make
CMakeFiles/Revive.dir/Revive.cpp.o: ../Revive.cpp
CMakeFiles/Revive.dir/Revive.cpp.o: CMakeFiles/Revive.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs144/revivecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Revive.dir/Revive.cpp.o"
	/usr/bin/x86_64-linux-gnu-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Revive.dir/Revive.cpp.o -MF CMakeFiles/Revive.dir/Revive.cpp.o.d -o CMakeFiles/Revive.dir/Revive.cpp.o -c /home/cs144/revivecpp/Revive.cpp

CMakeFiles/Revive.dir/Revive.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Revive.dir/Revive.cpp.i"
	/usr/bin/x86_64-linux-gnu-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs144/revivecpp/Revive.cpp > CMakeFiles/Revive.dir/Revive.cpp.i

CMakeFiles/Revive.dir/Revive.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Revive.dir/Revive.cpp.s"
	/usr/bin/x86_64-linux-gnu-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs144/revivecpp/Revive.cpp -o CMakeFiles/Revive.dir/Revive.cpp.s

# Object files for target Revive
Revive_OBJECTS = \
"CMakeFiles/Revive.dir/Revive.cpp.o"

# External object files for target Revive
Revive_EXTERNAL_OBJECTS =

Revive: CMakeFiles/Revive.dir/Revive.cpp.o
Revive: CMakeFiles/Revive.dir/build.make
Revive: /usr/local/lib/libcryptoTools.a
Revive: /usr/local/lib/librelic_s.a
Revive: /usr/local/lib/libboost_system.a
Revive: /usr/local/lib/libboost_thread.a
Revive: /usr/local/lib/libboost_regex.a
Revive: CMakeFiles/Revive.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs144/revivecpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Revive"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Revive.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Revive.dir/build: Revive
.PHONY : CMakeFiles/Revive.dir/build

CMakeFiles/Revive.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Revive.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Revive.dir/clean

CMakeFiles/Revive.dir/depend:
	cd /home/cs144/revivecpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs144/revivecpp /home/cs144/revivecpp /home/cs144/revivecpp/build /home/cs144/revivecpp/build /home/cs144/revivecpp/build/CMakeFiles/Revive.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Revive.dir/depend

