#include "segmenter_interface.h"
#include <algorithm>

class VideoMarker {
  public: 
    VideoMarker() : current_frame_(0),
  marker_on_(false){}
    int GetCurrentFrame() {
      return current_frame_; 
    }
    void NextFrame() {
      current_frame_++; 
      if(marker_on_)
        MarkCurrentFrame(); 
    }
    void PreviousFrame() {
      if (current_frame_ > 0)
        current_frame_--; 
      if (marker_on_)
        MarkCurrentFrame(); 
    }
    bool IsFrameMarked(int f) {
      std::vector<int>::iterator it;
      it = find (marked_frames_.begin(), marked_frames_.end(), f);
      if (it != marked_frames_.end()) {
        return true; 
       } else {
        return false; 
       }
    }

    void MarkCurrentFrame() {
      if (!IsFrameMarked(current_frame_)) 
          marked_frames_.push_back(current_frame_); 
    }
    void TurnMarkerOn(bool on) {
      // Frame I'm looking at, I want marked
      if(on)
        MarkCurrentFrame(); 
      // Frame at which I am looking I don't want marked
      else
        RemoveLastMarkedFrame(); 
      marker_on_ = on; 
    }

    void RemoveLastMarkedFrame() {
      if (marked_frames_.size() > 0)
        marked_frames_.erase(marked_frames_.end()-1); 
    }

    std::vector<int> GetMarkedFrames(){
      return marked_frames_; 
    }

    std::vector<Segment> GetSegments() {
      SortMarkedFrames(); 
      std::vector<Segment> s; 
      int start = 0; 
      int end = 0; 
      for(int i = 0; i < marked_frames_.size(); ++i) {
        if (marked_frames_.size()-1 == i) {
          s.push_back(GetSegment(start, end)); 
        } else {
          int diff = marked_frames_[i+1] - marked_frames_[i];
          if (diff > 1) {
            s.push_back(GetSegment(start, end)); 
            start = end+1; 
            end = start; 
          } else {
            end++; 
          }
        }
      }
      return s; 
    }

    void SortMarkedFrames() {
      std::sort(marked_frames_.begin(), marked_frames_.end());
    }

    Segment GetSegment(int start, int end) {
      Segment seg; 
      if (marked_frames_.size() == 0) 
        return seg; 

      int max = marked_frames_[start]; 
      int min = max; 
      for (int i = start; i <= end; ++i) {
        if (marked_frames_[i] > max) 
          max = marked_frames_[i]; 
        if (marked_frames_[i] < min) 
          min = marked_frames_[i]; 
      }
      seg.begin = min; 
      seg.end = max; 
      return seg; 
    }
  private: 
    int current_frame_;
    std::vector<int> marked_frames_;
    bool marker_on_;
};
