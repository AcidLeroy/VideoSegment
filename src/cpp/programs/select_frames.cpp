#include "user_divide.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream> 
#include <string>

int main(int argc, char *argv[]) {
  std::string filename = "/Volumes/my_data/data/Movies/GroupD/GO010077D21.MP4";
  cv::VideoCapture vc(filename);
  UserDivide ud; 
  std::vector<Segment> segments;  
  //ud.SegmentVideo(&vc, &segments);  
  return 0;
}
