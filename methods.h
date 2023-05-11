#ifndef METHODS_H
#define METHODS_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/features2d.hpp>

void BruteForceMethod(cv::Mat img1, cv::Mat img2);
void SURFmethod(cv::Mat img1, cv::Mat img2);
void SIFTmethod(cv::Mat img1, cv::Mat img2);

#endif