// Copyright (c) 2015 <Cody W. Eilar>
#include "evenly_divide.h"  // NOLINT
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include "gtest/gtest.h"

TEST(EvenlyDivide, Constructor) {
  EvenlyDivide ed;
  ASSERT_FALSE(&ed == NULL);
}

TEST(EvenlyDivide, NumberDivisions) {
  EvenlyDivide ed;
  int const expected_div = 4;
  ed.SetNumDivisions(expected_div);
  ASSERT_EQ(expected_div, ed.GetNumDivisions());
}

TEST(EvenlyDivide, InvalidVideoCapture) {
  cv::VideoCapture vc;
  std::vector<Segment> idx;
  EvenlyDivide ed;
  int const expected_divs = 4;
  ed.SetNumDivisions(expected_divs);
  ASSERT_THROW(ed.SegmentVideo(&vc, &idx), std::runtime_error);
}

TEST(EvenlyDivide, TestDivisions) {
  const std::string filename =
      "/Volumes/my_data/data/Movies/GroupD/GO010077D21.MP4";
  cv::VideoCapture vc(filename);
  std::vector<Segment> idx;
  EvenlyDivide ed;
  int const expected_max_frames = 16;
  ed.SetMaxFrames(expected_max_frames);
  EXPECT_TRUE(expected_max_frames == ed.GetMaxFrames());
  static int const expected_divs = 4;
  std::vector<Segment> expected_seg; 
  Segment s[expected_divs] = {{0, 3}, {4,7}, {8, 11}, {12, 15}}; 
  for (int i = 0; i < expected_divs; ++i)
    expected_seg.push_back(s[i]); 
  ed.SetNumDivisions(expected_divs);
  ed.SegmentVideo(&vc, &idx);
  ASSERT_TRUE(expected_divs == idx.size());
  for (int i = 0; i < expected_divs; ++i) {
    EXPECT_EQ(expected_seg[i].begin, idx[i].begin) << " on index " << i; 
    EXPECT_EQ(expected_seg[i].end, idx[i].end) << " on index " << i; 
  }
}
