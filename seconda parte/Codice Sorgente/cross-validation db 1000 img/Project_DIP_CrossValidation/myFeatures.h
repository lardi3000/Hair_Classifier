#ifndef FEATURES_H
#define FEATURES_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "functions.hpp"

using namespace cv;
using namespace std;

void getGabor2(const Mat &src,
               vector<vector<float> > &local_energy,
               vector<vector<float> > &mean_amplitude,
               unsigned int kernel_size);

void getHog2(Mat &image,
            vector<vector<vector<float> > > &descrittoriNormalizzati,
            int _cellWidth, int _numBin);


#endif // FEATURES_H
