cmake_minimum_required (VERSION 2.6)

project (VideoSegment)
find_package( OpenCV REQUIRED )
enable_testing()
find_package(GTest REQUIRED)

add_subdirectory(src/cpp)
add_subdirectory(test/cpp)

#target_link_libraries( VideoSegment ${OpenCV_LIBS})




