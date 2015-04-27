#include "segmenter_interface.h"
#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include <memory>
class MethodAccuracy {
 public:
  explicit MethodAccuracy(const std::vector<Segment> &gnd_truth,
                          const std::vector<Segment> &predicted) {
    gnd = gnd_truth;
    pred = predicted;
  }

  bool SegmentsIntersect(Segment a, Segment b) {
    if (a.begin >= b.begin && a.begin <= b.end) {
      return true;
    }
    if (b.begin >= a.begin && b.begin <= a.end) {
      return true;
    }

    return false;
  }

  size_t FalsePositives(Segment gnd_truth, Segment predicted) {
    if (!SegmentsIntersect(gnd_truth, predicted)) {
      return (predicted.end - predicted.begin + 1);
    }

    size_t count = 0;
    if (predicted.begin < gnd_truth.begin) {
      count += gnd_truth.begin - predicted.begin;
    }

    if (predicted.end > gnd_truth.end) {
      count += predicted.end - gnd_truth.end;
    }
    return count;
  }

  size_t NumIntersections() {
    size_t count = 0;
    for (size_t i = 0; i < pred.size(); ++i) {
      for (size_t j = 0; j < gnd.size(); ++j) {
        if (SegmentsIntersect(gnd[j], pred[i])) {
          count++;
        }
      }
    }
    return count;
  }

  size_t NumFalsePositives() {
    for (size_t i = 0; i < pred.size(); ++i) {
    }
    return 1;
  }

 private:
  std::vector<Segment> gnd, pred;
};

class TestMethodAccuracy : public ::testing::Test {
 protected:
  void SetUp() {
    Segment s[3] = {{1, 7}, {2, 6}, {8, 11}};
    gnd_truth.push_back(s[0]);
    predicted.push_back(s[1]);
    predicted.push_back(s[2]);
    m.reset(new MethodAccuracy(gnd_truth, predicted));
  }
  void TearDown() {}
  std::vector<Segment> gnd_truth, predicted;
  std::unique_ptr<MethodAccuracy> m;
//  static constexpr Segment gnd[3] = {{1, 3}, {5, 5}, {10, 15}};
//  static constexpr Segment pred[3] = {{2, 2}, {6, 7}, {9, 16}};
};

TEST_F(TestMethodAccuracy, TestFalsPositives) {
//  EXPECT_EQ(0, m->FalsePositives(gnd[0], pred[0]));
//  EXPECT_EQ(2, m->FalsePositives(gnd[1], pred[1]));
//  EXPECT_EQ(2, m->FalsePositives(gnd[2], pred[2]));
}

TEST_F(TestMethodAccuracy, TestNumberIntersections) {
  EXPECT_EQ(1, m->NumIntersections());
}

TEST_F(TestMethodAccuracy, TestSegmentsIntersect) {
  Segment a = {1, 3};
  Segment b = {2, 2};
  EXPECT_TRUE(m->SegmentsIntersect(a, b));
  EXPECT_TRUE(m->SegmentsIntersect(b, a));

  Segment c = {1, 3};
  Segment d = {2, 5};
  EXPECT_TRUE(m->SegmentsIntersect(c, d));
  EXPECT_TRUE(m->SegmentsIntersect(d, c));

  Segment e = {1, 3};
  Segment f = {3, 3};
  EXPECT_TRUE(m->SegmentsIntersect(e, f));
  EXPECT_TRUE(m->SegmentsIntersect(f, e));
}

TEST_F(TestMethodAccuracy, TestSegmentsDontIntersect) {
  Segment a = {1, 3};
  Segment b = {4, 5};
  EXPECT_FALSE(m->SegmentsIntersect(a, b));
  EXPECT_FALSE(m->SegmentsIntersect(b, a));

  Segment c = {1, 3};
  Segment d = {5, 5};
  EXPECT_FALSE(m->SegmentsIntersect(c, d));
  EXPECT_FALSE(m->SegmentsIntersect(d, c));
}

TEST_F(TestMethodAccuracy, TestNumFalsePositives) {
  ASSERT_EQ(3, m->NumFalsePositives());
}
