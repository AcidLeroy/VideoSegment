#include "segmenter_interface.h"
#include <gtest/gtest.h>
#include <vector>
class MethodAccuracy {
 public:
  explicit MethodAccuracy(const std::vector<Segment> &gnd_truth,
                          const std::vector<Segment> &predicted) {
    gnd = gnd_truth;
    pred = predicted;
  }
  unsigned int GetFalsePositives() {
    for (int i = 0; i < gnd.size(); ++i) {
    }
    return 1;
  }

 private:
  std::vector<Segment> gnd, pred;
};

TEST(MethodAccuracy, TestOneFalsePositive) {
  Segment s = {0, 0};
  std::vector<Segment> gnd_truth, predicted;
  gnd_truth.push_back(s);
  predicted.push_back(s);
  MethodAccuracy m = MethodAccuracy(gnd_truth, predicted);
  ASSERT_EQ(0, m.GetFalsePositives());
}
