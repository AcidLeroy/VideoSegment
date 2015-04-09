#include "user_divide.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream> 
#include <string>

int main(int argc, char *argv[]) {
  std::string filename = "/Users/cody/test.mov";
  cv::VideoCapture vc(filename);
  UserDivide ud; 
  std::vector<Segment> segments;  
  ud.SegmentVideo(&vc, &segments);  
  return 0;
}
