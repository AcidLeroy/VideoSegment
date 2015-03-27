cmake_minimum_required (VERSION 2.6)

project (VideoSegment)
find_package( OpenCV REQUIRED )

add_subdirectory(src)
add_subdirectory(test)

#target_link_libraries( VideoSegment ${OpenCV_LIBS})




