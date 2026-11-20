#include <opencv2/opencv.hpp>
#include "tit.hpp"

bool titd::feed(const cv::Mat& frame)
{
    auto grayscale = cv::Mat{};
    cv::cvtColor(frame, grayscale, cv::COLOR_BGR2GRAY);
    auto grayscale_cropped = grayscale(roi_);

    if (!got_frame_)
    {
        got_frame_ = true;
        prev_frame_ = grayscale_cropped;
        return false;
    }

    auto delta = cv::Mat{};
    cv::absdiff(grayscale_cropped, prev_frame_, delta);
    cv::threshold(delta, delta, movm_threshold_, 255.0, cv::THRESH_BINARY);
    
    auto kern = cv::getStructuringElement(cv::MORPH_RECT, cv::Size{5, 5});
    cv::morphologyEx(delta, delta, cv::MORPH_OPEN, kern);
    cv::morphologyEx(delta, delta, cv::MORPH_CLOSE, kern);

    const double area = roi_.area();
    const double white_ratio = cv::countNonZero(delta) / area;
    const bool ret = white_ratio >= area_threshold_;

    prev_frame_ = grayscale_cropped;
    return ret;
}
