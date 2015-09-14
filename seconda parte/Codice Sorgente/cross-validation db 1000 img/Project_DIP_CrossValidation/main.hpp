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

void calculateFeatures(Mat &trainingData,
                       Mat &labels,
                       vector<vector<String> > &imgDb,
                       vector<vector<String> > &maskDb,
                       int binToAvoid);

void trainSvmPolynomial(CvSVM &SVM,
                        Mat trainingData,
                        Mat labels);

void trainDTree(CvDTree &dtree,
                Mat trainingData,
                Mat labels);

void predict(CvDTree &dtree,
             String test_url,
             String map_url,
             int test_resize,
             String result_url,
             String confusion_url,
             String result_url_con_post_processing,
             String confusion_url_con_post_processing,
             float &accuracy,
             float &perc_capelli_riconosciuti,
             float &perc_sfondo_riconosciuto,
             float &accuracyConPostProcessing,
             float &perc_capelli_riconosciutiConPostProcessing,
             float &perc_sfondo_riconosciutoConPostProcessing);


void fillVector(vector<vector<String> > &img_db,
                vector<vector<String> > &mask_db,
                vector<vector<String> > &vector_result,
                vector<vector<String> > &vector_confusion,
                vector<vector<String> > &vector_result_con_post_processing,
                vector<vector<String> > &vector_confusion_con_post_processing,
                int num_img, int num_bin);


#define NUM_HOG 5
#define NUM_GABOR 16
#define NUM_GABOR_2 2
#define NUM_LBP 8
#define BACKGROUND -1.0
#define FOREGROUND +1.0
#define RESIZE 4096
#define BACKGROUND_PERC 50
#define HOG_CELL_SIZE 8

#endif /* MAIN_HPP_ */
