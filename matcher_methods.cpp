#include <array>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include "utils.h"

void bruteForceKNN(cv::Mat &img1, cv::Mat &img2, Result &res, int flag)
{
    cv::BFMatcher bf;
    std::vector<std::vector<cv::DMatch>> matches;
    bf.knnMatch(res.descriptor1, res.descriptor2, matches, 2);

    std::vector<cv::DMatch> good;
    for (const auto &match : matches)
    {
        if (match[0].distance < 0.75 * match[1].distance)
        {
            good.push_back(match[0]);
        }
    }

    cv::Mat imgMatches;
    cv::drawMatches(img1, res.kp1, img2, res.kp2, good, imgMatches);

    if (flag == 0)
        cv::imshow("KNN - Matching - SURF", imgMatches);
    if (flag == 1)
        cv::imshow("KNN - Matching - SIFT", imgMatches);

    cv::waitKey();
}

void bruteForceHamming(cv::Mat &img1, cv::Mat &img2, Result &res, int flag)
{
    cv::BFMatcher matcher(cv::NORM_L2);
    std::vector<cv::DMatch> matches;
    matcher.match(res.descriptor1, res.descriptor2, matches);

    cv::Mat imgMatches;
    cv::drawMatches(img1, res.kp1, img2, res.kp2, matches, imgMatches);

    if (flag == 0)
        cv::imshow("Hamming - Matching - SURF", imgMatches);
    if (flag == 1)
        cv::imshow("Hamming - Matching - SIFT", imgMatches);

    cv::waitKey();
}

void flannMatching(cv::Mat &img1, cv::Mat &img2, Result &res, int flag)
{
    // FLANN parameters
    int FLANN_INDEX_KDTREE = 1;
    cv::FlannBasedMatcher flann(cv::makePtr<cv::flann::KDTreeIndexParams>(5), cv::makePtr<cv::flann::SearchParams>(50));

    // Performs k-NN
    std::vector<std::vector<cv::DMatch>> matches;
    flann.knnMatch(res.descriptor1, res.descriptor2, matches, 2);

    // Draws only good matches, so create a mask
    std::vector<char> matchesMask(matches.size(), 0);

    for (size_t i = 0; i < matches.size(); i++)
    {
        if (matches[i][0].distance < 0.7 * matches[i][1].distance)
        {
            matchesMask[i] = 1;
        }
    }

    cv::Mat imgMatches;
    cv::drawMatches(img1, res.kp1, img2, res.kp2, matches, imgMatches);

    if (flag == 0)
        cv::imshow("FLANN - Matching - SURF", imgMatches);
    if (flag == 1)
        cv::imshow("FLANN - Matching - SIFT", imgMatches);

    cv::waitKey();
}