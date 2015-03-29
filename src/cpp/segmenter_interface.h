// Copyright (c) 2015 <Cody W. Eilar>
#ifndef SRC_CPP_SEGMENTER_INTERFACE_H_
#define SRC_CPP_SEGMENTER_INTERFACE_H_
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

class SegmenterInterface {
 public:
  virtual ~SegmenterInterface() {}
  virtual void SegmentVideo(const cv::VideoCapture &vc,
                            std::vector<int> *indices) = 0;
};
#endif  // SRC_CPP_SEGMENTER_INTERFACE_H_
