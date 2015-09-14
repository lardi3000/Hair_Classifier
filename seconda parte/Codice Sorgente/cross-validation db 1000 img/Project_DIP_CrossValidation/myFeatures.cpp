#include "myFeatures.h"

void getHog2(Mat &image,
            vector<vector<vector<float> > > &descrittoriNormalizzati,
            int _cellWidth, int _numBin){

    int cellWidth = _cellWidth;
    int nBins = _numBin;

    Size cellSize(cellWidth, cellWidth);
    Size blockSize(cellWidth*2, cellWidth*2);
    Size winSize(image.cols,image.rows);

    HOGDescriptor hog(
                winSize, //winSize
                blockSize, //blocksize
                cellSize, //blockStride,
                cellSize, //cellSize,
                nBins, //nbins,
                0, //derivAper,
                -1, //winSigma,
                0, //histogramNormType,
                0.2, //L2HysThresh,
                0, //gammal correction,
                64 //nlevels
                );

    vector<Point> locations;
    vector<float> descriptorsValues;
    hog.compute( image, descriptorsValues, Size(0,0), Size(0,0), locations);

    // prepare data structure: 9 orientation / gradient strenghts for each cell
    int cells_in_x_dir = winSize.width / cellSize.width;
    int cells_in_y_dir = winSize.height / cellSize.height;
    float*** gradientStrengths = new float**[cells_in_y_dir];
    int** cellUpdateCounter   = new int*[cells_in_y_dir];
    for (int y=0; y<cells_in_y_dir; y++)
    {
        gradientStrengths[y] = new float*[cells_in_x_dir];
        cellUpdateCounter[y] = new int[cells_in_x_dir];
        for (int x=0; x<cells_in_x_dir; x++)
        {
            gradientStrengths[y][x] = new float[nBins];
            cellUpdateCounter[y][x] = 0;

            for (int bin=0; bin<nBins; bin++)
                gradientStrengths[y][x][bin] = 0.0;
        }
    }

    // nr of blocks = nr of cells - 1
    // since there is a new block on each cell (overlapping blocks!) but the last one
    int blocks_in_x_dir = cells_in_x_dir - 1;
    int blocks_in_y_dir = cells_in_y_dir - 1;

    // compute gradient strengths per cell
    int descriptorDataIdx = 0;

    for (int blockx=0; blockx<blocks_in_x_dir; blockx++)
    {
        for (int blocky=0; blocky<blocks_in_y_dir; blocky++)
        {
            // 4 cells per block ...
            for (int cellNr=0; cellNr<4; cellNr++)
            {
                // compute corresponding cell nr
                int cellx = blockx;
                int celly = blocky;
                if (cellNr==1) celly++;
                if (cellNr==2) cellx++;
                if (cellNr==3)
                {
                    cellx++;
                    celly++;
                }

                for (int bin=0; bin<nBins; bin++)
                {
                    float gradientStrength = descriptorsValues[ descriptorDataIdx ];
                    descriptorDataIdx++;

                    gradientStrengths[celly][cellx][bin] += gradientStrength;

                } // for (all bins)


                // note: overlapping blocks lead to multiple updates of this sum!
                // we therefore keep track how often a cell was updated,
                // to compute average gradient strengths
                cellUpdateCounter[celly][cellx]++;

            } // for (all cells)


        } // for (all block x pos)
    } // for (all block y pos)


    // compute average gradient strengths
    for (int celly=0; celly<cells_in_y_dir; celly++)
    {
        for (int cellx=0; cellx<cells_in_x_dir; cellx++)
        {

            float NrUpdatesForThisCell = (float)cellUpdateCounter[celly][cellx];

            // compute average gradient strenghts for each gradient bin direction
            for (int bin=0; bin<nBins; bin++)
            {
                gradientStrengths[celly][cellx][bin] /= NrUpdatesForThisCell;
            }
        }
    }

    //Riempio il vettore da restituire
    descrittoriNormalizzati = vector<vector<vector<float> > >(cells_in_x_dir, vector<vector<float> >(cells_in_y_dir, vector<float>(nBins)));

    for (int celly=0; celly<cells_in_y_dir; celly++)
        for (int cellx=0; cellx<cells_in_x_dir; cellx++)
            for (int bin=0; bin<nBins; bin++)
                descrittoriNormalizzati[cellx][celly][bin] = gradientStrengths[celly][cellx][bin];

    // don't forget to free memory allocated by helper data structures!
    for (int y=0; y<cells_in_y_dir; y++)
    {
        for (int x=0; x<cells_in_x_dir; x++)
        {
            delete[] gradientStrengths[y][x];
        }
        delete[] gradientStrengths[y];
        delete[] cellUpdateCounter[y];
    }
    delete[] gradientStrengths;
    delete[] cellUpdateCounter;

}

void getGabor2(const Mat &src, vector<vector<float> > &local_energy, vector<vector<float> > &mean_amplitude, unsigned int kernel_size){

    // matrices used
    Mat dst, src_f;
    vector<vector<vector<float> > > output_gabor = vector<vector<vector<float> > >();
    local_energy = vector<vector<float> >(src.rows, vector<float>(src.cols, 0.0));
    mean_amplitude = vector<vector<float> >(src.rows, vector<float>(src.cols, 0.0));

    //Trasformo l'immagine in una mat di float
    if(src.type() != CV_32F)
        src.convertTo(src_f,CV_32F);

    //Parametri gabor
    float sigma;
    float gamma = 0.5; //aspect ratio 0 < gamma < 1.

    float theta1[] = {0,23,45,68,90,113,135,158};
    vector<float> theta = vector<float>(theta1, theta1 + 8); //orientazione del filtro
    float psi1[] = {0, -45, -90};
    vector<float> psi = vector<float>(psi1, psi1 + 3); //phase offset -180 < psi < 180.
    double lamda1[] = {13,31,47};
    vector<float> lamda = vector<float>(lamda1, lamda1 + 3); //in teoria 2 < lambda < size(img)/5

    //Definisco variabili utili per i controllo dei cicli successivi
    unsigned int t,p,l;
    unsigned int r,c,f;

    for(t=0; t<theta.size(); t++){
        for(p=0; p<psi.size(); p++){
            for(l=0; l<lamda.size(); l++){

                //Applico il filtro di gabor
                sigma = 0.56*lamda[l];
                Mat kernel = getGaborKernel(cv::Size(kernel_size,kernel_size), sigma, theta[t], lamda[l], gamma, psi[p]);
                filter2D(src_f, dst, CV_32F, kernel);

                //Trasformo la mat in vector<vector<double> >
                vector<vector<float> > tmp = vector<vector<float> >(dst.rows, vector<float>(dst.cols, 0.0));
                for(unsigned int r=0; r<dst.rows; r++){
                    for(unsigned int c=0; c<dst.cols; c++){
                        tmp[r][c] = dst.at<float>(r,c);
                    }
                }

                output_gabor.push_back(tmp);

            }
        }
    }


    //A questo punto in output_gabor ho 48 mat con le risposte ai filtri.
    //Le combino per calcolare local_energy e mean_amplitude
    for(r=0; r<src.rows; r++){
        for(c=0; c<src.cols; c++){

            //Calcolo il valore della feature per il singolo pixel
            float tmp_local_energy = 0;
            float tmp_mean_amplitude = 0;

            for(f=0; f<output_gabor.size(); f++){

                tmp_local_energy += pow(output_gabor[f][r][c], 2.0);
                tmp_mean_amplitude += abs(output_gabor[f][r][c]);

            }

            local_energy[r][c] = tmp_local_energy;
            mean_amplitude[r][c] = tmp_mean_amplitude;

        }
    }

}
