// Copyright (c) 2015 <Cody W. Eilar>
#include "user_divide.h"  // NOLINT
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <stdexcept>

void UserDivide::CallBackFunc(int event, int x, int y, int flags,
                              void *userdata) {
  UserDivide *ud = static_cast<UserDivide *>(userdata);
  if (event == cv::EVENT_LBUTTONDOWN) {
    // Increment video
    std::cout << "Left clicked: (" << x << "," << y << ")\n";

  } else if (event == cv::EVENT_RBUTTONDOWN) {
    // Toggle start and stop
    std::cout << "Right clicked: (" << x << "," << y << ")\n";
  }
}

void UserDivide::ShowFrame() {
  // Resize image because it is too big
  std::cout << "current frame is: " << vm_->GetCurrentFrame() << std::endl;
  vid_->set(cv::CAP_PROP_POS_FRAMES,
            static_cast<double>(vm_->GetCurrentFrame() + 1));
  cv::Mat frame;
  bool success = vid_->read(frame);
  if (!success) throw std::runtime_error("Cannot read frame!\n");
  cv::resize(frame, frame, cv::Size(frame.cols, frame.rows));

  if (marker_) {
    std::string text = "MARKING CURRENT FRAME.";
    AddText(text, &frame);
  }
  if (unmark_frame_) {
    std::string text = "UNMARKING CURRENT FRAME.";
    vm_->UnmarkCurrentFrame();
    AddText(text, &frame);
  }

  cv::imshow(win_name_, frame);
}

void UserDivide::AddText(const std::string &txt, cv::Mat *frame) {
  if (frame == NULL) {
    throw std::runtime_error("Null pointer received");
  }
  int fontFace = cv::FONT_HERSHEY_PLAIN;
  double fontScale = 1;
  int thickness = 2;
  int baseline = 0;
  cv::Size textSize =
      cv::getTextSize(txt, fontFace, fontScale, thickness, &baseline);
  baseline += thickness;
  // center the text
  cv::Point textOrg((frame->cols - textSize.width) / 2,
                    (frame->rows + textSize.height) / 2);
  cv::putText(*frame, txt, textOrg, fontFace, fontScale, cv::Scalar::all(0x000),
              thickness, 8);
}

void UserDivide::SegmentVideo(cv::VideoCapture *vc,
                              std::vector<size_t> *indices) {
  // Set local pointer
  if (vc != NULL)
    vid_ = vc;
  else
    throw std::runtime_error("Received NULL pointer!\n");

  vm_.reset(new VideoMarker);

  toggle_ = true;
  marker_ = false;
  unmark_frame_ = false;

  cv::Mat frame;
  bool success = vid_->read(frame);
  if (!success) throw std::runtime_error("Cannot read 1st frame!\n");

  // Show first frame
  win_name_ = "Manually Select Frames";
  cv::namedWindow(win_name_, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
  ShowFrame();

  while (1) {
    int c = cv::waitKey(1000) & 0xff;
    switch (c) {
      case 3:  // right arrow
        std::cout << "Right arrow\n";
        vm_->NextFrame();
        ShowFrame();
        break;

      case 2:  // left arrow
        std::cout << "Left arrow\n";
        vm_->PreviousFrame();
        ShowFrame();
        break;

      case 0:  // up arrow
        std::cout << "Up arrow\n";
        vm_->NextFrame();
        ShowFrame();
        break;

      case 1:  // down arrow
        std::cout << "Down arrow\n";
        vm_->PreviousFrame();
        ShowFrame();
        break;

      case 109:  // m for mark
        marker_ = !marker_;
        unmark_frame_ = false;
        vm_->TurnMarkerOn(marker_);
        std::cout << "Marking frame = " << marker_ << std::endl;
        ShowFrame();
        break;
      case 114:  // r remove marked frame
        marker_ = false;
        vm_->TurnMarkerOn(false);
        unmark_frame_ = !unmark_frame_;
        ShowFrame();
        break;

      case 27:  // esc
        std::cout << "Marked frames: \n";
        std::vector<size_t> segs = vm_->GetMarkedFrames();
        for (auto &i : segs) {
          std::cout << i << ", ";
        }
        std::cout << std::endl;
        *indices = segs;
        return;
    }
  }
}
