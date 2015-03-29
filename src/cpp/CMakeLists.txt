#add_executable(hello_world hello_world.cpp)
#target_link_libraries(hello_world ${OpenCV_LIBS})
#include_directories(${OpenCV_INCLUDE_DIRS})
add_library(EvenlyDivide 
  evenly_divide.hpp
  evenly_divide.cpp
  segmenter_interface.hpp)
target_include_directories(EvenlyDivide PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
