add_library(EvenlyDivide STATIC
  evenly_divide.h
  evenly_divide.cpp
  segmenter_interface.h)
target_include_directories(EvenlyDivide PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(EvenlyDivide
  ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})


add_library(UserDivide STATIC
  user_divide.h
  user_divide.cpp
  segmenter_interface.h)
target_include_directories(UserDivide PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(UserDivide
  ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})
