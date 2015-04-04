// Copyright (c) 2015 <Cody W. Eilar>
#include "user_divide.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include "gtest/gtest.h"

// Test code
class UserDivideTest : public ::testing::Test{
  protected:
    virtual void SetUp() {
      filename = 
        "/Volumes/my_data/data/Movies/GroupD/GO010077D21.MP4";

    }
    UserDivide ud; 
    std::string filename; 
    std::vector<Segment> segments; 
      
};

TEST_F(UserDivideTest, TestNamedWindow) {
  cv::VideoCapture vc(filename); 
  ud.SegmentVideo(&vc, &segments); 
}

