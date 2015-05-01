# If the pyx file is a C++ file, we should specify that here.
set_source_files_properties(
  ${VideoSegment_SOURCE_DIR}/cython/py_video_segment.pyx
  ${VideoSegment_SOURCE_DIR}/cython/py_method_accuracy/py_method_accuracy.pyx
  ${VideoSegment_SOURCE_DIR}/cython/py_user_divide/py_user_divide.pyx
  ${VideoSegment_SOURCE_DIR}/cython/py_opencv/py_opencv.pyx
  ${VideoSegment_SOURCE_DIR}/cython/py_utils/vector_numpy.pyx
  PROPERTIES CYTHON_IS_CXX TRUE )

# Multi-file cython modules do not appear to be working at the moment.
cython_add_module( py_video_segment 
py_video_segment.pyx)

target_link_libraries(py_video_segment 
  video_segmenter
   ${OpenCV_LIBS})
