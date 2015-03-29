add_executable(EvenlyDivideTest evenly_dividetest.cpp)
target_link_libraries(EvenlyDivideTest 
  EvenlyDivide
  ${OpenCV_LIBS}
  ${GTEST_BOTH_LIBRARIES})
add_test(AllTestsInSegmenter EvenlyDivideTest)
include_directories(${OpenCV_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIRS}
  )
