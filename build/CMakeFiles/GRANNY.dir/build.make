# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\projects\granny

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\projects\granny\build

# Include any dependencies generated for this target.
include CMakeFiles/GRANNY.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/GRANNY.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/GRANNY.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GRANNY.dir/flags.make

CMakeFiles/GRANNY.dir/main.cc.obj: CMakeFiles/GRANNY.dir/flags.make
CMakeFiles/GRANNY.dir/main.cc.obj: C:/projects/granny/main.cc
CMakeFiles/GRANNY.dir/main.cc.obj: CMakeFiles/GRANNY.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\projects\granny\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GRANNY.dir/main.cc.obj"
	C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GRANNY.dir/main.cc.obj -MF CMakeFiles\GRANNY.dir\main.cc.obj.d -o CMakeFiles\GRANNY.dir\main.cc.obj -c C:\projects\granny\main.cc

CMakeFiles/GRANNY.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GRANNY.dir/main.cc.i"
	C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\projects\granny\main.cc > CMakeFiles\GRANNY.dir\main.cc.i

CMakeFiles/GRANNY.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GRANNY.dir/main.cc.s"
	C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\projects\granny\main.cc -o CMakeFiles\GRANNY.dir\main.cc.s

# Object files for target GRANNY
GRANNY_OBJECTS = \
"CMakeFiles/GRANNY.dir/main.cc.obj"

# External object files for target GRANNY
GRANNY_EXTERNAL_OBJECTS =

GRANNY.exe: CMakeFiles/GRANNY.dir/main.cc.obj
GRANNY.exe: CMakeFiles/GRANNY.dir/build.make
GRANNY.exe: ./engine/libs/glfw3.lib
GRANNY.exe: CMakeFiles/GRANNY.dir/linkLibs.rsp
GRANNY.exe: CMakeFiles/GRANNY.dir/objects1.rsp
GRANNY.exe: CMakeFiles/GRANNY.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\projects\granny\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable GRANNY.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\GRANNY.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GRANNY.dir/build: GRANNY.exe
.PHONY : CMakeFiles/GRANNY.dir/build

CMakeFiles/GRANNY.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\GRANNY.dir\cmake_clean.cmake
.PHONY : CMakeFiles/GRANNY.dir/clean

CMakeFiles/GRANNY.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\projects\granny C:\projects\granny C:\projects\granny\build C:\projects\granny\build C:\projects\granny\build\CMakeFiles\GRANNY.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/GRANNY.dir/depend

