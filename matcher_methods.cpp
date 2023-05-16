#include <array>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include "utils.h"

void bruteForceHamming(cv::Mat img1, cv::Mat img2, Result res)
{
    // Convert images to 8-bit unsigned integer type
    img1.convertTo(img1, CV_8U);
    img2.convertTo(img2, CV_8U);

    cv::BFMatcher matcher(cv::NORM_L2);
    std::vector<cv::DMatch> matches;
    matcher.match(res.descriptor1, res.descriptor2, matches);

    cv::Mat imgMatches;
    cv::drawMatches(img1, res.kp1, img2, res.kp2, matches, imgMatches);

    cv::imshow("Hamming - ORB", imgMatches);
    cv::imwrite("../ResultImages/Hamming - ORB.png", imgMatches);

    cv::waitKey();
}

void bruteForceHammingSorted(cv::Mat img1, cv::Mat img2, Result res)
{
    // Convert images to 8-bit unsigned integer type
    if (!img1.empty() && img1.type() != CV_8U)
        img1.convertTo(img1, CV_8U);
    if (!img2.empty() && img2.type() != CV_8U)
        img2.convertTo(img2, CV_8U);
    img2.convertTo(img2, CV_8U);

    // Check and convert descriptors to 8-bit unsigned integer type
    if (res.descriptor1.type() != CV_8U)
        res.descriptor1.convertTo(res.descriptor1, CV_8U);
    if (res.descriptor2.type() != CV_8U)
        res.descriptor2.convertTo(res.descriptor2, CV_8U);

    cv::BFMatcher bf(cv::NORM_HAMMING, true);

    std::vector<cv::DMatch> matches;
    bf.match(res.descriptor1, res.descriptor2, matches);

    std::sort(matches.begin(), matches.end());

    cv::Mat imgMatches;
    cv::drawMatches(img1, res.kp1, img2, res.kp2, matches, imgMatches);

    cv::imshow("Hamming - ORB Sorted", imgMatches);
    cv::imwrite("../ResultImages/Hamming - ORB Sorted.png", imgMatches);

    cv::waitKey();
}

void bruteForceKNN(cv::Mat img1, cv::Mat img2, Result res, int flag)
{
    // Convert images to 8-bit unsigned integer type
    img1.convertTo(img1, CV_8U);
    img2.convertTo(img2, CV_8U);

    cv::BFMatcher bf;
    std::vector<std::vector<cv::DMatch>> matches;
    bf.knnMatch(res.descriptor1, res.descriptor2, matches, 2);

    std::vector<cv::DMatch> goodMatches;
    for (const auto &match : matches)
    {
        if (match[0].distance < 0.6 * match[1].distance)
        {
            goodMatches.push_back(match[0]);
        }
    }

    cv::Mat imgMatches;
    cv::drawMatches(img1, res.kp1, img2, res.kp2, goodMatches, imgMatches);

    if (flag == 0)
        cv::imshow("KNN - Matching - SURF", imgMatches);
    cv::imwrite("../ResultImages/KNN - Matching - SURF.png", imgMatches);

    if (flag == 1)
        cv::imshow("KNN - Matching - SIFT", imgMatches);
    cv::imwrite("../ResultImages/KNN - Matching - SIFT.png", imgMatches);

    cv::waitKey();
}

/*
 ***********************************
 *
 *   Non - functioning    FLANN (KNN)
 *   Both with SURF and SIFT descriptors-keypoints in input (passed with Result res variable)
 *
 ***********************************
 */
void flannMatching(cv::Mat img1, cv::Mat img2, Result res, int flag)
{

    // Convert images to 8-bit unsigned integer type
    img1.convertTo(img1, CV_8U);
    img2.convertTo(img2, CV_8U);

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
        if (matches[i][0].distance < 0.6 * matches[i][1].distance)
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
