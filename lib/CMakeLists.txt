# Include dirs
include_directories( ${OpenCV_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIRS}
  evenly_divide
  interfaces
  method_accuracy
  user_divide
  video_marker
  )

# Library shared objects
add_library(video_segmenter SHARED
  evenly_divide/evenly_divide.cpp
  evenly_divide/evenly_divide.h

  interfaces/segmenter_interface.h

  method_accuracy/method_accuracy.h

  user_divide/user_divide.cpp
  user_divide/user_divide.h

  video_marker/video_marker.cpp
  video_marker/video_marker.h
  )

target_link_libraries(video_segmenter
  ${OpenCV_LIBS}
  )

# Tests
add_executable(video_marker_test video_marker/video_marker_test.cpp)
target_link_libraries(video_marker_test 
  ${GTEST_BOTH_LIBRARIES}
  video_segmenter)
add_test( NAME video_marker_test  COMMAND video_marker_test)

add_executable(method_accuracy_test
  method_accuracy/method_accuracy_test.cpp)
target_link_libraries(method_accuracy_test 
  ${GTEST_BOTH_LIBRARIES}
  video_segmenter)
add_test( NAME method_accuracy_test  COMMAND method_accuracy_test)
