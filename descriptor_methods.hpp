#ifndef METHODS_H
#define METHODS_H

#include <opencv2/core.hpp>
#include "utils.h"

Result useSURF(cv::Mat &img1, cv::Mat &img2);
Result useSIFT(cv::Mat &img1, cv::Mat &img2);
Result useORB(cv::Mat &img1, cv::Mat &img2);
void internalProcedure(cv::Mat &img1, cv::Mat &img2, Result &res, cv::Ptr<cv::Feature2D> det);

#endif // METHODS_H