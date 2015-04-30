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
  std::vector<size_t> segments;
  ud.SegmentVideo(&vc, &segments);
  std::ofstream out("/tmp/test.txt");
  std::streambuf *coutbuf = std::cout.rdbuf();
  std::cout.rdbuf(out.rdbuf());
  std::cout << "marked_frames\n";
  for (auto &i : segments) {
    std::cout << i << "\n";
  }
  std::cout.rdbuf(coutbuf);
  out.close();

  return 0;
}
