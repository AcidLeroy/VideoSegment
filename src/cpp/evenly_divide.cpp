// Copyright (c) 2015 <Cody W. Eilar>
#include "evenly_divide.h"  // NOLINT
#include <iostream>
#include <exception>
#include <vector>
#include "opencv2/opencv.hpp"

EvenlyDivide::EvenlyDivide() {}
EvenlyDivide::~EvenlyDivide() {}

void EvenlyDivide::SegmentVideo(cv::VideoCapture &vc,
                                std::vector<int> *indicies) {
  if (!vc.isOpened()) {
    throw std::runtime_error("VideoCapture is not open!");
    return;
  }

  int count = 0;
  cv::Mat frame;
  while (1) {
    vc >> frame;
    if (frame.empty()) break;
    count++;
  }
  indicies->push_back(1);
  indicies->push_back(2);
  indicies->push_back(3);
}
