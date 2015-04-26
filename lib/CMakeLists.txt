# Include dirs
include_directories( ${OpenCV_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIRS}
  interfaces
  evenly_divide
  video_marker
  user_divide
  )

# Library shared objects
add_library(video_segmenter SHARED
  interfaces/segmenter_interface.h

  evenly_divide/evenly_divide.h
  evenly_divide/evenly_divide.cpp

  video_marker/video_marker.h
  video_marker/video_marker.cpp

  user_divide/user_divide.h
  user_divide/user_divide.cpp
  )

target_link_libraries(video_segmenter
  ${OpenCV_LIBS}
  )

# Tests
#add_executable(EvenlyDivideTest evenly_dividetest.cpp)
#add_executable(UserDivideTest user_dividetest.cpp)

add_executable(video_marker_test video_marker/video_marker_test.cpp)
target_link_libraries(video_marker_test 
  ${GTEST_BOTH_LIBRARIES}
  video_segmenter)
add_test(segmenter_tests video_marker_test)

add_executable(method_accuracy_test
  method_accuracy/method_accuracy_test.cpp)
target_link_libraries(method_accuracy_test 
  ${GTEST_BOTH_LIBRARIES}
  video_segmenter)
add_test(segmenter_tests method_accuracy_test)

#add_executable(MethodAccuracyTest method_accuracy.cpp)
#
#include_directories(${OpenCV_INCLUDE_DIRS}
#  ${GTEST_INCLUDE_DIRS}
#  ../../src/cpp/
#  )
#
#target_link_libraries(EvenlyDivideTest 
#  EvenlyDivide
#  ${OpenCV_LIBS}
#  ${GTEST_BOTH_LIBRARIES})
#
#target_link_libraries(UserDivideTest 
#  UserDivide
#  VideoMarker
#  ${OpenCV_LIBS}
#  ${GTEST_BOTH_LIBRARIES})
#
#target_link_libraries(VideoMarkerTest 
#  VideoMarker
#  ${GTEST_BOTH_LIBRARIES})
#
#target_link_libraries(MethodAccuracyTest 
#  ${GTEST_BOTH_LIBRARIES})
#
#add_test(AllTestsInSegmenter EvenlyDivideTest)
#add_test(AllTestsInSegmenter UserDivideTest)
#add_test(AllTestsInSegmenter VideoMarkerTest)
#add_test(AllTestsInSegmenter MethodAccuracyTest)
