/*
 * main.hpp
 *
 *  Created on: Mar 18, 2014
 *      Author: svdrv
 */

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "functions.hpp"
#include "db_utils.hpp"
#include "myFeatures.h"
#include <algorithm>
#include <string>

using namespace std;
using namespace cv;

void calculateFeatures(Mat &trainingData, Mat &labels);

void trainDTree();

void predict(String test_url,
             String map_url,
             int test_resize,
             String result_url,
             String confusion_url,
             float &accuracy,
             float &perc_capelli_riconosciuti,
             float &perc_sfondo_riconosciuto);

void saveSVM(CvSVM &SVM,
             int index,
             String dir);

void fillVector(vector<String> &vector_test,
                vector<String> &vector_map,
                vector<String> &vector_result,
                vector<String> &vector_confusion,
                int &num_train,
                int &num_test);

void printUsage();

#define NUM_HOG 5
#define NUM_GABOR 2
#define BACKGROUND -1.0
#define FOREGROUND +1.0
#define RESIZE 512
#define BACKGROUND_PERC 50

#endif /* MAIN_HPP_ */
