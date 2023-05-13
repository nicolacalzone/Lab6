#ifndef METHODS_H
#define METHODS_H

#include <opencv2/core.hpp>
#include "utils.h"

Result useSURF(cv::Mat &img1, cv::Mat &img2);
Result useSIFT(cv::Mat &img1, cv::Mat &img2);

#endif // METHODS_H