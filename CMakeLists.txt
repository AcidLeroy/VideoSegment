cmake_minimum_required (VERSION 2.8)

project (VideoSegment)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package( OpenCV REQUIRED )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake )
include(UseCython)
find_package( NumPy REQUIRED )

enable_testing()
find_package(GTest REQUIRED)

include_directories(
  ${OpenCV_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIRS}
  ${NUMPY_INCLUDE_DIRS} 
  ${VideoSegment_SOURCE_DIR}/src/evenly_divide
  ${VideoSegment_SOURCE_DIR}/src/interfaces
  ${VideoSegment_SOURCE_DIR}/src/method_accuracy
  ${VideoSegment_SOURCE_DIR}/src/user_divide
  ${VideoSegment_SOURCE_DIR}/src/video_marker)

add_subdirectory(src)
add_subdirectory(cython)

add_custom_target( ReplicatePythonSourceTree ALL ${CMAKE_COMMAND} -P
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ReplicatePythonSourceTree.cmake
  ${CMAKE_CURRENT_BINARY_DIR}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
