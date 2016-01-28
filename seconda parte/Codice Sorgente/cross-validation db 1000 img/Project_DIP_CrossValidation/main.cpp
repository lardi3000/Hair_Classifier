#include "main.hpp"

//int NUM_FEATURES = 1 + NUM_HOG + NUM_GABOR + NUM_LBP;
int NUM_FEATURES = NUM_HOG + NUM_GABOR_2;

//Parametri per hog
int cellWidth = 31;
int numBin = NUM_HOG;

//Variabili utili per la normalizzazione delle features
float min_local_energy;
float max_local_energy;
float min_mean_amplitude;
float max_mean_amplitude;
float new_min;
float new_max;

int main(int argc, char ** argv){

    cout << "Inizio programma." << endl;

    ofstream file_out("../out");

    //Inizializzo le variabili per la cross-validation
    int numImg = 1000;
    int numBin = 10;
    float accuracy = 0.0;
    float percCapelliRiconosciuti = 0.0;
    float percSfondoRiconosciuto = 0.0;
    float accuracyConPostProcessing = 0.0;
    float percCapelliRiconosciutiConPostProcessing = 0.0;
    float percSfondoRiconosciutoConPostProcessing = 0.0;
    double tempoFeaturesComplessivo = 0.0;
    double tempoTrainingComplessivo = 0.0;
    double tempoTestComplessivo = 0.0;

    //Salvo i nomi delle immagini da utilizzare
    vector<vector<String> > imgDb, maskDb, vectorResult, vectorConfusion, vectorResultConPostProcessing, vectorConfusionConPostProcessing;
    fillVector(imgDb, maskDb, vectorResult, vectorConfusion, vectorResultConPostProcessing, vectorConfusionConPostProcessing, numImg, numBin);

    //Itero lungo tutti i bin
    for(unsigned int binToTest=0; binToTest<numBin; binToTest++){

        cout << endl << endl << "Begin of the computation of the features for the bin " << binToTest+1 << " of " << numBin << "." << endl;
        file_out << endl << endl << "Begin of the computation of the bin " << binToTest+1 << " of " << numBin << "." << endl;

        double tempo_features = (double) getTickCount();

        //Calcolo le features
        Mat trainingData, labels;
        calculateFeatures(trainingData,
                          labels,
                          imgDb,
                          maskDb,
                          binToTest);

        tempo_features = ((double)getTickCount() - tempo_features)/getTickFrequency();

        cout << "Ended the calculation of the features of the training set." << endl;
        cout << "Time for computing the features: " << tempo_features << " s." << endl << endl;

        cout << "Begin of the training of the decision tree." << endl;

        double tempo_training = (double) getTickCount();

        //Addestro la decision tree
        CvDTree dtree;
        trainDTree(dtree, trainingData, labels);

        tempo_training = ((double)getTickCount() - tempo_training)/getTickFrequency();

        cout << "End of the training of the decision tree." << endl;
        cout << "Time for training the decision tree: " << tempo_training << " s." << endl << endl;
        cout << "Begin of the testing phase." << endl;

        double tempo_test = (double) getTickCount();

        int resizeToTest = RESIZE;
        float accuracyTmp;
        float accuracyBin = 0.0;
        float percCapelliRiconosciutiTmp;
        float percCapelliRiconosciutiBin = 0.0;
        float percSfondoRiconosciutoTmp;
        float percSfondoRiconosciutoBin = 0.0;

        float accuracyTmpConPostProcessing;
        float accuracyBinConPostProcessing = 0.0;
        float percCapelliRiconosciutiTmpConPostProcessing;
        float percCapelliRiconosciutiBinConPostProcessing = 0.0;
        float percSfondoRiconosciutoTmpConPostProcessing;
        float percSfondoRiconosciutoBinConPostProcessing = 0.0;

        int numero_immagini_elaborate = 0;

        for(unsigned int i=0; i<imgDb[binToTest].size(); i++){

            double tempo_test_tmp = (double) getTickCount();

            predict(dtree,
                    imgDb[binToTest][i],
                    maskDb[binToTest][i],
                    resizeToTest,
                    vectorResult[binToTest][i],
                    vectorConfusion[binToTest][i],
                    vectorResultConPostProcessing[binToTest][i],
                    vectorConfusionConPostProcessing[binToTest][i],
                    accuracyTmp,
                    percCapelliRiconosciutiTmp,
                    percSfondoRiconosciutoTmp,
                    accuracyTmpConPostProcessing,
                    percCapelliRiconosciutiTmpConPostProcessing,
                    percSfondoRiconosciutoTmpConPostProcessing);

            accuracyBin += accuracyTmp;
            percCapelliRiconosciutiBin += percCapelliRiconosciutiTmp;
            percSfondoRiconosciutoBin += percSfondoRiconosciutoTmp;
            accuracyBinConPostProcessing += accuracyTmpConPostProcessing;
            percCapelliRiconosciutiBinConPostProcessing += percCapelliRiconosciutiTmpConPostProcessing;
            percSfondoRiconosciutoBinConPostProcessing += percSfondoRiconosciutoTmpConPostProcessing;

            tempo_test_tmp = ((double)getTickCount() - tempo_test_tmp)/getTickFrequency();

            /*
                cout << "Computed image " << vector_result[i].substr(11, vector_result[i].length());
                cout << "   Accuracy: " << accuracyTmp << " % hair recognised: " << percCapelliRiconosciutiTmp;
                cout << " % background recognised: " << percSfondoRiconosciutoTmp << " % ";
                cout << "time: " << tempo_test_tmp << " s." << endl;
             */

            if(((++numero_immagini_elaborate)%(imgDb[binToTest].size()/10))==0)
                cout << "Tested " << numero_immagini_elaborate << " images of " << imgDb[binToTest].size()  << "." << endl;

        }

        //Aggiorno i va1ori di accuracy e percCapelli e sfondo
        accuracyBin = accuracyBin / numero_immagini_elaborate;
        percCapelliRiconosciutiBin = percCapelliRiconosciutiBin / numero_immagini_elaborate;
        percSfondoRiconosciutoBin = percSfondoRiconosciutoBin / numero_immagini_elaborate;
        accuracyBinConPostProcessing = accuracyBinConPostProcessing / numero_immagini_elaborate;
        percCapelliRiconosciutiBinConPostProcessing = percCapelliRiconosciutiBinConPostProcessing / numero_immagini_elaborate;
        percSfondoRiconosciutoBinConPostProcessing = percSfondoRiconosciutoBinConPostProcessing / numero_immagini_elaborate;

        tempo_test = ((double)getTickCount() - tempo_test)/getTickFrequency();

        //Aggiorno i valori complessivi del programma
        accuracy += accuracyBin;
        percCapelliRiconosciuti += percCapelliRiconosciutiBin;
        percSfondoRiconosciuto += percSfondoRiconosciutoBin;
        accuracyConPostProcessing += accuracyBinConPostProcessing;
        percCapelliRiconosciutiConPostProcessing += percCapelliRiconosciutiBinConPostProcessing;
        percSfondoRiconosciutoConPostProcessing += percSfondoRiconosciutoBinConPostProcessing;
        tempoFeaturesComplessivo += tempo_features;
        tempoTrainingComplessivo += tempo_training;
        tempoTestComplessivo += tempo_test;

        cout << endl << "Ended the test phase for the bin: " << binToTest+1 << "." << endl;
        cout << "Time for evaluating the features: " << tempo_features << " s." << endl;
        cout << "Time to train the decision tree: " << tempo_training << " s." << endl;
        cout << "Time for the test phase: " << tempo_test << " s." << endl;
        cout << "Average time for testing one image: " << tempo_test/(numImg/numBin) << " s." << endl;
        cout << "Accuracy: " << accuracyBin << " %" << endl;
        cout << "Percentage hair recognised: " << percCapelliRiconosciutiBin << " %" << endl;
        cout << "Percentage background recognised: " << percSfondoRiconosciutoBin << " %" << endl;
        cout << "Accuracy using post processing: " << accuracyBinConPostProcessing << " %" << endl;
        cout << "Percentage hair recognised using post processing: " << percCapelliRiconosciutiBinConPostProcessing << " %" << endl;
        cout << "Percentage background recognised using post processing: " << percSfondoRiconosciutoBinConPostProcessing << " %" << endl;

        file_out << endl << "Ended the test phase for the bin: " << binToTest+1 << "." << endl;
        file_out << "Time for evaluating the features: " << tempo_features << " s." << endl;
        file_out << "Time to train the decision tree: " << tempo_training << " s." << endl;
        file_out << "Time for the test phase: " << tempo_test << " s." << endl;
        file_out << "Average time for testing one image: " << tempo_test/(numImg/numBin) << " s." << endl;
        file_out << "Accuracy: " << accuracyBin << " %" << endl;
        file_out << "Percentage hair recognised: " << percCapelliRiconosciutiBin << " %" << endl;
        file_out << "Percentage background recognised: " << percSfondoRiconosciutoBin << " %" << endl;
        file_out << "Accuracy using post processing: " << accuracyBinConPostProcessing << " %" << endl;
        file_out << "Percentage hair recognised using post processing: " << percCapelliRiconosciutiBinConPostProcessing << " %" << endl;
        file_out << "Percentage background recognised using post processing: " << percSfondoRiconosciutoBinConPostProcessing << " %" << endl;

    }

    //Ultimo i valori accuracy e precisione di riconoscimento capelli-sfondo
    accuracy = accuracy / numBin;
    percCapelliRiconosciuti = percCapelliRiconosciuti / numBin;
    percSfondoRiconosciuto = percSfondoRiconosciuto / numBin;
    accuracyConPostProcessing = accuracyConPostProcessing / numBin;
    percCapelliRiconosciutiConPostProcessing = percCapelliRiconosciutiConPostProcessing / numBin;
    percSfondoRiconosciutoConPostProcessing = percSfondoRiconosciutoConPostProcessing / numBin;

    cout << endl << "Software ended." << endl;
    cout << "Time for computing the features: " << tempoFeaturesComplessivo << " s." << endl;
    cout << "Time for training the decision tree: " << tempoTrainingComplessivo << " s." << endl;
    cout << "Time for the testing phase: " << tempoTestComplessivo << " s." << endl;
    cout << "Average time for testing one image: " << tempoTestComplessivo/numImg << " s." << endl;
    cout << "Accuracy: " << accuracy << " %" << endl;
    cout << "Percentage hair recognised: " << percCapelliRiconosciuti << " %" << endl;
    cout << "Percentage background recognised: " << percSfondoRiconosciuto << " %" << endl;
    cout << "Accuracy using post processing: " << accuracyConPostProcessing << " %" << endl;
    cout << "Percentage hair recognised using post processing: " << percCapelliRiconosciutiConPostProcessing << " %" << endl;
    cout << "Percentage background recognised using post processing: " << percSfondoRiconosciutoConPostProcessing << " %" << endl;

    file_out << endl << "Software ended." << endl;
    file_out << "Time for computing the features: " << tempoFeaturesComplessivo << " s." << endl;
    file_out << "Time for training the decision tree: " << tempoTrainingComplessivo << " s." << endl;
    file_out << "Time for the testing phase: " << tempoTestComplessivo << " s." << endl;
    file_out << "Average time for testing one image: " << tempoTestComplessivo/numImg << " s." << endl;
    file_out << "Accuracy: " << accuracy << " %" << endl;
    file_out << "Percentage hair recognised: " << percCapelliRiconosciuti << " %" << endl;
    file_out << "Percentage background recognised: " << percSfondoRiconosciuto << " %" << endl;
    file_out << "Accuracy using post processing: " << accuracyConPostProcessing << " %" << endl;
    file_out << "Percentage hair recognised using post processing: " << percCapelliRiconosciutiConPostProcessing << " %" << endl;
    file_out << "Percentage background recognised using post processing: " << percSfondoRiconosciutoConPostProcessing << " %" << endl;

    file_out.close();

    return 0;

}

void trainDTree(CvDTree &dtree,
                Mat trainingData,
                Mat labels){

    // define the parameters for training the decision tree

    float *priors = NULL;  // weights of each classification for classes
    // (all equal as equal samples of each character)

    CvDTreeParams params = CvDTreeParams(25, // max depth
                                         5, // min sample count
                                         0, // regression accuracy: N/A here
                                         false, // compute surrogate split, no missing data
                                         15, // max number of categories (use sub-optimal algorithm for larger numbers)
                                         15, // the number of cross-validation folds
                                         false, // use 1SE rule => smaller tree
                                         false, // throw away the pruned tree branches
                                         priors // the array of priors
                                         );

    Mat var_type = Mat(NUM_FEATURES + 1, 1, CV_8U );
    var_type.setTo(Scalar(CV_VAR_NUMERICAL) ); // all inputs are numerical

    // this is a classification problem (i.e. predict a discrete number of class
    // outputs) so reset the last (+1) output var_type element to CV_VAR_CATEGORICAL

    var_type.at<uchar>(NUM_FEATURES, 0) = CV_VAR_CATEGORICAL;

    // train decision tree classifier (using training data)
    dtree.train(trainingData, CV_ROW_SAMPLE, labels,
                 Mat(), Mat(), var_type, Mat(), params);

}

void calculateFeatures(Mat &trainingData,
                       Mat &labels,
                       vector<vector<String> > &imgDb,
                       vector<vector<String> > &maskDb,
                       int binToAvoid){

    vector<float> labelsVector;
    vector<vector<float> > trainingDataVector;

    //In outputHOG c'è il vettore degli output di HOG
    vector<Mat> maps = vector<Mat>();
    vector<vector<vector<vector<float> > > > outputHOG = vector<vector<vector<vector<float> > > >();
    vector<vector<vector<float> > > localEnergy = vector<vector<vector<float> > >();
    vector<vector<vector<float> > > meanAmplitude = vector<vector<vector<float> > >();

    int numero_immagini_elaborate = 0;

    //Calcolo tutte le features
    for(int i=0; i<imgDb.size(); i++){
        if(i!=binToAvoid){
            for(int j=0; j<imgDb[i].size(); j++){

                string image_url = imgDb[i][j];
                string map_url = maskDb[i][j];

                /*
                 * Load the current image and its hair map
                 */
                Mat image = imread(image_url,0);
                Mat map = imread(map_url,0);

                if(map.channels()>1)
                    cvtColor(map, map, CV_RGB2GRAY);

                image = myResize(image, RESIZE);
                resize(map, map, image.size());
                clearMat(map);

                //Taglio immagine e mappa per rendere le dimensioni dell'immagine
                //proporzionali a cellWidth
                image = image(Rect((int) (image.cols%cellWidth)/2.0, (int) (image.rows%cellWidth)/2.0, image.cols - image.cols%cellWidth, image.rows - image.rows%cellWidth));
                map = map(Rect((int) (image.cols%cellWidth)/2.0, (int) (image.rows%cellWidth)/2.0, map.cols - map.cols%cellWidth, map.rows - map.rows%cellWidth));

                maps.push_back(map);

                /*
                 * HOG 2 e GABOR 2
                 */
                vector<vector<vector<float> > > descrittoriNormalizzati;
                vector<vector<float> > localEnergyTmp;
                vector<vector<float> > meanAmplitudeTmp;

                getHog2(image, descrittoriNormalizzati, cellWidth, numBin);
                getGabor2(image, localEnergyTmp, meanAmplitudeTmp, (unsigned int) cellWidth);

                outputHOG.push_back(descrittoriNormalizzati);
                localEnergy.push_back(localEnergyTmp);
                meanAmplitude.push_back(meanAmplitudeTmp);

                if(((++numero_immagini_elaborate)%(imgDb[i].size()))==0)
                    cout << "Elaborate " << numero_immagini_elaborate << " immagini su " << (imgDb.size()-1)*imgDb[i].size()  << "." << endl;

            }
        }
    }

    //Normalizzo i vettori localEnergy e meanAmplitude
    findMinMax(outputHOG, new_min, new_max);
    findMinMax(localEnergy, min_local_energy, max_local_energy);
    findMinMax(meanAmplitude, min_mean_amplitude, max_mean_amplitude);

    normalizeVector(localEnergy, min_local_energy, max_local_energy, new_min, new_max);
    normalizeVector(meanAmplitude, min_mean_amplitude, max_mean_amplitude, new_min, new_max);

    float perc_pixel_giusti_minimi = 0.5;

        //Aggiungo i valori alla matrice trainingData per l'addestramento
        //e salvo i valori delle maps nelle labels
        for(int i=0; i<outputHOG.size(); i++){

            //Itero lungo le celle
            for(int indice_cella_x=0; indice_cella_x<outputHOG[i].size(); indice_cella_x++){

                for(int indice_cella_y=0; indice_cella_y<outputHOG[i][indice_cella_x].size(); indice_cella_y++){

                    //Trovo il pixel in alto a sx della cella
                    int x_cella_iniziale = indice_cella_x*cellWidth;
                    int y_cella_iniziale = indice_cella_y*cellWidth;

                    //Controllo se l'intorno la cella ha almeno perc_pixel_giusti_minimi % di pixel
                    //di una classe, altrimenti scarto la cella
                    int num_pixel_cella = cellWidth*cellWidth;
                    int num_pixel_foreground = 0;
                    int num_pixel_background = 0;

                    for(unsigned int c = x_cella_iniziale; c < x_cella_iniziale + cellWidth; c++){
                        for(unsigned int r = y_cella_iniziale; r < y_cella_iniziale + cellWidth; r++){

                            if(maps[i].at<uchar>(r,c) == 255)
                                num_pixel_foreground++;
                            else
                                num_pixel_background++;

                        }
                    }

                    float pixelClass = 0.0;

                    if(num_pixel_foreground > num_pixel_cella*perc_pixel_giusti_minimi)
                        pixelClass = FOREGROUND;
                    else if(num_pixel_background >= num_pixel_cella*perc_pixel_giusti_minimi)
                        pixelClass = BACKGROUND;


                    //Se la condizione della percentuale minima è rispettata
                    //aggiungo la cella ai dati per gli alberi di decisione
                    if(pixelClass==FOREGROUND || (pixelClass==BACKGROUND && rand()%100<BACKGROUND_PERC)){

                        labelsVector.push_back(pixelClass);

                        vector<float> features;

                        for(int k=0; k<numBin; k++){
                            features.push_back(outputHOG[i][indice_cella_x][indice_cella_y][k]);
                        }

                        features.push_back(localEnergy[i][y_cella_iniziale + (int) cellWidth/2][x_cella_iniziale + (int) cellWidth/2]);
                        features.push_back(meanAmplitude[i][y_cella_iniziale + (int) cellWidth/2][x_cella_iniziale + (int) cellWidth/2]);

                        trainingDataVector.push_back(features);

                    }

                }

            }

        }


    //Svuoto un po' di ram cancellando vettori non più utili
    maps.clear();
    outputHOG.clear();
    localEnergy.clear();
    meanAmplitude.clear();

    cout << "dimensione dei dati di training: " << trainingDataVector.size() << endl;

    /*
         *
         * Converto i vector in array
         */
    int numPixels=labelsVector.size(); //Numero effettivo di pixel considerati per il training
    float labels_array[numPixels];
    float trainingData_array[numPixels][NUM_FEATURES];
    for(int i=0; i<numPixels; i++){
        labels_array[i] = labelsVector[i];
        for(int j=0; j<NUM_FEATURES; j++)
            trainingData_array[i][j] = trainingDataVector[i][j];
    }

    Mat labelsMat(numPixels, 1, CV_32FC1, labels_array);
    Mat trainingDataMat(numPixels, NUM_FEATURES, CV_32FC1, trainingData_array);

    trainingData = trainingDataMat.clone();
    labels = labelsMat.clone();

}


/*
 * Creo 2 mat per visualizzare gli errori del programma.
 * La test url contiene l'img originale con in verde ciò che l'albero di decisione ritiene capelli
 * la confusion mat, contiene: verde  -> veri positivi
 *                             blu    -> veri negativi
 *                             bianco -> falsi positivi
 *                             rosso  -> falsi negativi
 *                             nero   -> c'è qualcosa che non va, probabile bug
 */
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
             float &perc_sfondo_riconosciutoConPostProcessing){

    Mat test = imread(test_url, CV_LOAD_IMAGE_GRAYSCALE);

    test = myResize(test, test_resize);

    Mat confusionMat(test.rows, test.cols, CV_8UC3);
    Mat sampleMat(1,NUM_FEATURES,CV_32FC1);

    Mat map = imread(map_url, CV_LOAD_IMAGE_GRAYSCALE);

    map = myResize(map, test_resize);
    clearMat(map);

    Mat resultMat = imread(test_url, CV_LOAD_IMAGE_COLOR);
    resize(resultMat, resultMat, test.size());

    //Creo una mat per tener conto dei valori delle predizioni effettuate
    Mat countMat(test.rows, test.cols, CV_8UC1);
    countMat = Scalar(0);

    //Calcolo un offset per tagliare l'immagine così da tagliarla il più in centro possibile
    int offset_cols = (int) (test.cols%cellWidth)/2.0;
    int offset_rows = (int) (test.rows%cellWidth)/2.0;

    //Taglio le immagini per rendere le dimensioni delle immagini
    //proporzionali a cellWidth
    test = test(Rect(offset_cols, offset_rows, test.cols - test.cols%cellWidth, test.rows - test.rows%cellWidth));
    map = map(Rect(offset_cols, offset_rows, map.cols - map.cols%cellWidth, map.rows - map.rows%cellWidth));
    confusionMat = confusionMat(Rect(offset_cols, offset_rows, confusionMat.cols - confusionMat.cols%cellWidth, confusionMat.rows - confusionMat.rows%cellWidth));
    resultMat = resultMat(Rect(offset_cols, offset_rows, resultMat.cols - resultMat.cols%cellWidth, resultMat.rows - resultMat.rows%cellWidth));

    /*
     * HOG 2 e GABOR 2
     */
    vector<vector<vector<float> > > descrittoriNormalizzati;
    vector<vector<float> > localEnergy;
    vector<vector<float> > meanAmplitude;

    getHog2(test, descrittoriNormalizzati, cellWidth, numBin);
    getGabor2(test, localEnergy, meanAmplitude, (unsigned int) cellWidth);

    //Normalizzo l'output di Gabor
    normalizeVector(localEnergy, min_local_energy, max_local_energy, new_min, new_max);
    normalizeVector(meanAmplitude, min_mean_amplitude, max_mean_amplitude, new_min, new_max);

    //A questo punto effettuo le predizioni con l'albero di decisione addestrate in precedenza

    //Itero lungo le celle
    for(int indice_cella_x=0; indice_cella_x<descrittoriNormalizzati.size(); indice_cella_x++){
        for(int indice_cella_y=0; indice_cella_y<descrittoriNormalizzati[indice_cella_x].size(); indice_cella_y++){

            //Trovo il pixel in alto a sinistra della cella
            int x_cella_iniziale = indice_cella_x*cellWidth;
            int y_cella_iniziale = indice_cella_y*cellWidth;

            //Predico il risultato con l'albero di decisione e in caso metto i pixel corrispondenti positivi
            for(int k=0; k<numBin; k++)
                sampleMat.at<float>(k) = descrittoriNormalizzati[indice_cella_x][indice_cella_y][k];

            sampleMat.at<float>(numBin) = localEnergy[y_cella_iniziale + (int) cellWidth/2][x_cella_iniziale + (int) cellWidth/2];
            sampleMat.at<float>(numBin+1) = meanAmplitude[y_cella_iniziale + (int) cellWidth/2][x_cella_iniziale + (int) cellWidth/2];

            float response = dtree.predict(sampleMat)->value;

            //Salvo le predizioni sulla countMat
            if (response == FOREGROUND){

                for(unsigned int c = x_cella_iniziale; c < x_cella_iniziale + cellWidth; c++)
                    for(unsigned int r = y_cella_iniziale; r < y_cella_iniziale + cellWidth; r++)
                        countMat.at<uchar>(r,c) = countMat.at<uchar>(r,c) +1;

            }

            if(response!=FOREGROUND && response!=BACKGROUND)
                cout << "response: " << response << endl;

        }
    }

    //Adesso unisco i risultati ricevuti e se più della metà dell'albero di decisione Ritiene che
    //un certo pixel sia FOREGROUND sarà impostato come tale
    float predizioni_min = 0.5;

    //Itero lungo le celle
    for(int r=0; r<resultMat.rows; r++){
        for(int c=0; c<resultMat.cols; c++){
            if ((float) countMat.at<uchar>(r,c) > predizioni_min){

                resultMat.at<Vec3b>(r,c)[0]  = 0;
                resultMat.at<Vec3b>(r,c)[1]  = 255;
                resultMat.at<Vec3b>(r,c)[2]  = 0;

            }
        }
    }

    Mat original = imread(test_url, CV_LOAD_IMAGE_COLOR);
    original = myResize(original,test_resize);
    original = original(Rect(offset_cols, offset_rows, original.cols - original.cols%cellWidth, original.rows - original.rows%cellWidth));

    calculateAccuracy(resultMat, confusionMat, map,
                      accuracy, perc_capelli_riconosciuti, perc_sfondo_riconosciuto,
                      FOREGROUND, BACKGROUND, cellWidth);

    if(accuracy>90 || accuracy<10){
        imwrite(result_url,resultMat);
        imwrite(confusion_url, confusionMat);
    }

    //Applico una funzione di postprocessing al termine dell'elaborazione
    postProcessing(resultMat, original, cellWidth);

    calculateAccuracy(resultMat, confusionMat, map,
                      accuracyConPostProcessing, perc_capelli_riconosciutiConPostProcessing, perc_sfondo_riconosciutoConPostProcessing,
                      FOREGROUND, BACKGROUND, cellWidth);

    if(accuracyConPostProcessing>90 || accuracyConPostProcessing<10){
        imwrite(result_url_con_post_processing,resultMat);
        imwrite(confusion_url_con_post_processing, confusionMat);
    }

}


void fillVector(vector<vector<String> > &img_db,
                vector<vector<String> > &mask_db,
                vector<vector<String> > &vector_result,
                vector<vector<String> > &vector_confusion,
                vector<vector<String> > &vector_result_con_post_processing,
                vector<vector<String> > &vector_confusion_con_post_processing,
                int num_img, int num_bin){

    img_db = vector<vector<String> >(num_bin, vector<String>());
    mask_db = vector<vector<String> >(num_bin, vector<String>());
    vector_result = vector<vector<String> >(num_bin, vector<String>());
    vector_confusion = vector<vector<String> >(num_bin, vector<String>());
    vector_result_con_post_processing = vector<vector<String> >(num_bin, vector<String>());
    vector_confusion_con_post_processing = vector<vector<String> >(num_bin, vector<String>());

    for(int i=1; i<=num_img; i++){


        int bin_to_insert = (i-1)/(num_img/num_bin);
        if(bin_to_insert>num_bin-1)
            bin_to_insert = num_bin-1;

        stringstream name_original;
        name_original << "../db/originali/frame";

        int lengthCount = 0;
        for(int x = i; x > 0; x /= 10, lengthCount++);

        for(int x = 0; x<5-lengthCount; x++)
            name_original << "0";

        name_original << i;
        name_original << ".jpg";

        img_db[bin_to_insert].push_back(name_original.str().c_str());


        stringstream name_mask;
        name_mask << "../db/maschere/frame";

        for(int x = 0; x<5-lengthCount; x++)
            name_mask << "0";

        name_mask << i;
        name_mask << ".pbm";

        mask_db[bin_to_insert].push_back(name_mask.str().c_str());


        stringstream name_result;
        name_result << "../predict/frame";

        for(int x = 0; x<5-lengthCount; x++)
            name_result << "0";

        name_result << i;
        name_result << ".jpg";

        vector_result[bin_to_insert].push_back(name_result.str().c_str());


        stringstream name_confusion;
        name_confusion << "../predict/frame";

        for(int x = 0; x<5-lengthCount; x++)
            name_confusion << "0";

        name_confusion << i;
        name_confusion << "_confusion.jpg";

        vector_confusion[bin_to_insert].push_back(name_confusion.str().c_str());


        stringstream name_result_con_post_processing;
        name_result_con_post_processing << "../predict_postProcessing/frame";

        for(int x = 0; x<5-lengthCount; x++)
            name_result_con_post_processing << "0";

        name_result_con_post_processing << i;
        name_result_con_post_processing << ".jpg";

        vector_result_con_post_processing[bin_to_insert].push_back(name_result_con_post_processing.str().c_str());


        stringstream name_confusion_con_post_processing;
        name_confusion_con_post_processing << "../predict_postProcessing/frame";

        for(int x = 0; x<5-lengthCount; x++)
            name_confusion_con_post_processing << "0";

        name_confusion_con_post_processing << i;
        name_confusion_con_post_processing << "_confusion.jpg";

        vector_confusion_con_post_processing[bin_to_insert].push_back(name_confusion_con_post_processing.str().c_str());

    }

}
