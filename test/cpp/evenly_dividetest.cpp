// Copyright (c) 2015 <Cody W. Eilar>
#include "evenly_divide.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include "gtest/gtest.h"

TEST(EvenlyDivide, values) {
  cv::VideoCapture vc;
  std::vector<int> idx;
  EvenlyDivide ed;
  ed.SegmentVideo(vc, &idx);
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(idx[i], i + 1) << "values at i="<<i<<std::endl;
  }
}
