// Copyright (c) 2015 <Cody W. Eilar>
#include "segmenter_interface.h"  // NOLINT
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

class UserDivide : public SegmenterInterface{
  public: 
    UserDivide(); 
    ~UserDivide();
    static void CallBackFunc(int event, int x, int y, 
        int flags, void *userdata);

    void ShowFrame(const cv::Mat &frame, const std::string &win_name_) ;

    virtual void SegmentVideo(cv::VideoCapture *vc, 
        std::vector<Segment> *indices);  
  private: 
    cv::VideoCapture * vid_; 
    std::string win_name_; 
    std::vector<Segment> segments_; 
    Segment current_seg_; 
    bool toggle_; 

}; 
