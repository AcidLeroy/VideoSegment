// Copyright (c) 2015 <Cody W. Eilar>
#ifndef SRC_CPP_SEGMENTER_INTERFACE_H_
#define SRC_CPP_SEGMENTER_INTERFACE_H_
#include <iostream>
#include <stdio.h>
#include <opencv2/imgcodecs.hpp>

class SegmenterInterface {
  virtual ~SegmenterInterface();
  virtual void SegmentVideo(const cv::VideoCapture &vc, std::vector *indices);
}
#endif  // SRC_CPP_SEGMENTER_INTERFACE_H_
