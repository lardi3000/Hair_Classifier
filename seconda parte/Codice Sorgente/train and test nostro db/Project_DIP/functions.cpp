#include "functions.hpp"


/*
 * Set all pixels to 255 or 0
 */
void clearMat(Mat image){
	for(int r=0;r<image.rows;r++){
		for(int c=0;c<image.cols;c++){
			int col=image.at<uchar>(r,c);
			if(col>200)
				image.at<uchar>(r,c)=255;
			else
				image.at<uchar>(r,c)=0;
		}
	}
}

/*
 * Ridimensione src fissando il lato più lungo = max_dim mantenendo le proporzioni
 * Se src ha entrambi i lati < max_dim non viene modificata
 */
Mat myResize(Mat src, int max_dim){

    int width=src.cols;
    int height=src.rows;
    int new_width,new_height;
    if(width<=max_dim&&height<=max_dim){
    	return src;
    }else{
    	if(width>height){
    		new_width=max_dim;
    		new_height=floor(new_width*height/width);
    	}else{
    		new_height=max_dim;
    		new_width=floor(new_height*width/height);
    	}
    }

    Mat dst(new_height,new_width,src.type());
   	resize(src,dst,dst.size(), 0, 0, INTER_LINEAR);
    return dst;

}

/*
 * Espando le dimensioni ripetendo il bordo sx/basso per rendere le dimensioni divisibile in celle div X div
 */
void makeMatSizeDivisible(Mat &src,Mat &dst,int div){
	int rest_x = src.cols%div;
	int rest_y = src.rows%div;

	resize(dst,dst,Size(src.cols+div-rest_x,src.rows+div-rest_y));

	for(int r=0;r<dst.rows;r++){
		for(int c=0;c<dst.cols;c++){
			if(r<src.rows&&c<src.cols)
                dst.at<unsigned char>(r,c) = src.at<unsigned char>(r,c);
			else
                dst.at<unsigned char>(r,c) = src.at<unsigned char>(min(r,src.rows-1),min(c,src.cols-1));
		}
	}
}

/*
 * trova il minimo e il massimo del vettore di input
 */
void findMinMax(vector<vector<vector<float> > > &vectorToFind, float &min, float &max){

    //Calcolo max e min di local energy, mean amplitude e phase amplitude
    unsigned int i,j,k;
    min = FLT_MAX;
    max = FLT_MIN;

    for(i=0; i<vectorToFind.size(); i++){
        for(j=0; j<vectorToFind[i].size(); j++){
            for(k=0; k<vectorToFind[i][j].size(); k++){

                //Salvo il valore max e min
                if(vectorToFind[i][j][k] > max)
                    max = vectorToFind[i][j][k];
                if(vectorToFind[i][j][k] < min)
                    min = vectorToFind[i][j][k];

            }
        }
    }

}


/*
 * trova il minimo e il massimo del vettore di input
 */
void findMinMax(vector<vector<vector<vector<float> > > > &vectorToFind, float &min, float &max){

    //Calcolo max e min di local energy, mean amplitude e phase amplitude
    unsigned int i,j,k,l;
    min = FLT_MAX;
    max = FLT_MIN;

    for(i=0; i<vectorToFind.size(); i++){
        for(j=0; j<vectorToFind[i].size(); j++){
            for(k=0; k<vectorToFind[i][j].size(); k++){
                for(l=0; l<vectorToFind[i][j][k].size(); l++){

                //Salvo il valore max e min
                if(vectorToFind[i][j][k][l] > max)
                    max = vectorToFind[i][j][k][l];
                if(vectorToFind[i][j][k][l] < min)
                    min = vectorToFind[i][j][k][l];

                }
            }
        }
    }

}

//Normalizza il vettore secondo i nuovi valori impostati
void normalizeVector(vector<vector<vector<float> > > &vectorToNormalize,
                     float oldMin, float oldMax,
                     float newMin, float newMax){

    unsigned int i,j,k;

    if(oldMin >= 0)
        for(i=0; i<vectorToNormalize.size(); i++)
            for(j=0; j<vectorToNormalize[i].size(); j++)
                for(k=0; k<vectorToNormalize[i][j].size(); k++)
                    vectorToNormalize[i][j][k] = ((vectorToNormalize[i][j][k] - oldMin) / (oldMax + oldMin))*(newMax-newMin) + newMin;
    else
        for(i=0; i<vectorToNormalize.size(); i++)
            for(j=0; j<vectorToNormalize[i].size(); j++)
                for(k=0; k<vectorToNormalize[i][j].size(); k++)
                    vectorToNormalize[i][j][k] = ((vectorToNormalize[i][j][k] - oldMin) / (oldMax - oldMin))*(newMax-newMin) + newMin;

}

//Normalizza il vettore secondo i nuovi valori impostati
void normalizeVector(vector<vector<float> > &vectorToNormalize,
                     float oldMin, float oldMax,
                     float newMin, float newMax){

    unsigned int i,j;

    if(oldMin >= 0)
        for(i=0; i<vectorToNormalize.size(); i++)
            for(j=0; j<vectorToNormalize[i].size(); j++)
                    vectorToNormalize[i][j] = ((vectorToNormalize[i][j] - oldMin)*(newMax-newMin) / (oldMax - oldMin)) + newMin;
    else
        for(i=0; i<vectorToNormalize.size(); i++)
            for(j=0; j<vectorToNormalize[i].size(); j++)
                    vectorToNormalize[i][j] = ((vectorToNormalize[i][j] + oldMin)*(newMax-newMin) / (oldMax + oldMin)) + newMin;


}


//Scandisce la matrice risultante cancellando i punti rilevati come capelli isolati
//e riempiendo eventuali punti vuoti in zone contrassegnate come capelli
void postProcessing(Mat &imgToProcess, Mat &imgOriginal, int cellWidth){

    //Itero l'algoritmo finchè non c'è alcuna modifica all'immagine
    float perc_massima = 0.3;
    int offset = cellWidth/3;
    bool blocca_ciclo = false;

    for(unsigned int i=0; !blocca_ciclo && i<10; i++){

        blocca_ciclo = true;

        //Scorro tutte le celle dell'immagine
        for(int r=0; r<imgToProcess.rows; r += cellWidth){
            for(int c=0; c<imgToProcess.cols; c += cellWidth){

                //identifico la classe di appartenenza della cella selezionata
                bool capelli = false;
                if(imgToProcess.at<Vec3b>(r+offset,c+offset)[0]==0 && imgToProcess.at<Vec3b>(r+offset,c+offset)[1]==255 && imgToProcess.at<Vec3b>(r+offset,c+offset)[3]==0)
                    capelli = true;

                float num_celle_adiacenti     = 0.0;
                float num_celle_stessa_classe = 0.0;

                //Controllo le 8 celle adiacenti per verificare se esistono e
                //se sono della stessa classe (capelli/non capelli)
                if(r-cellWidth >= 0){

                    int new_r = r-cellWidth +offset;

                    if(c-cellWidth >= 0){

                        int new_c_1 = c-cellWidth +offset;
                        num_celle_adiacenti++;
                        if(imgToProcess.at<Vec3b>(new_r,new_c_1)[0]==0 && imgToProcess.at<Vec3b>(new_r,new_c_1)[1]==255 && imgToProcess.at<Vec3b>(new_r,new_c_1)[3]==0){
                            if(capelli)
                                num_celle_stessa_classe++;
                        }
                        else if(!capelli)
                            num_celle_stessa_classe++;

                    }

                    int new_c_2 = c+offset;
                    num_celle_adiacenti++;
                    if(imgToProcess.at<Vec3b>(new_r,new_c_2)[0]==0 && imgToProcess.at<Vec3b>(new_r,new_c_2)[1]==255 && imgToProcess.at<Vec3b>(new_r,new_c_2)[3]==0){
                        if(capelli)
                            num_celle_stessa_classe++;
                    }
                    else if(!capelli)
                        num_celle_stessa_classe++;

                    if(c+cellWidth < imgToProcess.cols){

                        int new_c_3 = c+cellWidth +offset;
                        num_celle_adiacenti++;
                        if(imgToProcess.at<Vec3b>(new_r,new_c_3)[0]==0 && imgToProcess.at<Vec3b>(new_r,new_c_3)[1]==255 && imgToProcess.at<Vec3b>(new_r,new_c_3)[3]==0){
                            if(capelli)
                                num_celle_stessa_classe++;
                        }
                        else if(!capelli)
                            num_celle_stessa_classe++;

                    }

                }

                if(r+cellWidth < imgToProcess.rows){

                    int new_r = r+cellWidth +offset;

                    if(c-cellWidth >= 0){

                        int new_c_1 = c-cellWidth +offset;
                        num_celle_adiacenti++;
                        if(imgToProcess.at<Vec3b>(new_r,new_c_1)[0]==0 && imgToProcess.at<Vec3b>(new_r,new_c_1)[1]==255 && imgToProcess.at<Vec3b>(new_r,new_c_1)[3]==0){
                            if(capelli)
                                num_celle_stessa_classe++;
                        }
                        else if(!capelli)
                            num_celle_stessa_classe++;

                    }

                    int new_c_2 = c+offset;
                    num_celle_adiacenti++;
                    if(imgToProcess.at<Vec3b>(new_r,new_c_2)[0]==0 && imgToProcess.at<Vec3b>(new_r,new_c_2)[1]==255 && imgToProcess.at<Vec3b>(new_r,new_c_2)[3]==0){
                        if(capelli)
                            num_celle_stessa_classe++;
                    }
                    else if(!capelli)
                        num_celle_stessa_classe++;

                    if(c+cellWidth < imgToProcess.cols){

                        int new_c_3 = c+cellWidth +offset;
                        num_celle_adiacenti++;
                        if(imgToProcess.at<Vec3b>(new_r,new_c_3)[0]==0 && imgToProcess.at<Vec3b>(new_r,new_c_3)[1]==255 && imgToProcess.at<Vec3b>(new_r,new_c_3)[3]==0){
                            if(capelli)
                                num_celle_stessa_classe++;
                        }
                        else if(!capelli)
                            num_celle_stessa_classe++;

                    }

                }

                if(c-cellWidth >= 0){

                    int new_r = r+offset;
                    int new_c = c-cellWidth +offset;
                    num_celle_adiacenti++;
                    if(imgToProcess.at<Vec3b>(new_r,new_c)[0]==0 && imgToProcess.at<Vec3b>(new_r,new_c)[1]==255 && imgToProcess.at<Vec3b>(new_r,new_c)[3]==0){
                        if(capelli)
                            num_celle_stessa_classe++;
                    }
                    else if(!capelli)
                        num_celle_stessa_classe++;

                }

                if(c+cellWidth < imgToProcess.cols){

                    int new_r = r+offset;
                    int new_c = c+cellWidth +offset;
                    num_celle_adiacenti++;
                    if(imgToProcess.at<Vec3b>(new_r,new_c)[0]==0 && imgToProcess.at<Vec3b>(new_r,new_c)[1]==255 && imgToProcess.at<Vec3b>(new_r,new_c)[3]==0){
                        if(capelli)
                            num_celle_stessa_classe++;
                    }
                    else if(!capelli)
                        num_celle_stessa_classe++;

                }

                //Se la percentuale di celle della stessa classe è minore
                //della percentuale massima specificata, allora la cella cambia classe
                if((float) (num_celle_stessa_classe/num_celle_adiacenti) < perc_massima){

                    blocca_ciclo = false;

                    for(unsigned int r_interno=r; r_interno<r+cellWidth; r_interno++){
                        for(unsigned int c_interno=c; c_interno<c+cellWidth; c_interno++){

                            if(!capelli){
                                imgToProcess.at<Vec3b>(r_interno,c_interno)[0] = 0;
                                imgToProcess.at<Vec3b>(r_interno,c_interno)[1] = 255;
                                imgToProcess.at<Vec3b>(r_interno,c_interno)[2] = 0;
                            }
                            else{
                                imgToProcess.at<Vec3b>(r_interno,c_interno)[0] = imgOriginal.at<Vec3b>(r_interno,c_interno)[0];
                                imgToProcess.at<Vec3b>(r_interno,c_interno)[1] = imgOriginal.at<Vec3b>(r_interno,c_interno)[1];
                                imgToProcess.at<Vec3b>(r_interno,c_interno)[2] = imgOriginal.at<Vec3b>(r_interno,c_interno)[2];
                            }

                        }
                    }

                }

            }
        }

    }

}


//Calcola l'accuratezza della predizione
void calculateAccuracy(Mat &resultMat,
                       Mat &confusionMat,
                       Mat &map,
                       float &accuracy,
                       float &perc_capelli_riconosciuti,
                       float &perc_sfondo_riconosciuto,
                       int foreground,
                       int background,
                       int cellWidth){

    //Riempio la confusionMat
    for(int r=0; r<map.rows; r++){
        for(int c=0; c<map.cols; c++){

            int response = background;
            if(resultMat.at<Vec3b>(r,c)[0] == 0 && resultMat.at<Vec3b>(r,c)[1] == 255 && resultMat.at<Vec3b>(r,c)[2] == 0)
                response = foreground;

            //Riempio la confusionMat
            if(response == foreground && (int) map.at<uchar>(r,c) == 255){
                confusionMat.at<Vec3b>(r,c)[0] = 0;
                confusionMat.at<Vec3b>(r,c)[1] = 255;
                confusionMat.at<Vec3b>(r,c)[2] = 0;
            } else if(response == background && (int) map.at<uchar>(r,c) == 0){
                confusionMat.at<Vec3b>(r,c)[0] = 255;
                confusionMat.at<Vec3b>(r,c)[1] = 0;
                confusionMat.at<Vec3b>(r,c)[2] = 0;
            } else if(response == background && (int) map.at<uchar>(r,c) == 255){
                confusionMat.at<Vec3b>(r,c)[0] = 255;
                confusionMat.at<Vec3b>(r,c)[1] = 255;
                confusionMat.at<Vec3b>(r,c)[2] = 255;
            } else if(response == foreground && (int) map.at<uchar>(r,c) == 0){
                confusionMat.at<Vec3b>(r,c)[0] = 0;
                confusionMat.at<Vec3b>(r,c)[1] = 0;
                confusionMat.at<Vec3b>(r,c)[2] = 255;
            } else{
                confusionMat.at<Vec3b>(r,c)[0] = 0;
                confusionMat.at<Vec3b>(r,c)[1] = 0;
                confusionMat.at<Vec3b>(r,c)[2] = 0;
            }

        }
    }

    //Salvo il numero di pixel, di true positive,
    //true negative, false positive e false negative
    int numCelle = 0;
    int numTP = 0;
    int numTN = 0;
    int numFP = 0;
    int numFN = 0;

    int offset = (int) (cellWidth / 3.0);

    //Calcolo TP, TN, FP, FN
    for(int r=0; r<map.rows; r += cellWidth){
        for(int c=0; c<map.cols; c += cellWidth){

            //Salvo la risposta dell'SVM
            int response_SVM = background;
            if(resultMat.at<Vec3b>(r+offset,c+offset)[0] == 0 && resultMat.at<Vec3b>(r+offset,c+offset)[1] == 255 && resultMat.at<Vec3b>(r+offset,c+offset)[2] == 0)
                response_SVM = foreground;

            //Conto il numero di pixel del quadrato foreground-background
            int response_MAP = INT_MAX;
            int num_foreground = 0;
            int num_background = 0;
            for(int r_interno=r; r_interno < r+cellWidth; r_interno++){
                for(int c_interno=c; c_interno < c+cellWidth; c_interno++){

                    if((int) map.at<uchar>(r_interno,c_interno) == 255)
                        num_foreground++;
                    else
                        num_background++;

                }
            }

            //Se almeno il 50% +1 dei pixel è di una categoria allora imposto la
            //risposta della mappa come quella categoria
            if(num_foreground > ((cellWidth*cellWidth)/2.0))
                response_MAP = foreground;
            else
                response_MAP = background;

            if(response_SVM == foreground && response_MAP == foreground){
                numTP++;
                numCelle++;
            } else if(response_SVM == background && response_MAP == background){
                numTN++;
                numCelle++;
            } else if(response_SVM == foreground && response_MAP == background){
                numFP++;
                numCelle++;
            } else if(response_SVM == background && response_MAP == foreground){
                numFN++;
                numCelle++;
            }

        }
    }


    //calcolo accuracy e il resto
    accuracy = (float) (numTP + numTN)*100.0/numCelle;

    if(numTP+numFN > 0)
        perc_capelli_riconosciuti = (float) (numTP*100.0)/(numTP+numFN);
    else
        perc_capelli_riconosciuti = 100.0;


    if(numTN+numFP > 0)
        perc_sfondo_riconosciuto = (float) (numTN*100.0)/(numTN+numFP);
    else
        perc_sfondo_riconosciuto = 100.0;

}



