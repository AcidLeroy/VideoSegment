// Copyright (c) 2015 <Cody W. Eilar>
#ifndef SRC_CPP_EVENLY_DIVIDE_H_
#define SRC_CPP_EVENLY_DIVIDE_H_
#include <vector>
#include "segmenter_interface.h"  // NOLINT
class EvenlyDivide : public SegmenterInterface {
 public:
  // dtor
  virtual ~EvenlyDivide();
  EvenlyDivide();
  void SetNumDivisions(int div) { num_divisions_ = div; }
  int GetNumDivisions() { return num_divisions_; }
  inline void SetMaxFrames(int frames) { max_frames_ = frames; }
  inline int GetMaxFrames() const { return (max_frames_); }
  virtual void SegmentVideo(cv::VideoCapture *vc,
                            std::vector<Segment> *indices);

 private:
  int num_divisions_;
  int max_frames_;
};
#endif  // SRC_CPP_EVENLY_DIVIDE_H_
