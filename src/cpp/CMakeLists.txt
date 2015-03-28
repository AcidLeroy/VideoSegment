add_executable(hello_world hello_world.cpp)
target_link_libraries(hello_world ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})
