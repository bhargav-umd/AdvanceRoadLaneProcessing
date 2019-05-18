#include "./LaneDetector.hpp"

/**
 * @brief      Class for lane predictor.
 */
class LanePredictor : public LaneDetector {
private:
  std::string lane_indicator;
  cv::Mat inputImageP;
  // std::vector<cv::Vec4i> lines_p;
  cv::Mat frameP;
  std::string turn_predict; // variable stores the lane turn prediction
                            // cv::Vec4d yellow_lanes;
                            // cv::Vec4d white_lanes;
                            // double slope_thresh = 0.7;
                            // std::vector<double> slopes;
                            // std::vector<cv::Vec4i> selected_lines;

public:
  // LanePredictor(); // default constructor
  // ~LanePredictor(); // default destructor

  /**
   * @brief      { to threshold the image to get only yellow lanes}
   *
   * @param[in]  frameP  The frame of the video
   *
   * @return     { thresholded image }
   */
  cv::Mat hsvThresholdY(cv::Mat frameP);

  /**
   * @brief      { It finds the yellow lane }
   *
   * @param[in]    { thresholded image }
   *
   * @return     { end points of the yellow lines  }
   */
  cv::Vec4d detectYellow(cv::Mat);

  /**
    * @brief      { to plot a polygon over detected lanes  }
   *
   * @param[in]  { image to plot lanes}
   * @param[in]  { left lanes }
   * @param[in]  { right lanes }
   *
   * @return     {Image with polygon plot }
   */
  cv::Mat plotPolygon(cv::Mat, cv::Vec4d, cv::Vec4d);

  /**
   * @brief      {predict if vehicle is on wrong lane }
   *
   * @param[in]  { yellow lane end points}
   *
   * @return     {string indicating the lane}
   */
  std::string wrongLanePredictor(cv::Vec4d);

  /**
   * @brief      {function which calculates vanishing points
   *               and predicts turn  }
   *
   * @param[in]  { left lanes end points}
   * @param[in]  { right lane end points }
   * @param[in]  { Output Image }
   *
   * @return     {Output Image with predicted turns text }
   */
  std::string predictTurn(cv::Vec4d, cv::Vec4d, cv::Mat);
};
