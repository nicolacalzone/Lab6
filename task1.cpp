#include <iostream>
#include <chrono>
#include <cmath>
#include <array>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>

#include "utils.h"
#include "descriptor_methods.hpp"
#include "matcher_methods.hpp"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
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
    }

    img1 = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    img2 = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);

    Result resSURF, resSIFT;

    resSURF = useSURF(img1, img2);
    resSIFT = useSIFT(img1, img2);

    bruteForceHamming(img1, img2, resSURF, 0);
    bruteForceHamming(img1, img2, resSIFT, 1);

    bruteForceKNN(img1, img2, resSURF, 0);
    bruteForceKNN(img1, img2, resSIFT, 1);

    flannMatching(img1, img2, resSIFT, 0);
    flannMatching(img1, img2, resSIFT, 1);

    return 0;
}
