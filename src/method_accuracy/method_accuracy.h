#ifndef LIB_METHOD_ACCURACY_METHOD_ACCURACY_H_
#define LIB_METHOD_ACCURACY_METHOD_ACCURACY_H_
#include <iterator>
#include <vector>
#include "segmenter_interface.h"

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

#endif /* LIB_METHOD_ACCURACY_METHOD_ACCURACY_H_ */
