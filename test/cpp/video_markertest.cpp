#include "gtest/gtest.h"
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
        std::cout << "Start = " << start << " End = " << end << std::endl; 
        if (marked_frames_.size()-1 == i) {
          std::cout << "Pushed " << start << ", " << end << std::endl;
          s.push_back(GetSegment(start, end)); 
        } else {
          int diff = marked_frames_[i+1] - marked_frames_[i];
          if (diff > 1) {
            std::cout << "Pushed " << start << ", " << end << std::endl;
            s.push_back(GetSegment(start, end)); 
            std::cout << "Diff graeter than 1.\n"; 
            start = end+1; 
            end = start; 
          } else {
            std::cout << "Incremented end\n";
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

      std::cout << "Marked frames size = " << 
        marked_frames_.size() << std::endl; 

      int max = marked_frames_[start]; 
      int min = max; 
      for (int i = start; i <= end; ++i) {
        std::cout << "get seg: " << i << "\n"; 
        if (marked_frames_[i] > max) 
          max = marked_frames_[i]; 
        if (marked_frames_[i] < min) 
          min = marked_frames_[i]; 
      }
      std::cout << "Begin = " << min << " End = " << max << std::endl;
      seg.begin = min; 
      seg.end = max; 
      return seg; 
    }
  private: 
    int current_frame_;
    std::vector<int> marked_frames_;
    bool marker_on_;
};

class VideoMarkerTest : public ::testing::Test {
  public: 
    VideoMarker vm; 
};

TEST_F(VideoMarkerTest, TestCurrentFrame)
{
  ASSERT_EQ(vm.GetCurrentFrame(), 0); 
}

TEST_F(VideoMarkerTest, TestNextFrame) {
  EXPECT_EQ(vm.GetCurrentFrame(), 0); 
  vm.NextFrame(); 
  EXPECT_EQ(vm.GetCurrentFrame(), 1); 
}

TEST_F(VideoMarkerTest, TestPreviousFrame){
  EXPECT_EQ(vm.GetCurrentFrame(), 0); 
  vm.NextFrame(); 
  vm.PreviousFrame();  
  EXPECT_EQ(vm.GetCurrentFrame(), 0); 
}

TEST_F(VideoMarkerTest, TestNegativeFrame) {
  vm.PreviousFrame(); 
  EXPECT_EQ(vm.GetCurrentFrame(), 0);
}

TEST_F(VideoMarkerTest, TestFrameNotMarked) {
  EXPECT_FALSE(vm.IsFrameMarked(0));
}

TEST_F(VideoMarkerTest, TestMarkCurrentFrame) {
  vm.MarkCurrentFrame(); 
  EXPECT_TRUE(vm.IsFrameMarked(0));
}

TEST_F(VideoMarkerTest, TestNextMarkedFrame) {
  vm.TurnMarkerOn(true); 
  EXPECT_TRUE(vm.IsFrameMarked(0));
  vm.NextFrame(); 
  EXPECT_TRUE(vm.IsFrameMarked(1));
}

TEST_F(VideoMarkerTest, TestPreviousMarkedFrame) {
  vm.TurnMarkerOn(true); 
  vm.NextFrame(); 
  vm.PreviousFrame(); 
  EXPECT_TRUE(vm.IsFrameMarked(
        vm.GetCurrentFrame())); 
}

TEST_F(VideoMarkerTest, TestDuplicateMarkedFrames) {
  vm.TurnMarkerOn(true); 
  vm.NextFrame(); 
  vm.PreviousFrame();
  std::vector<int> m_frames = vm.GetMarkedFrames(); 
  EXPECT_EQ(m_frames.size(), 2); 
}

TEST_F(VideoMarkerTest, TestGetSingleSegment) {
  //0
  vm.NextFrame(); 
  //1
  vm.NextFrame(); 
  // Turn marker on on the current frame
  vm.TurnMarkerOn(true);  
  //2
  vm.NextFrame(); 
  //3
  vm.NextFrame(); 
  //4 Turn marker off on the current frame. 
  vm.TurnMarkerOn(false); 
  vm.NextFrame(); 
  vm.NextFrame(); 
  std::vector<Segment>exp_segs =  vm.GetSegments(); 
  std::vector<int> marks = vm.GetMarkedFrames(); 
  for (int i = 0; i< marks.size(); ++i) 
    std::cout << "marks = " << marks[i] << std::endl; 
  ASSERT_EQ(1, exp_segs.size()); 
  EXPECT_EQ(2, exp_segs[0].begin); 
  EXPECT_EQ(3, exp_segs[0].end); 
  
}

TEST_F(VideoMarkerTest, TestTurningOffMarking) {
  vm.TurnMarkerOn(true); 
  vm.TurnMarkerOn(false); 
  std::vector<int> marks = vm.GetMarkedFrames(); 
  EXPECT_EQ(0, marks.size());
}

TEST_F(VideoMarkerTest, TestSortedFrames) {
  vm.NextFrame(); //1 
  vm.NextFrame(); //2 
  vm.TurnMarkerOn(true); //2 
  vm.PreviousFrame(); // 1 
  vm.PreviousFrame(); // 0 
  vm.SortMarkedFrames(); 
  std::vector<int> frames = vm.GetMarkedFrames(); 
  EXPECT_EQ(0, frames[0]); 
  EXPECT_EQ(1, frames[1]); 
}

TEST_F(VideoMarkerTest, TestGetMultipleSegment) {
  vm.NextFrame(); //1
  vm.NextFrame(); //2 
  vm.TurnMarkerOn(true); //2 
  vm.NextFrame(); //3 
  vm.NextFrame(); //4 
  vm.TurnMarkerOn(false); //4 
  vm.NextFrame(); //5 
  vm.NextFrame(); //6 
  vm.TurnMarkerOn(true); //6 
  vm.NextFrame();//7 
  vm.NextFrame();//8  
  std::vector<Segment>exp_segs =  vm.GetSegments(); 
  ASSERT_EQ(2, exp_segs.size()); 
  EXPECT_EQ(2, exp_segs[0].begin); 
  EXPECT_EQ(3, exp_segs[0].end); 
  EXPECT_EQ(6, exp_segs[1].begin); 
  EXPECT_EQ(8, exp_segs[1].end); 

}
