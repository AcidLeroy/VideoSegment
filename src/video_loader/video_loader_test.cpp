#include <gtest/gtest.h>
#include <vector>

class VideoLoader {};

class VideoLoaderTest : public ::testing::Test {
 protected:
  VideoLoader vl;
};

TEST_F(VideoLoaderTest, TestCorrectSize) {
  using namespace std;
  double buff_size_mb = 8;
  // vector<vector<double>> mat = vl.LoadVideo();
}
