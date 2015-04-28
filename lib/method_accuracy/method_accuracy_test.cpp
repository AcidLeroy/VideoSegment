#include "segmenter_interface.h"
#include <gtest/gtest.h>
#include <vector>
#include <iterator>

class MethodAccuracy {
 public:
  template <typename T>
  static size_t NumFalsePositives(const std::vector<T> &gnd_truth,
                                  const std::vector<T> &predicted,
                                  size_t length) {
    size_t count = 0;
    for (auto &pred : predicted) {
      auto it = find(gnd_truth.begin(), gnd_truth.end(), pred);
      if (it == gnd_truth.end()) {
        count++;
      }
    }
    return count;
  }

  template <typename T>
  static size_t NumTrueNegatives(const std::vector<T> &gnd_truth,
                                 const std::vector<T> &predicted,
                                 size_t length) {
    size_t fp = NumFalsePositives(gnd_truth, predicted, length);
    size_t fn = NumFalseNegatives(gnd_truth, predicted, length);
    size_t tp = NumTruePositives(gnd_truth, predicted, length);
    return length - (fp + fn + tp);
  }

  template <typename T>
  static size_t NumFalseNegatives(const std::vector<T> &gnd_truth,
                                  const std::vector<T> &predicted,
                                  size_t length) {
    return NumFalsePositives(predicted, gnd_truth, length);
  }
  template <typename T>
  static size_t NumTruePositives(const std::vector<T> &gnd_truth,
                                 const std::vector<T> &predicted,
                                 size_t length) {
    size_t count = 0;
    for (auto &pred : predicted) {
      auto it = find(gnd_truth.begin(), gnd_truth.end(), pred);
      if (it != gnd_truth.end()) {
        count++;
      }
    }
    return count;
  }
};

class TestMethodAccuracy : public ::testing::Test {
 protected:
  void SetUp() {
    size_t truth[5] = {0, 1, 2, 10, 50};
    size_t pred[3] = {1, 11, 100};
    gnd_truth.assign(truth, truth + 5);
    predicted.assign(pred, pred + 3);
  }
  void TearDown() {}
  MethodAccuracy ma;
  std::vector<size_t> gnd_truth, predicted;
  size_t length = 100;
};

TEST_F(TestMethodAccuracy, NumFalsePositives) {
  EXPECT_EQ(2, ma.NumFalsePositives<size_t>(gnd_truth, predicted, length));
}

TEST_F(TestMethodAccuracy, NumTrueNegatives) {
  EXPECT_EQ(93, ma.NumTrueNegatives<size_t>(gnd_truth, predicted, length));
}

TEST_F(TestMethodAccuracy, NumFalseNegatives) {
  EXPECT_EQ(4, ma.NumFalseNegatives<size_t>(gnd_truth, predicted, length));
}

TEST_F(TestMethodAccuracy, NumTruePostives) {
  EXPECT_EQ(1, ma.NumTruePositives<size_t>(gnd_truth, predicted, length));
}
