#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/features2d.hpp>
#include "methods.h"
#include <chrono>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{

    std::cout << "OpenCV version: " << CV_VERSION << std::endl;

    /* cv::CommandLineParser parser(argc, argv, keys);

    cv::Mat img1 = cv::imread(samples::findFile(parser.get<cv::String>("input1")), cv::IMREAD_GRAYSCALE);
    cv::Mat img2 = cv::imread(samples::findFile(parser.get<cv::String>("input2")), cv::IMREAD_GRAYSCALE);

    if (img1.empty() || img2.empty())
    {
        cout << "Could not open or find the image!\n"
             << endl;
        parser.printMessage();
        return -1;
    }

    */

    cv::Mat img1, img2;

    if (argc == 1)
    {
        cout << "\nNo images passed as arguments.";
        return -1;
    }

    if (argc == 2)
    {
        cout << "\nOnly program name and 1 image were passed as arguments.";
        return -1;
    }

    if (argc >= 3)
    {
        cout << "\nArguments passed correctly:" << endl;
        for (int i = 0; i < argc; i++)
            cout << "argv[" << i << "]: " << argv[i] << endl;

        img1 = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
        img2 = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);
    }

    // METHOD 1
    BruteForceMethod(img1, img2);

    // METHOD 2
    auto start_time = std::chrono::high_resolution_clock::now();
    SURFmethod(img1, img2);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "SURF computation time: " << duration.count() << "ms" << std::endl;

    // METHOD 3
    start_time = std::chrono::high_resolution_clock::now();
    SIFTmethod(img1, img2);
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "SIFT computation time: " << duration.count() << "ms" << std::endl;

    return 0;
}

void BruteForceMethod(cv::Mat img1, cv::Mat img2)
{
}

void SURFmethod(cv::Mat img1, cv::Mat img2)
{
    cv::Ptr<cv::xfeatures2d::SURF> det = cv::xfeatures2d::SURF::create();
    // Detect features in the image
    std::vector<cv::KeyPoint> keypoints;
    det->detect(img1, keypoints);

    // Draw the detected features
    cv::Mat img_keypoints;
    cv::drawKeypoints(img1, keypoints, img_keypoints);

    // Display the result
    cv::imshow("Features", img_keypoints);
    cv::waitKey(0);
}

void SIFTmethod(cv::Mat img1, cv::Mat img2)
{
    // Create a SIFT feature detector
    cv::Ptr<cv::SIFT> det = cv::SIFT::create();

    // Detect and compute features in the image
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    det->detectAndCompute(img1, cv::noArray(), keypoints, descriptors);

    // Draw the detected features
    cv::Mat img_keypoints;
    cv::drawKeypoints(img1, keypoints, img_keypoints);

    // Display the result
    cv::imshow("Features", img_keypoints);
    cv::waitKey(0);
}
