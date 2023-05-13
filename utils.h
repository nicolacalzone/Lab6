#ifndef UTILS_H
#define UTILS_H

#include <opencv2/core.hpp>

struct Result
{
    std::vector<cv::KeyPoint> kp1, kp2;
    cv::Mat descriptor1, descriptor2;
};

#endif