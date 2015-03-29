// Copyright (c) 2015 <Cody W. Eilar>
#include "evenly_divide.h" // NOLINT
#include <vector>
EvenlyDivide::EvenlyDivide() {}
EvenlyDivide::~EvenlyDivide() {}

void EvenlyDivide::SegmentVideo(const cv::VideoCapture &vc,
                                std::vector<int> *indicies) {
  indicies->push_back(1);
  indicies->push_back(2);
  indicies->push_back(3);
}
