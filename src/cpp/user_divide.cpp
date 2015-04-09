// Copyright (c) 2015 <Cody W. Eilar>
#include "user_divide.h"  // NOLINT
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

void UserDivide::CallBackFunc(int event, int x, int y, int flags,
		void *userdata) {
	UserDivide *ud = static_cast<UserDivide*>(userdata);
	if (event == cv::EVENT_LBUTTONDOWN) {
		// Increment video
		std::cout << "Left clicked: (" << x << "," << y << ")\n";
		cv::Mat frame;
		bool success = ud->vid_->read(frame);
		if (!success)
			throw std::runtime_error("Cannot read frame!\n");
		//ud->ShowFrame(frame, ud->win_name_);

	} else if (event == cv::EVENT_RBUTTONDOWN) {
		// Toggle start and stop
		std::cout << "Right clicked: (" << x << "," << y << ")\n";
		const int curr_frame = static_cast<int>(ud->vid_->get(
				cv::CAP_PROP_POS_FRAMES) - 1);
		std::cout << "Current frame is: " << curr_frame << std::endl;
		if (curr_frame == ud->current_seg_.begin)
			return;
		if (ud->toggle_) {
			std::cout << "Begin frame =" << curr_frame << std::endl;
			ud->current_seg_.begin = curr_frame;
		} else {
			std::cout << "End frame = " << curr_frame << std::endl;
			ud->current_seg_.end = curr_frame;
			ud->segments_.push_back(ud->current_seg_);
		}
		ud->toggle_ = !ud->toggle_;
	}
}

void UserDivide::ShowFrame(const VideoMarker &vm) {
	// Resize image because it is too big

	std::cout << "current frame is: "<< vm.GetCurrentFrame() << std::endl;
	vid_->set(cv::CAP_PROP_POS_FRAMES, static_cast<double>(vm.GetCurrentFrame()+1));
	cv::Mat frame;
	bool success = vid_->read(frame);
		if (!success)
			throw std::runtime_error("Cannot read frame!\n");
	cv::resize(frame, frame, cv::Size(frame.cols, frame.rows));

	if (marker_) {
		std::string text = "MARKING CURRENT FRAME.";
		int fontFace = cv::FONT_HERSHEY_PLAIN;
		double fontScale = 1;
		int thickness = 1;
		int baseline=0;
		cv::Size textSize = cv::getTextSize(text, fontFace,
		                            fontScale, thickness, &baseline);
		baseline += thickness;
		// center the text
		cv::Point textOrg((frame.cols - textSize.width)/2,
		              (frame.rows + textSize.height)/2);
		cv::putText(frame, text, textOrg, fontFace, fontScale,
		        cv::Scalar::all(255), thickness, 8);
	}

	cv::imshow(win_name_, frame);
}

void UserDivide::SegmentVideo(cv::VideoCapture *vc,
		std::vector<Segment> *indices) {
	// Set local pointer
	if (vc != NULL)
		vid_ = vc;
	else
		throw std::runtime_error("Received NULL pointer!\n");

	VideoMarker vm;

	toggle_ = true;
	marker_ = false;
	current_seg_.begin = -1;
	current_seg_.end = -1;

	cv::Mat frame;
	bool success = vid_->read(frame);
	if (!success)
		throw std::runtime_error("Cannot read 1st frame!\n");

	// Show first frame
	win_name_ = "w";
	cv::namedWindow(win_name_);
	cv::setMouseCallback(win_name_, CallBackFunc, static_cast<void*>(this));
	ShowFrame(vm);

	while (1) {
		int c = cv::waitKey(100) & 0xff;
		switch (c) {
		case 3: // right arrow
			std::cout << "Right arrow\n";
			vm.NextFrame();
			ShowFrame(vm);
			break;

		case 2: // left arrow
			std::cout << "Left arrow\n";
			vm.PreviousFrame();
			ShowFrame(vm);
			break;

		case 0: // up arrow
			std::cout << "Up arrow\n";
			vm.NextFrame();
			ShowFrame(vm);
			break;

		case 1: // down arrow
			std::cout << "Down arrow\n";
			vm.PreviousFrame();
			ShowFrame(vm);
			break;

		case 109: // m for mark
			marker_ = !marker_;
			vm.TurnMarkerOn(marker_);
			std::cout << "Marking frame = " << marker_ << std::endl;
			ShowFrame(vm);
			break;
		case 27: // esc
			std::cout << "Exiting...\n";
			std::vector<Segment> segs = vm.GetSegments();
			for (int i = 0; i < segs.size(); ++i){
				std::cout << "Segment " << i << ": \n";
			    std::cout << "\t start = " << segs[i].begin << std::endl;
				std::cout << "\t end = " << segs[i].end << std::endl;
			}
			*indices = segs;
			return;
		}
	}

}
