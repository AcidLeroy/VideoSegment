// Copyright (c) 2015 <Cody W. Eilar>
#ifndef SRC_CPP_EVENLY_DIVIDE_H_
#define SRC_CPP_EVENLY_DIVIDE_H_
#include <vector>
#include "segmenter_interface.h" // NOLINT
class EvenlyDivide : public SegmenterInterface {
 public:
  // dtor
  virtual ~EvenlyDivide();
  EvenlyDivide();
  virtual void SegmentVideo(const cv::VideoCapture &vc,
                            std::vector<int> *indices);
};
#endif  // SRC_CPP_EVENLY_DIVIDE_H_
