# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_SOURCE_DIR = /home/omer/BIU/pFlight

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/omer/BIU/pFlight/build

# Include any dependencies generated for this target.
include CMakeFiles/ex2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ex2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex2.dir/flags.make

CMakeFiles/ex2.dir/MainTrain.cpp.o: CMakeFiles/ex2.dir/flags.make
CMakeFiles/ex2.dir/MainTrain.cpp.o: ../MainTrain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omer/BIU/pFlight/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex2.dir/MainTrain.cpp.o"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex2.dir/MainTrain.cpp.o -c /home/omer/BIU/pFlight/MainTrain.cpp

CMakeFiles/ex2.dir/MainTrain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex2.dir/MainTrain.cpp.i"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/omer/BIU/pFlight/MainTrain.cpp > CMakeFiles/ex2.dir/MainTrain.cpp.i

CMakeFiles/ex2.dir/MainTrain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex2.dir/MainTrain.cpp.s"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/omer/BIU/pFlight/MainTrain.cpp -o CMakeFiles/ex2.dir/MainTrain.cpp.s

CMakeFiles/ex2.dir/timeseries.cpp.o: CMakeFiles/ex2.dir/flags.make
CMakeFiles/ex2.dir/timeseries.cpp.o: ../timeseries.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omer/BIU/pFlight/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ex2.dir/timeseries.cpp.o"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex2.dir/timeseries.cpp.o -c /home/omer/BIU/pFlight/timeseries.cpp

CMakeFiles/ex2.dir/timeseries.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex2.dir/timeseries.cpp.i"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/omer/BIU/pFlight/timeseries.cpp > CMakeFiles/ex2.dir/timeseries.cpp.i

CMakeFiles/ex2.dir/timeseries.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex2.dir/timeseries.cpp.s"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/omer/BIU/pFlight/timeseries.cpp -o CMakeFiles/ex2.dir/timeseries.cpp.s

CMakeFiles/ex2.dir/anomaly_detection_util.cpp.o: CMakeFiles/ex2.dir/flags.make
CMakeFiles/ex2.dir/anomaly_detection_util.cpp.o: ../anomaly_detection_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omer/BIU/pFlight/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ex2.dir/anomaly_detection_util.cpp.o"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex2.dir/anomaly_detection_util.cpp.o -c /home/omer/BIU/pFlight/anomaly_detection_util.cpp

CMakeFiles/ex2.dir/anomaly_detection_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex2.dir/anomaly_detection_util.cpp.i"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/omer/BIU/pFlight/anomaly_detection_util.cpp > CMakeFiles/ex2.dir/anomaly_detection_util.cpp.i

CMakeFiles/ex2.dir/anomaly_detection_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex2.dir/anomaly_detection_util.cpp.s"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/omer/BIU/pFlight/anomaly_detection_util.cpp -o CMakeFiles/ex2.dir/anomaly_detection_util.cpp.s

CMakeFiles/ex2.dir/SimpleAnomalyDetector.cpp.o: CMakeFiles/ex2.dir/flags.make
CMakeFiles/ex2.dir/SimpleAnomalyDetector.cpp.o: ../SimpleAnomalyDetector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omer/BIU/pFlight/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ex2.dir/SimpleAnomalyDetector.cpp.o"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex2.dir/SimpleAnomalyDetector.cpp.o -c /home/omer/BIU/pFlight/SimpleAnomalyDetector.cpp

CMakeFiles/ex2.dir/SimpleAnomalyDetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex2.dir/SimpleAnomalyDetector.cpp.i"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/omer/BIU/pFlight/SimpleAnomalyDetector.cpp > CMakeFiles/ex2.dir/SimpleAnomalyDetector.cpp.i

CMakeFiles/ex2.dir/SimpleAnomalyDetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex2.dir/SimpleAnomalyDetector.cpp.s"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/omer/BIU/pFlight/SimpleAnomalyDetector.cpp -o CMakeFiles/ex2.dir/SimpleAnomalyDetector.cpp.s

CMakeFiles/ex2.dir/HybridAnomalyDetector.cpp.o: CMakeFiles/ex2.dir/flags.make
CMakeFiles/ex2.dir/HybridAnomalyDetector.cpp.o: ../HybridAnomalyDetector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omer/BIU/pFlight/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ex2.dir/HybridAnomalyDetector.cpp.o"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex2.dir/HybridAnomalyDetector.cpp.o -c /home/omer/BIU/pFlight/HybridAnomalyDetector.cpp

CMakeFiles/ex2.dir/HybridAnomalyDetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex2.dir/HybridAnomalyDetector.cpp.i"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/omer/BIU/pFlight/HybridAnomalyDetector.cpp > CMakeFiles/ex2.dir/HybridAnomalyDetector.cpp.i

CMakeFiles/ex2.dir/HybridAnomalyDetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex2.dir/HybridAnomalyDetector.cpp.s"
	/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/omer/BIU/pFlight/HybridAnomalyDetector.cpp -o CMakeFiles/ex2.dir/HybridAnomalyDetector.cpp.s

# Object files for target ex2
ex2_OBJECTS = \
"CMakeFiles/ex2.dir/MainTrain.cpp.o" \
"CMakeFiles/ex2.dir/timeseries.cpp.o" \
"CMakeFiles/ex2.dir/anomaly_detection_util.cpp.o" \
"CMakeFiles/ex2.dir/SimpleAnomalyDetector.cpp.o" \
"CMakeFiles/ex2.dir/HybridAnomalyDetector.cpp.o"

# External object files for target ex2
ex2_EXTERNAL_OBJECTS =

ex2: CMakeFiles/ex2.dir/MainTrain.cpp.o
ex2: CMakeFiles/ex2.dir/timeseries.cpp.o
ex2: CMakeFiles/ex2.dir/anomaly_detection_util.cpp.o
ex2: CMakeFiles/ex2.dir/SimpleAnomalyDetector.cpp.o
ex2: CMakeFiles/ex2.dir/HybridAnomalyDetector.cpp.o
ex2: CMakeFiles/ex2.dir/build.make
ex2: CMakeFiles/ex2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/omer/BIU/pFlight/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ex2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex2.dir/build: ex2

.PHONY : CMakeFiles/ex2.dir/build

CMakeFiles/ex2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex2.dir/clean

CMakeFiles/ex2.dir/depend:
	cd /home/omer/BIU/pFlight/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/omer/BIU/pFlight /home/omer/BIU/pFlight /home/omer/BIU/pFlight/build /home/omer/BIU/pFlight/build /home/omer/BIU/pFlight/build/CMakeFiles/ex2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex2.dir/depend

