#pragma once

#include <opencv2/core.hpp>

class titd {
public:
    titd(double movm_threshold, double area_threshold, cv::Rect roi)
        : movm_threshold_(movm_threshold), area_threshold_(area_threshold),
        roi_(roi)
    {
    }

    bool feed(const cv::Mat& frame);
private:
    const double movm_threshold_;
    const double area_threshold_;
    const cv::Rect roi_;

    bool got_frame_ = false;
    cv::Mat prev_frame_ = {};
};
