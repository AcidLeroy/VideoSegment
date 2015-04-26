add_executable(SelectFrames select_frames.cpp)
target_link_libraries(SelectFrames
    UserDivide
    VideoMarker
  ${OpenCV_LIBS})
  
include_directories(../ 
${OpenCV_INCLUDE_DIRS})
