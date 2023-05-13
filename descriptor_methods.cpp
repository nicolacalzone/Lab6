#include <array>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include "utils.h"

Result useSURF(cv::Mat &img1, cv::Mat &img2)
{
    cv::Ptr<cv::xfeatures2d::SURF> det = cv::xfeatures2d::SURF::create();
    std::vector<cv::KeyPoint> kp1, kp2;
    cv::Mat descriptor1, descriptor2;
    det->detectAndCompute(img1, cv::noArray(), kp1, descriptor1);
    det->detectAndCompute(img1, cv::noArray(), kp2, descriptor2);

    Result res;
    res.descriptor1 = descriptor1;
    res.descriptor2 = descriptor2;
    res.kp1 = kp1;
    res.kp2 = kp2;

    return res;
}

Result useSIFT(cv::Mat &img1, cv::Mat &img2)
{
    cv::Ptr<cv::SIFT> det = cv::SIFT::create();
    std::vector<cv::KeyPoint> kp1, kp2;
    cv::Mat descriptor1, descriptor2;
    det->detectAndCompute(img1, cv::noArray(), kp1, descriptor1);
    det->detectAndCompute(img1, cv::noArray(), kp2, descriptor2);

    Result res;
    res.descriptor1 = descriptor1;
    res.descriptor2 = descriptor2;
    res.kp1 = kp1;
    res.kp2 = kp2;

    return res;
}