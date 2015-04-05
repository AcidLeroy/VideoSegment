add_executable(EvenlyDivideTest evenly_dividetest.cpp)
add_executable(UserDivideTest user_dividetest.cpp)
add_executable(VideoMarkerTest video_markertest.cpp)

include_directories(${OpenCV_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIRS}
  ../../src/cpp/
  )

target_link_libraries(EvenlyDivideTest 
  EvenlyDivide
  ${OpenCV_LIBS}
  ${GTEST_BOTH_LIBRARIES})

target_link_libraries(UserDivideTest 
  UserDivide
  ${OpenCV_LIBS}
  ${GTEST_BOTH_LIBRARIES})

target_link_libraries(VideoMarkerTest 
  VideoMarker
  ${GTEST_BOTH_LIBRARIES})

add_test(AllTestsInSegmenter EvenlyDivideTest)
add_test(AllTestsInSegmenter UserDivideTest)
add_test(AllTestsInSegmenter VideoMarkerTest)
