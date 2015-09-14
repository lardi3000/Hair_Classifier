#include "main.hpp"

int NUM_FEATURES = NUM_HOG + NUM_GABOR;

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

/*
 * Variabili booleane che modificano il comportamento del programma
 *
 * Il programma di default non prevede il calcolo delle features
 * ne l'addestramento dell'SVM, ne la creazione di un file csv
 * contenente i dati del training set. L'unico comportamento
 * abilitato di default è l'algoritmo di postProcessing
 *
 * Per abilitare le opzioni è possibile aggiungere parametri al lancio
 * del software. I parametri validi sono:
 * -f: abilita il calcolo delle features (comando eseguito solo se viene effettuato il calcolo dell'svm
 * -dtree: abilita il calcolo dell'svm
 * -cvs: crea il file csv contenente il training set
 * -p: disattiva il postProcessing
 *
 */

bool calcolaFeatures = false;
bool addestraDTree = false;
bool creaCSV = false;
bool effettuaPostProcessing = true;

int main(int argc, char ** argv){

    //Gestione dei parametri di chiamata del programma
    string opzione_features("-f");
    string opzione_dtree("-dtree");
    string opzione_csv("-csv");
    string opzione_p("-p");

    for(int i=1; i<argc; i++){

        string stringa_da_testare(argv[i]);

        if(stringa_da_testare.compare(opzione_features) == 0)
            calcolaFeatures = true;
        else if(stringa_da_testare.compare(opzione_dtree) == 0)
            addestraDTree = true;
        else if(stringa_da_testare.compare(opzione_csv) == 0)
            creaCSV = true;
        else if(stringa_da_testare.compare(opzione_p) == 0)
            effettuaPostProcessing = false;

    }

    cout << "Inizio programma." << endl << endl;
    cout << "Iniziata la fase di training" << endl;

    double tempo_training = (double) getTickCount();

    ofstream file_out("../predict/out");

    if(addestraDTree){

        trainDTree();

    } else{

        //Leggo i dati salvati per effettuare il test
        FileStorage fsRead("../tmp/features.yml", FileStorage::READ);

        if (fsRead.isOpened()){
            fsRead["min_local_energy"] >> min_local_energy;
            fsRead["max_local_energy"] >> max_local_energy;
            fsRead["min_mean_amplitude"] >> min_mean_amplitude;
            fsRead["max_mean_amplitude"] >> max_mean_amplitude;
            fsRead["new_min"] >> new_min;
            fsRead["new_max"] >> new_max;
        }

        fsRead.release();

    }

    tempo_training = ((double)getTickCount() - tempo_training)/getTickFrequency();

    cout << "Terminata la fase di training!!" << endl;
    cout << "Tempo necessario per la fase di training: " << tempo_training << " s." << endl << endl;
    cout << "Inizia la fase di testing!!" << endl;

    double tempo_test = (double) getTickCount();

    int train_resize = RESIZE;
    int test_resize = 1024;
    int numTrain; // = 11;
    int numTest; // = 44;
    float accuracyTrain = 0.0;
    float accuracyTest = 0.0;
    float accuracyTmp;
    float percCapelliRiconosciutiTmp;
    float percCapelliRiconosciutiTrain = 0.0;
    float percCapelliRiconosciutiTest = 0.0;
    float percSfondoRiconosciutoTmp;
    float percSfondoRiconosciutoTrain = 0.0;
    float percSfondoRiconosciutoTest = 0.0;

    //Creo i vettori con le immagini da testare
    vector<String> vector_test, vector_map, vector_result, vector_confusion;
    fillVector(vector_test, vector_map, vector_result, vector_confusion, numTrain, numTest);

    for(unsigned int i=0; i<vector_result.size(); i++){

        double tempo_test_tmp = (double) getTickCount();

        if(i<numTrain){

            predict(vector_test[i],
                    vector_map[i],
                    train_resize,
                    vector_result[i],
                    vector_confusion[i],
                    accuracyTmp,
                    percCapelliRiconosciutiTmp,
                    percSfondoRiconosciutoTmp);

            accuracyTrain += accuracyTmp;
            percCapelliRiconosciutiTrain += percCapelliRiconosciutiTmp;
            percSfondoRiconosciutoTrain += percSfondoRiconosciutoTmp;

        }else{

            predict(vector_test[i],
                    vector_map[i],
                    test_resize,
                    vector_result[i],
                    vector_confusion[i],
                    accuracyTmp,
                    percCapelliRiconosciutiTmp,
                    percSfondoRiconosciutoTmp);

            if(i<numTest+numTrain){
                accuracyTest += accuracyTmp;
                percCapelliRiconosciutiTest += percCapelliRiconosciutiTmp;
                percSfondoRiconosciutoTest += percSfondoRiconosciutoTmp;
            }

        }

        tempo_test_tmp = ((double)getTickCount() - tempo_test_tmp)/getTickFrequency();

        cout << "Elaborata l'immagine " << vector_result[i].substr(11, vector_result[i].length());
        cout << "   Accuracy: " << accuracyTmp << " % capelli riconosciuti: " << percCapelliRiconosciutiTmp;
        cout << " % sfondo riconosciuto: " << percSfondoRiconosciutoTmp << " % ";
        cout << "tempo impiegato: " << tempo_test_tmp << " s." << endl;


        file_out << "Elaborata l'immagine " << vector_result[i].substr(11, vector_result[i].length());
        file_out << "   Accuracy: " << accuracyTmp << " % capelli riconosciuti: " << percCapelliRiconosciutiTmp;
        file_out << " % sfondo riconosciuto: " << percSfondoRiconosciutoTmp << " % ";
        file_out << "tempo impiegato: " << tempo_test_tmp << " s." << endl;

    }

    accuracyTrain = accuracyTrain / numTrain;
    accuracyTest = accuracyTest / numTest;
    percCapelliRiconosciutiTrain = percCapelliRiconosciutiTrain / numTrain;
    percCapelliRiconosciutiTest = percCapelliRiconosciutiTest / numTest;
    percSfondoRiconosciutoTrain = percSfondoRiconosciutoTrain / numTrain;
    percSfondoRiconosciutoTest = percSfondoRiconosciutoTest / numTest;

    tempo_test = ((double)getTickCount() - tempo_test)/getTickFrequency();

    cout << "Terminata la fase di test!" << endl;

    cout << endl << "Programma terminato!" << endl;
    cout << "Tempo necessario per la fase di training: " << tempo_training << " s." << endl;
    cout << "Tempo necessario per la fase di test: " << tempo_test << " s." << endl;
    cout << "Tempo medio per il test di una singola immagine: " << tempo_test/vector_result.size() << " s." << endl;
    cout << "Accuracy train: " << accuracyTrain << " %" << endl;
    cout << "Accuracy test: " << accuracyTest << " %" << endl;
    cout << "Percentuale capelli riconosciuti train: " << percCapelliRiconosciutiTrain << " %" << endl;
    cout << "Percentuale capelli riconosciuti test: " << percCapelliRiconosciutiTest << " %" << endl;
    cout << "Percentuale sfondo riconosciuto train: " << percSfondoRiconosciutoTrain << " %" << endl;
    cout << "Percentuale sfondo riconosciuto test: " << percSfondoRiconosciutoTest << " %" << endl;

    file_out << endl << "Programma terminato!" << endl;
    file_out << "Tempo necessario per la fase di training: " << tempo_training << " s." << endl;
    file_out << "Tempo necessario per la fase di test: " << tempo_test << " s." << endl;
    file_out << "Tempo medio per il test di una singola immagine: " << tempo_test/vector_result.size() << " s." << endl;
    file_out << "Accuracy train: " << accuracyTrain << " %" << endl;
    file_out << "Accuracy test: " << accuracyTest << " %" << endl;
    file_out << "Percentuale capelli riconosciuti train: " << percCapelliRiconosciutiTrain << " %" << endl;
    file_out << "Percentuale capelli riconosciuti test: " << percCapelliRiconosciutiTest << " %" << endl;
    file_out << "Percentuale sfondo riconosciuto train: " << percSfondoRiconosciutoTrain << " %" << endl;
    file_out << "Percentuale sfondo riconosciuto test: " << percSfondoRiconosciutoTest << " %" << endl;

    file_out.close();

    return 0;

}

void trainDTree(){

    Mat trainingData, labels;

    if(calcolaFeatures){

        double tempo_features = (double) getTickCount();

        calculateFeatures(trainingData, labels);

        tempo_features = ((double)getTickCount() - tempo_features)/getTickFrequency();
        cout << "Tempo necessario per calcolare le features: " << tempo_features << " s." << endl;

        //Salvo i dati necessari per effettuare il training
        FileStorage fsWrite("../tmp/features.yml", FileStorage::WRITE);
        fsWrite << "trainingData" << trainingData;
        fsWrite << "labels" << labels;
        fsWrite << "min_local_energy" << min_local_energy;
        fsWrite << "max_local_energy" << max_local_energy;
        fsWrite << "min_mean_amplitude" << min_mean_amplitude;
        fsWrite << "max_mean_amplitude" << max_mean_amplitude;
        fsWrite << "new_min" << new_min;
        fsWrite << "new_max" << new_max;
        fsWrite.release();

    } else{

        //Leggo i dati salvati per effettuare il test
        FileStorage fsRead("../tmp/features.yml", FileStorage::READ);

        if (fsRead.isOpened()){
            fsRead["trainingData"] >> trainingData;
            fsRead["labels"] >> labels;
            fsRead["min_local_energy"] >> min_local_energy;
            fsRead["max_local_energy"] >> max_local_energy;
            fsRead["min_mean_amplitude"] >> min_mean_amplitude;
            fsRead["max_mean_amplitude"] >> max_mean_amplitude;
            fsRead["new_min"] >> new_min;
            fsRead["new_max"] >> new_max;
        }

        fsRead.release();
    }

    cout << "Terminato il calcolo del training set." << endl;

    CvDTree dtree;

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

    stringstream nomeDTree;
    nomeDTree << "../tmp/dtree.xml";
    dtree.save(nomeDTree.str().c_str());

    cout << "Albero di decisione addestrato." << endl;


}

void calculateFeatures(Mat &trainingData, Mat &labels){

    MYSQL *connection;
    MYSQL_RES *resource;
    MYSQL_ROW result;

    connection = mysql_init(NULL);
    char *servername     = "localhost";
    char *user           = "root";
    char *password       = "";
    char *database       = "hair_db2";
    char *socket         = "/opt/lampp/var/mysql/mysql.sock";
    char *hostinfo;
    char *serverinfo;
    connection = mysql_real_connect(connection, servername, user,password, database, 0, socket, 0);

    mysql_query(connection, "SELECT * FROM images");
    resource = mysql_use_result(connection);

    vector<float> labelsVector;
    vector<vector<float> > trainingDataVector;

    //In outputHOG c'è il vettore degli output di HOG
    vector<Mat> maps = vector<Mat>();
    vector<vector<vector<vector<float> > > > outputHOG = vector<vector<vector<vector<float> > > >();
    vector<vector<vector<float> > > localEnergy = vector<vector<vector<float> > >();
    vector<vector<vector<float> > > meanAmplitude = vector<vector<vector<float> > >();

    int numero_immagini_elaborate = 1;

    //Calcolo tutte le features
    while((result = mysql_fetch_row(resource))) {

        string image_url = result[1];
        string map_url = result[2];

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

        cout << "Elaborata l'immagine " << numero_immagini_elaborate++ << " di 61." << endl;

    }

    mysql_close(connection);

    //Normalizzo i vettori localEnergy e meanAmplitude
    findMinMax(outputHOG, new_min, new_max);
    findMinMax(localEnergy, min_local_energy, max_local_energy);
    findMinMax(meanAmplitude, min_mean_amplitude, max_mean_amplitude);

    normalizeVector(localEnergy, min_local_energy, max_local_energy, new_min, new_max);
    normalizeVector(meanAmplitude, min_mean_amplitude, max_mean_amplitude, new_min, new_max);

    ofstream file_out;
    if(creaCSV){
        file_out.open("../predict/training_set.csv");
        for(int k=0; k<numBin; k++)
            file_out << "hog" << k+1 << ",";
        file_out << "localEnergy,meanAmplitude,map" << endl;
    }

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
                //aggiungo la cella ai dati per l'svm
                if(pixelClass==FOREGROUND || (pixelClass==BACKGROUND && rand()%100<BACKGROUND_PERC)){

                    labelsVector.push_back(pixelClass);

                    vector<float> features;

                    for(int k=0; k<numBin; k++){
                        features.push_back(outputHOG[i][indice_cella_x][indice_cella_y][k]);
                    }

                    features.push_back(localEnergy[i][y_cella_iniziale + (int) cellWidth/2][x_cella_iniziale + (int) cellWidth/2]);
                    features.push_back(meanAmplitude[i][y_cella_iniziale + (int) cellWidth/2][x_cella_iniziale + (int) cellWidth/2]);

                    trainingDataVector.push_back(features);

                    if(creaCSV){
                        for(int k=0; k<numBin; k++)
                            file_out << outputHOG[i][indice_cella_x][indice_cella_y][k] << ",";
                        file_out << localEnergy[i][y_cella_iniziale + (int) cellWidth/2][x_cella_iniziale + (int) cellWidth/2] << ",";
                        file_out << meanAmplitude[i][y_cella_iniziale + (int) cellWidth/2][x_cella_iniziale + (int) cellWidth/2] << ",";
                        file_out << pixelClass << endl;
                    }

                }

            }

        }

    }

    if(creaCSV)
        file_out.close();

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
 * La test url contiene l'img originale con in verde ciò che svm ritiene capelli
 * la confusion mat, contiene: verde  -> veri positivi
 *                             blu    -> veri negativi
 *                             bianco -> falsi positivi
 *                             rosso  -> falsi negativi
 *                             nero   -> c'è qualcosa che non va, probabile bug
 */
void predict(String test_url,
             String map_url,
             int test_resize,
             String result_url,
             String confusion_url,
             float &accuracy,
             float &perc_capelli_riconosciuti,
             float &perc_sfondo_riconosciuto){

    Mat test = imread(test_url, CV_LOAD_IMAGE_GRAYSCALE);

    test = myResize(test, test_resize);

    Mat confusionMat(test.rows, test.cols, CV_8UC3);
    Mat sampleMat(1,NUM_FEATURES,CV_32FC1);

    Mat map = imread(map_url, CV_LOAD_IMAGE_GRAYSCALE);

    map = myResize(map, test_resize);
    clearMat(map);

    Mat resultMat = imread(test_url, CV_LOAD_IMAGE_COLOR);
    resize(resultMat, resultMat, test.size());

    //Calcolo un offset per tagliare l'immagine così da tagliarla il più in centro possibile
    int offset_cols = (int) (test.cols%cellWidth)/2.0;
    int offset_rows = (int) (test.rows%cellWidth)/2.0;

    //Taglio le immagini per rendere le dimensioni delle immagini
    //proporzionali a cellWidth
    test = test(Rect(offset_cols, offset_rows, test.cols - test.cols%cellWidth, test.rows - test.rows%cellWidth));
    map = map(Rect(0, 0, map.cols - map.cols%cellWidth, map.rows - map.rows%cellWidth));
    confusionMat = confusionMat(Rect(0, 0, confusionMat.cols - confusionMat.cols%cellWidth, confusionMat.rows - confusionMat.rows%cellWidth));
    resultMat = resultMat(Rect(0, 0, resultMat.cols - resultMat.cols%cellWidth, resultMat.rows - resultMat.rows%cellWidth));

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

    CvDTree dtree;
    stringstream nomeDTree;
    nomeDTree << "../tmp/dtree.xml";
    dtree.load(nomeDTree.str().c_str());

    //Itero lungo le celle
    for(int indice_cella_x=0; indice_cella_x<descrittoriNormalizzati.size(); indice_cella_x++){
        for(int indice_cella_y=0; indice_cella_y<descrittoriNormalizzati[indice_cella_x].size(); indice_cella_y++){

            //Trovo il pixel in alto a sinistra della cella
            int x_cella_iniziale = indice_cella_x*cellWidth;
            int y_cella_iniziale = indice_cella_y*cellWidth;

            //Predico il risultato con l'svm e in caso metto i pixel corrispondenti positivi
            for(int k=0; k<numBin; k++)
                sampleMat.at<float>(k) = descrittoriNormalizzati[indice_cella_x][indice_cella_y][k];

            sampleMat.at<float>(numBin) = localEnergy[y_cella_iniziale + (int) cellWidth/2][x_cella_iniziale + (int) cellWidth/2];
            sampleMat.at<float>(numBin+1) = meanAmplitude[y_cella_iniziale + (int) cellWidth/2][x_cella_iniziale + (int) cellWidth/2];

            float response = dtree.predict(sampleMat)->value;

            //Salvo le predizioni sulla resultMat
            if (response == FOREGROUND){

                for(unsigned int c = x_cella_iniziale; c < x_cella_iniziale + cellWidth; c++){
                    for(unsigned int r = y_cella_iniziale; r < y_cella_iniziale + cellWidth; r++){

                        resultMat.at<Vec3b>(r,c)[0]  = 0;
                        resultMat.at<Vec3b>(r,c)[1]  = 255;
                        resultMat.at<Vec3b>(r,c)[2]  = 0;

                    }
                }

            }

        }
    }

    Mat original = imread(test_url, CV_LOAD_IMAGE_COLOR);
    original = myResize(original,test_resize);

    //Applico una funzione di postprocessing al termine dell'elaborazione
    if(effettuaPostProcessing)
        postProcessing(resultMat, original, cellWidth);

    calculateAccuracy(resultMat, confusionMat, map,
                      accuracy, perc_capelli_riconosciuti, perc_sfondo_riconosciuto,
                      FOREGROUND, BACKGROUND, cellWidth);

    imwrite(result_url,resultMat);
    imwrite(confusion_url, confusionMat);

}

void fillVector(vector<String> &vector_test,
                vector<String> &vector_map,
                vector<String> &vector_result,
                vector<String> &vector_confusion,
                int &num_train,
                int &num_test){

    vector_test = vector<String>();
    vector_map = vector<String>();
    vector_result = vector<String>();
    vector_confusion = vector<String>();

    //Aggiungo le immagini da testare per il train

    vector_test.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Beautiful_healty_hair_resized.JPG");
    vector_map.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Beautiful_healty_hair_resized_hair_map.JPG");
    vector_result.push_back("../predict/train0.jpg");
    vector_confusion.push_back("../predict/train0_confusion.jpg");

    vector_test.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56bleached_hair_o3o_daid_by_mischievousgirl-d65oyat_resized.jpg");
    vector_map.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56bleached_hair_o3o_daid_by_mischievousgirl-d65oyat_resized_hair_map.jpg");
    vector_result.push_back("../predict/train1.jpg");
    vector_confusion.push_back("../predict/train1_confusion.jpg");

    vector_test.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Blonde_hair_resized.JPG");
    vector_map.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Blonde_hair_resized_hair_map.JPG");
    vector_result.push_back("../predict/train2.jpg");
    vector_confusion.push_back("../predict/train2_confusion.jpg");

    vector_test.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56hair-315053_640_resized.jpg");
    vector_map.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56hair-315053_640_resized_hair_map.jpg");
    vector_result.push_back("../predict/train3.jpg");
    vector_confusion.push_back("../predict/train3_confusion.jpg");

    vector_test.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Hand_combed_hair_resized.JPG");
    vector_map.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Hand_combed_hair_resized_hair_map.JPG");
    vector_result.push_back("../predict/train4.jpg");
    vector_confusion.push_back("../predict/train4_confusion.jpg");

    vector_test.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Natalie_Portman_2010_resized.jpg");
    vector_map.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Natalie_Portman_2010_resized_hair_map.jpg");
    vector_result.push_back("../predict/train5.jpg");
    vector_confusion.push_back("../predict/train5_confusion.jpg");

    vector_test.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56252964050_a43e9f9b11_b_resized.jpg");
    vector_map.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56252964050_a43e9f9b11_b_resized_hair_map.jpg");
    vector_result.push_back("../predict/train6.jpg");
    vector_confusion.push_back("../predict/train6_confusion.jpg");

    vector_test.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566776475056_9f75afa3a4_b_resized.jpg");
    vector_map.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566776475056_9f75afa3a4_b_resized_hair_map.jpg");
    vector_result.push_back("../predict/train7.jpg");
    vector_confusion.push_back("../predict/train7_confusion.jpg");

    vector_test.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro5614804535712_44427edb6b_o_d_resized.jpg");
    vector_map.push_back("/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro5614804535712_44427edb6b_o_d_resized_hair_map.jpg");
    vector_result.push_back("../predict/train8.jpg");
    vector_confusion.push_back("../predict/train8_confusion.jpg");

    vector_test.push_back("/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr723Kaley_Cuoco_at_PaleyFest_2013_resized.jpg");
    vector_map.push_back("/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr723Kaley_Cuoco_at_PaleyFest_2013_resized_hair_map.jpg");
    vector_result.push_back("../predict/train9.jpg");
    vector_confusion.push_back("../predict/train9_confusion.jpg");

    vector_test.push_back("/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe46747577235_cd2d4d76f1_b_resized.jpg");
    vector_map.push_back("/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe46747577235_cd2d4d76f1_b_resized_hair_map.jpg");
    vector_result.push_back("../predict/train10.jpg");
    vector_confusion.push_back("../predict/train10_confusion.jpg");

    num_train = vector_test.size();

    //Adesso aggiungo le immagini da testare per il test

    vector_test.push_back("../images_test/image0_resized.jpg");
    vector_map.push_back("../images_test/image0_resized_hair_map.jpg");
    vector_result.push_back("../predict/test0.jpg");
    vector_confusion.push_back("../predict/test0_confusion.jpg");

    vector_test.push_back("../images_test/image1_resized.jpg");
    vector_map.push_back("../images_test/image1_resized_hair_map.jpg");
    vector_result.push_back("../predict/test1.jpg");
    vector_confusion.push_back("../predict/test1_confusion.jpg");

    vector_test.push_back("../images_test/image2_resized.jpg");
    vector_map.push_back("../images_test/image2_resized_hair_map.jpg");
    vector_result.push_back("../predict/test2.jpg");
    vector_confusion.push_back("../predict/test2_confusion.jpg");

    vector_test.push_back("../images_test/image3_resized.jpg");
    vector_map.push_back("../images_test/image3_resized_hair_map.jpg");
    vector_result.push_back("../predict/test3.jpg");
    vector_confusion.push_back("../predict/test3_confusion.jpg");

    vector_test.push_back("../images_test/image4_resized.jpg");
    vector_map.push_back("../images_test/image4_resized_hair_map.jpg");
    vector_result.push_back("../predict/test4.jpg");
    vector_confusion.push_back("../predict/test4_confusion.jpg");

    vector_test.push_back("../images_test/image5_resized.jpg");
    vector_map.push_back("../images_test/image5_resized_hair_map.jpg");
    vector_result.push_back("../predict/test5.jpg");
    vector_confusion.push_back("../predict/test5_confusion.jpg");

    vector_test.push_back("../images_test/image6_resized.jpg");
    vector_map.push_back("../images_test/image6_resized_hair_map.jpg");
    vector_result.push_back("../predict/test6.jpg");
    vector_confusion.push_back("../predict/test6_confusion.jpg");

    vector_test.push_back("../images_test/image7_resized.jpg");
    vector_map.push_back("../images_test/image7_resized_hair_map.jpg");
    vector_result.push_back("../predict/test7.jpg");
    vector_confusion.push_back("../predict/test7_confusion.jpg");

    vector_test.push_back("../images_test/image8_resized.jpg");
    vector_map.push_back("../images_test/image8_resized_hair_map.jpg");
    vector_result.push_back("../predict/test8.jpg");
    vector_confusion.push_back("../predict/test8_confusion.jpg");

    vector_test.push_back("../images_test/image9_resized.jpg");
    vector_map.push_back("../images_test/image9_resized_hair_map.jpg");
    vector_result.push_back("../predict/test9.jpg");
    vector_confusion.push_back("../predict/test9_confusion.jpg");

    vector_test.push_back("../images_test/image10_resized.jpg");
    vector_map.push_back("../images_test/image10_resized_hair_map.jpg");
    vector_result.push_back("../predict/test10.jpg");
    vector_confusion.push_back("../predict/test10_confusion.jpg");

    vector_test.push_back("../images_test/image11_resized.jpg");
    vector_map.push_back("../images_test/image11_resized_hair_map.jpg");
    vector_result.push_back("../predict/test11.jpg");
    vector_confusion.push_back("../predict/test11_confusion.jpg");

    vector_test.push_back("../images_test/image12_resized.jpg");
    vector_map.push_back("../images_test/image12_resized_hair_map.jpg");
    vector_result.push_back("../predict/test12.jpg");
    vector_confusion.push_back("../predict/test12_confusion.jpg");

    vector_test.push_back("../images_test/image13_resized.jpg");
    vector_map.push_back("../images_test/image13_resized_hair_map.jpg");
    vector_result.push_back("../predict/test13.jpg");
    vector_confusion.push_back("../predict/test13_confusion.jpg");

    vector_test.push_back("../images_test/image14_resized.jpg");
    vector_map.push_back("../images_test/image14_resized_hair_map.jpg");
    vector_result.push_back("../predict/test14.jpg");
    vector_confusion.push_back("../predict/test14_confusion.jpg");

    vector_test.push_back("../images_test/image15_resized.jpg");
    vector_map.push_back("../images_test/image15_resized_hair_map.jpg");
    vector_result.push_back("../predict/test15.jpg");
    vector_confusion.push_back("../predict/test15_confusion.jpg");

    vector_test.push_back("../images_test/image16_resized.jpg");
    vector_map.push_back("../images_test/image16_resized_hair_map.jpg");
    vector_result.push_back("../predict/test16.jpg");
    vector_confusion.push_back("../predict/test16_confusion.jpg");

    vector_test.push_back("../images_test/image17_resized.jpg");
    vector_map.push_back("../images_test/image17_resized_hair_map.jpg");
    vector_result.push_back("../predict/test17.jpg");
    vector_confusion.push_back("../predict/test17_confusion.jpg");

    vector_test.push_back("../images_test/image18_resized.jpg");
    vector_map.push_back("../images_test/image18_resized_hair_map.jpg");
    vector_result.push_back("../predict/test18.jpg");
    vector_confusion.push_back("../predict/test18_confusion.jpg");

    vector_test.push_back("../images_test/image19_resized.jpg");
    vector_map.push_back("../images_test/image19_resized_hair_map.jpg");
    vector_result.push_back("../predict/test19.jpg");
    vector_confusion.push_back("../predict/test19_confusion.jpg");

    vector_test.push_back("../images_test/image20_resized.jpg");
    vector_map.push_back("../images_test/image20_resized_hair_map.jpg");
    vector_result.push_back("../predict/test20.jpg");
    vector_confusion.push_back("../predict/test20_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0ambra-angiolini-2_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0ambra-angiolini-2_resized_hair_map.jpg");
    vector_result.push_back("../predict/test21.jpg");
    vector_confusion.push_back("../predict/test21_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0barbato_headshot1_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0barbato_headshot1_resized_hair_map.jpg");
    vector_result.push_back("../predict/test22.jpg");
    vector_confusion.push_back("../predict/test22_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0bfdcd718-640b-4af5-8661-3a5560a7d852_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0bfdcd718-640b-4af5-8661-3a5560a7d852_resized_hair_map.jpg");
    vector_result.push_back("../predict/test23.jpg");
    vector_confusion.push_back("../predict/test23_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0capelli2_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0capelli2_resized_hair_map.jpg");
    vector_result.push_back("../predict/test24.jpg");
    vector_confusion.push_back("../predict/test24_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0capelli-corti-uomo-ricci-con-ciuffo-800x1024_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0capelli-corti-uomo-ricci-con-ciuffo-800x1024_resized_hair_map.jpg");
    vector_result.push_back("../predict/test25.jpg");
    vector_confusion.push_back("../predict/test25_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0capelli-donna4_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0capelli-donna4_resized_hair_map.jpg");
    vector_result.push_back("../predict/test26.jpg");
    vector_confusion.push_back("../predict/test26_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0capelli-mossi5_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0capelli-mossi5_resized_hair_map.jpg");
    vector_result.push_back("../predict/test27.jpg");
    vector_confusion.push_back("../predict/test27_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0Dollarphotoclub_52732977_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0Dollarphotoclub_52732977_resized_hair_map.jpg");
    vector_result.push_back("../predict/test28.jpg");
    vector_confusion.push_back("../predict/test28_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0Heat-Free-Hair-For-Kurls-Line-Empress-Wig-Medium_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0Heat-Free-Hair-For-Kurls-Line-Empress-Wig-Medium_resized_hair_map.jpg");
    vector_result.push_back("../predict/test29.jpg");
    vector_confusion.push_back("../predict/test29_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h05499fc515e85e_-_hbz-beauty-hair-promo_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h05499fc515e85e_-_hbz-beauty-hair-promo_resized_hair_map.jpg");
    vector_result.push_back("../predict/test30.jpg");
    vector_confusion.push_back("../predict/test30_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0IMG_3553-copia_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0IMG_3553-copia_resized_hair_map.jpg");
    vector_result.push_back("../predict/test31.jpg");
    vector_confusion.push_back("../predict/test31_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0le-attrici-di-l-oreal-paris-cinema-373861_w1000_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0le-attrici-di-l-oreal-paris-cinema-373861_w1000_resized_hair_map.jpg");
    vector_result.push_back("../predict/test32.jpg");
    vector_confusion.push_back("../predict/test32_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0Maurizio_Aiello_2013_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0Maurizio_Aiello_2013_resized_hair_map.jpg");
    vector_result.push_back("../predict/test33.jpg");
    vector_confusion.push_back("../predict/test33_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0maxresdefault_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0maxresdefault_resized_hair_map.jpg");
    vector_result.push_back("../predict/test34.jpg");
    vector_confusion.push_back("../predict/test34_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0mission-impossible-ghost-protocol_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0mission-impossible-ghost-protocol_resized_hair_map.jpg");
    vector_result.push_back("../predict/test35.jpg");
    vector_confusion.push_back("../predict/test35_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0Nora1.q1_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0Nora1.q1_resized_hair_map.jpg");
    vector_result.push_back("../predict/test36.jpg");
    vector_confusion.push_back("../predict/test36_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0Raoul_Bova_1_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0Raoul_Bova_1_resized_hair_map.jpg");
    vector_result.push_back("../predict/test37.jpg");
    vector_confusion.push_back("../predict/test37_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0shakira-2320-600x390_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0shakira-2320-600x390_resized_hair_map.jpg");
    vector_result.push_back("../predict/test38.jpg");
    vector_confusion.push_back("../predict/test38_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0shilajit-hair-1_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0shilajit-hair-1_resized_hair_map.jpg");
    vector_result.push_back("../predict/test39.jpg");
    vector_confusion.push_back("../predict/test39_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0taglio-capelli-sotiili-1024x1024_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0taglio-capelli-sotiili-1024x1024_resized_hair_map.jpg");
    vector_result.push_back("../predict/test40.jpg");
    vector_confusion.push_back("../predict/test40_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0zzzmaxresdefault_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h0zzzmaxresdefault_resized_hair_map.jpg");
    vector_result.push_back("../predict/test41.jpg");
    vector_confusion.push_back("../predict/test41_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h01-Vanessa-Hessler3_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h01-Vanessa-Hessler3_resized_hair_map.jpg");
    vector_result.push_back("../predict/test42.jpg");
    vector_confusion.push_back("../predict/test42_confusion.jpg");

    vector_test.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h025euw4w_resized.jpg");
    vector_map.push_back("../images_test/fslg1sjeuu17vn5f93ne97p7h025euw4w_resized_hair_map.jpg");
    vector_result.push_back("../predict/test43.jpg");
    vector_confusion.push_back("../predict/test43_confusion.jpg");

    num_test = vector_test.size() - num_train;

    vector_test.push_back("../images_test/image11.jpg");
    vector_map.push_back("../images_test/image11_map.jpg");
    vector_result.push_back("../predict/test44.jpg");
    vector_confusion.push_back("../predict/test44_confusion.jpg");

    vector_test.push_back("../images_test/image14.jpg");
    vector_map.push_back("../images_test/image14_map.jpg");
    vector_result.push_back("../predict/test45.jpg");
    vector_confusion.push_back("../predict/test45_confusion.jpg");

    vector_test.push_back("../images_test/image15.jpg");
    vector_map.push_back("../images_test/image15_map.jpg");
    vector_result.push_back("../predict/test46.jpg");
    vector_confusion.push_back("../predict/test46_confusion.jpg");

    vector_test.push_back("../images_test/image17.jpg");
    vector_map.push_back("../images_test/image17_map.jpg");
    vector_result.push_back("../predict/test47.jpg");
    vector_confusion.push_back("../predict/test47_confusion.jpg");


}
