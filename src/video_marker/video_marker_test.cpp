#include "gtest/gtest.h"
#include "video_marker.cpp"

class VideoMarkerTest : public ::testing::Test {
 public:
  VideoMarker vm;
};

TEST_F(VideoMarkerTest, TestCurrentFrame) {
  ASSERT_EQ(vm.GetCurrentFrame(), 0);
}

TEST_F(VideoMarkerTest, TestNextFrame) {
  EXPECT_EQ(vm.GetCurrentFrame(), 0);
  vm.NextFrame();
  EXPECT_EQ(vm.GetCurrentFrame(), 1);
}

TEST_F(VideoMarkerTest, TestPreviousFrame) {
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
  EXPECT_TRUE(vm.IsFrameMarked(vm.GetCurrentFrame()));
}

TEST_F(VideoMarkerTest, TestDuplicateMarkedFrames) {
  vm.TurnMarkerOn(true);
  vm.NextFrame();
  vm.PreviousFrame();
  std::vector<size_t> m_frames = vm.GetMarkedFrames();
  EXPECT_EQ(m_frames.size(), 2);
}

TEST_F(VideoMarkerTest, TestGetSingleSegment) {
  // 0
  vm.NextFrame();
  // 1
  vm.NextFrame();
  // Turn marker on on the current frame
  vm.TurnMarkerOn(true);
  // 2
  vm.NextFrame();
  // 3
  vm.NextFrame();
  // 4 Turn marker off on the current frame.
  vm.TurnMarkerOn(false);
  vm.NextFrame();
  vm.NextFrame();
  std::vector<Segment> exp_segs = vm.GetSegments();
  std::vector<size_t> marks = vm.GetMarkedFrames();
  ASSERT_EQ(1, exp_segs.size());
  EXPECT_EQ(2, exp_segs[0].begin);
  EXPECT_EQ(3, exp_segs[0].end);
}

TEST_F(VideoMarkerTest, TestTurningOffMarking) {
  vm.TurnMarkerOn(true);
  vm.TurnMarkerOn(false);
  std::vector<size_t> marks = vm.GetMarkedFrames();
  EXPECT_EQ(0, marks.size());
}

TEST_F(VideoMarkerTest, TestSortedFrames) {
  vm.NextFrame();         // 1
  vm.NextFrame();         // 2
  vm.TurnMarkerOn(true);  // 2
  vm.PreviousFrame();     // 1
  vm.PreviousFrame();     // 0
  vm.SortMarkedFrames();
  std::vector<size_t> frames = vm.GetMarkedFrames();
  EXPECT_EQ(0, frames[0]);
  EXPECT_EQ(1, frames[1]);
}

TEST_F(VideoMarkerTest, TestGetMultipleSegment) {
  vm.NextFrame();          // 1
  vm.NextFrame();          // 2
  vm.TurnMarkerOn(true);   // 2
  vm.NextFrame();          // 3
  vm.NextFrame();          // 4
  vm.TurnMarkerOn(false);  // 4
  vm.NextFrame();          // 5
  vm.NextFrame();          // 6
  vm.TurnMarkerOn(true);   // 6
  vm.NextFrame();          // 7
  vm.NextFrame();          // 8
  std::vector<Segment> exp_segs = vm.GetSegments();
  ASSERT_EQ(2, exp_segs.size());
  EXPECT_EQ(2, exp_segs[0].begin);
  EXPECT_EQ(3, exp_segs[0].end);
  EXPECT_EQ(6, exp_segs[1].begin);
  EXPECT_EQ(8, exp_segs[1].end);
}

TEST_F(VideoMarkerTest, TestRemoveFrames) {
  vm.TurnMarkerOn(true);    // 0 - marked
  vm.NextFrame();           // 1 - marked
  vm.UnmarkCurrentFrame();  // 1 unmarked
  vm.PreviousFrame();       // 0
  vm.UnmarkCurrentFrame();  // 0 unmarked
  ASSERT_EQ(0, vm.GetMarkedFrames().size());
}

TEST_F(VideoMarkerTest, TestRemoveCorrectFrame) {
  vm.TurnMarkerOn(true);    // 0 - marked
  vm.NextFrame();           // 1 - marked
  vm.UnmarkCurrentFrame();  // 1 unmarked
  vm.PreviousFrame();       // 0
  ASSERT_EQ(1, vm.GetMarkedFrames().size());
  EXPECT_EQ(0, vm.GetMarkedFrames()[0]);
}
