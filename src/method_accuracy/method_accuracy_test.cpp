
#include "method_accuracy.h"
#include <gtest/gtest.h>

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
