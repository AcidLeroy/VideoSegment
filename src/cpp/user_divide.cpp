// Copyright (c) 2015 <Cody W. Eilar>
#include "user_divide.h"  // NOLINT
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

void UserDivide::CallBackFunc(int event, int x, int y, 
    int flags, void *userdata){
  UserDivide *ud = static_cast<UserDivide*>(userdata); 
  if  ( event == cv::EVENT_LBUTTONDOWN ) {
    // Increment video
    std::cout << "Left clicked: ("<<x<<","<<y<<")\n";
    cv::Mat frame; 
    bool success = ud->vid_->read(frame);
    if(!success)
      throw std::runtime_error("Cannot read frame!\n"); 
    ud->ShowFrame(frame, ud->win_name_); 

  }
  else if  ( event == cv::EVENT_RBUTTONDOWN ) {
    // Toggle start and stop
    std::cout << "Right clicked: ("<<x<<","<<y<<")\n";
    const int curr_frame = static_cast<int>(
        ud->vid_->get(cv::CAP_PROP_POS_FRAMES)-1); 
    std::cout << "Current frame is: " << curr_frame << std::endl;
    if (curr_frame == ud->current_seg_.begin)
      return;
    if (ud->toggle_) { 
      std::cout << "Begin frame =" << curr_frame << std::endl;
      ud->current_seg_.begin = curr_frame; 
    } else {
      std::cout << "End frame = " << curr_frame << std::endl; 
      ud->current_seg_.end =  curr_frame;           
      ud->segments_.push_back(ud->current_seg_);
    }
    ud->toggle_ = !ud->toggle_; 
  }
}

void UserDivide::ShowFrame(const cv::Mat &frame, const std::string &win_name_) {
  // Resize image because it is too big
  cv::Mat oFrame; 
  cv::resize(frame, oFrame, 
      cv::Size(frame.cols/2, frame.rows/2)); 
  cv::imshow(win_name_, oFrame); 
}

void UserDivide::SegmentVideo(cv::VideoCapture *vc, 
    std::vector<Segment> *indices) {
  // Set local pointer
  if (vc != NULL) 
    vid_ = vc; 
  else 
    throw std::runtime_error("Received NULL pointer!\n"); 

  toggle_ = true; 
  current_seg_.begin = -1;
  current_seg_.end = -1; 

  cv::Mat frame; 
  bool success = vc->read(frame);
  if(!success)
    throw std::runtime_error("Cannot read frame!\n"); 

  // Show first frame
  win_name_ = "w"; 
  cv::namedWindow(win_name_); 
  cv::setMouseCallback(win_name_, CallBackFunc,
      static_cast<void*>(this));  
  ShowFrame(frame, win_name_); 
  cv::waitKey(0); 
}
