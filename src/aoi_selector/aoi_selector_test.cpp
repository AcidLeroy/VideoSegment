#include "gtest/gtest.h"
#include <opencv2/opencv.hpp>

template <typename T>
class AoiSelector {
 public:
  void SetXY(T x, T y) {
    aoi_.x = x;
    aoi_.y = y;
  }

  void SetSize(T width, T height) {
    aoi_.width = width;
    aoi_.height = height;
  }

  cv::Rect_<T> aoi() { return aoi_; }

 private:
  cv::Rect_<T> aoi_{};
};

class AoiSelectorTest : public ::testing::Test {
 protected:
  AoiSelector<double> as{};
  const double x{10.0};
  const double y{11.0};
  const double width{12.0};
  const double height{13.0};
  const cv::Rect_<double> truth{x, y, width, height};
};

TEST_F(AoiSelectorTest, SetXY) {
  cv::Rect_<double> xy_truth{x, y, 0.0, 0.0};
  as.SetXY(x, y);
  auto my_aoi = as.aoi();
  ASSERT_EQ(xy_truth, my_aoi);
}

TEST_F(AoiSelectorTest, SetSize) {
  cv::Rect_<double> size_truth{0.0, 0.0, width, height};
  as.SetSize(width, height);
  auto my_aoi = as.aoi();
  ASSERT_EQ(size_truth, my_aoi);
}
