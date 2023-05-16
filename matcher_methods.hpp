#ifndef MATCHER_H
#define MATCHER_H

#include <opencv2/core.hpp>
#include "utils.h"

/*
    non passo tramite puntatore img1, img2 e res perché richiamo più funzioni in task1.cpp
    e c'è il rischio di applicare modifiche alle immagini (conversioni ad CV_8U ecc)
*/

// functioning methods
void bruteForceHamming(cv::Mat img1, cv::Mat img2, Result res);
void bruteForceHammingSorted(cv::Mat img1, cv::Mat img2, Result res);

// non functioning ones
void bruteForceKNN(cv::Mat img1, cv::Mat img2, Result res, int flag);
void flannMatching(cv::Mat img1, cv::Mat img2, Result res, int flag);

#endif // MATCHER_H