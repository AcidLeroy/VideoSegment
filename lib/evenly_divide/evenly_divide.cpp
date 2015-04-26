// Copyright (c) 2015 <Cody W. Eilar>
#include "evenly_divide.h"  // NOLINT
#include <iostream>
#include <exception>
#include <vector>
#include "opencv2/opencv.hpp"

EvenlyDivide::EvenlyDivide() : max_frames_(-1) {}
EvenlyDivide::~EvenlyDivide() {}

void EvenlyDivide::SegmentVideo(cv::VideoCapture *vc,
                                std::vector<Segment> *indicies) {
  if (!vc->isOpened()) {
    throw std::runtime_error("VideoCapture is not open!");
    return;
  }

  int count = 0;
  cv::Mat frame;
  while (1) {
    if (max_frames_ >= 0)
      if (count > max_frames_) break;
    *vc >> frame;
    if (frame.empty()) break;
    std::cout << "Received frame: " << count << std::endl;
    count++;
  }

  int stride = count / num_divisions_;
  int value = 0;
  for (int i = 0; i < num_divisions_; ++i) {
    Segment s = {value, value + stride - 1};
    indicies->push_back(s);
    value += stride;
  }
}
