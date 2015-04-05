#include "gtest/gtest.h"
#include "segmenter_interface.h"

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
      if(on)
        MarkCurrentFrame(); 
      marker_on_ = on; 
    }

    std::vector<int> GetMarkedFrames(){
      return marked_frames_; 
    }

    std::vector<Segment> GetSegments() {
      std::vector<Segment> s; 
      Segment seg; 
      int max = *max_element(std::begin(marked_frames_), 
          std::end(marked_frames_));
      int min = *min_element(std::begin(marked_frames_), 
          std::end(marked_frames_));
      seg.begin = min; 
      seg.end = max; 
      s.push_back(seg); 
      return s; 
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
  vm.TurnMarkerOn(true); 
  //2
  vm.NextFrame(); 
  //3
  vm.NextFrame(); 
  //4
  vm.TurnMarkerOn(false); 
  vm.NextFrame(); 
  vm.NextFrame(); 
  std::vector<Segment>exp_segs =  vm.GetSegments(); 
  std::vector<int> marks = vm.GetMarkedFrames(); 
  for (int i = 0; i< marks.size(); ++i) 
    std::cout << "marks = " << marks[i] << std::endl;
  ASSERT_EQ(exp_segs.size(), 1); 
  EXPECT_EQ(exp_segs[0].begin, 2); 
  EXPECT_EQ(exp_segs[0].end, 4); 
  
}

TEST_F(VideoMarkerTest, DISABLED_TestGetMultipleSegment) {
  vm.NextFrame(); 
  vm.NextFrame(); 
  vm.TurnMarkerOn(true); 
  vm.NextFrame(); 
  vm.NextFrame(); 
  vm.TurnMarkerOn(false); 
  vm.NextFrame(); 
  vm.NextFrame(); 
  vm.TurnMarkerOn(true); 
  vm.NextFrame(); 
  vm.NextFrame(); 
  std::vector<Segment>exp_segs =  vm.GetSegments(); 
  ASSERT_EQ(exp_segs.size(), 2); 
}
