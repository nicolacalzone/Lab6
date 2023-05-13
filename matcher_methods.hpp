#ifndef MATCHER_H
#define MATCHER_H

#include <opencv2/core.hpp>
#include "utils.h"

void bruteForceHamming(cv::Mat &img1, cv::Mat &img2, Result &res, int flag);
void bruteForceKNN(cv::Mat &img1, cv::Mat &img2, Result &res, int flag);
void flannMatching(cv::Mat &img1, cv::Mat &img2, Result &res, int flag);

#endif // MATCHER_H