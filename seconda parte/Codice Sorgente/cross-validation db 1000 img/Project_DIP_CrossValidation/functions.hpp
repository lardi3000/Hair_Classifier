/*
 * functions.hpp
 *
 *  Created on: Mar 18, 2014
 *      Author: svdrv
 */

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_


#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include "myFeatures.h"

using namespace std;
using namespace cv;

void clearMat(Mat image);
Mat myResize(Mat src,int max_dim);
void makeMatSizeDivisible(Mat &src,Mat &dst,int div);

void findMinMax(vector<vector<vector<float> > > &vectorToFind, float &min, float &max);
void findMinMax(vector<vector<vector<vector<float> > > > &vectorToFind, float &min, float &max);
void normalizeVector(vector<vector<vector<float> > > &vectorToNormalize, float oldMin, float oldMax, float newMin, float newMax);
void normalizeVector(vector<vector<float> > &vectorToNormalize, float oldMin, float oldMax, float newMin, float newMax);

void postProcessing(Mat &imgToProcess,
                    Mat &imgOriginal,
                    int cellWidth);

void calculateAccuracy(Mat &resultMat,
                       Mat &confusionMat,
                       Mat &map,
                       float &accuracy,
                       float &perc_capelli_riconosciuti,
                       float &perc_sfondo_riconosciuto,
                       int foreground,
                       int background,
                       int cellWidth);

#endif /* FUNCTIONS_HPP_ */
