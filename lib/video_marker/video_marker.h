/*
 * video_marker.h
 *
 *  Created on: Apr 17, 2015
 *      Author: cody
 */

#ifndef SRC_CPP_VIDEO_MARKER_H_
#define SRC_CPP_VIDEO_MARKER_H_
#include "segmenter_interface.h"
#include <algorithm>
#include <iterator>
#include <vector>

class VideoMarker {
 public:
  VideoMarker();
  int GetCurrentFrame() const;
  void NextFrame();
  void PreviousFrame();
  bool IsFrameMarked(int f);

  void MarkCurrentFrame();
  void TurnMarkerOn(bool on);

  void RemoveLastMarkedFrame();
  std::vector<int> GetMarkedFrames();

  std::vector<Segment> GetSegments();

  void SortMarkedFrames();

  void UnmarkCurrentFrame();

  Segment GetSegment(int start, int end);

 private:
  int current_frame_;
  std::vector<int> marked_frames_;
  bool marker_on_;
};

#endif /* SRC_CPP_VIDEO_MARKER_H_ */
