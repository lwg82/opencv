# cmake needs this line
cmake_minimum_required(VERSION 2.8)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)


if(WIN32)
	set(ENV OpenCV_DIR C:/Program Files/opencv/build/x64/vc15/lib)
	message(STATUS ${OpenCV_DIR})
endif()

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

if(CMAKE_VERSION VERSION_LESS "2.8.11")
  # Add OpenCV headers location to your include paths
  include_directories(${OpenCV_INCLUDE_DIRS})
endif()

add_subdirectory(src)


# mkdir -p build/debug 
# cmake -E chdir build/debug cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=debug ../../
