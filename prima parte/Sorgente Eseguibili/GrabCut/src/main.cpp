#include "main.hpp"

/*
 * Versione: numero incrementale che indica quante volte è stato chiamato il prigramma sull'immagine ridimensionata
 * Se version==-1 richiede il risultato definitivp, quindi chiamo graCut sull'immagine originale
 */
int main(int argc, char ** argv){

    string path_img_resized=argv[1];
    string path_map=argv[2];
    int version=atoi(argv[3]);
/*
    string path_img_resized="../1_resized.jpg";
    string path_map="../1_map.png";
    int version=1;
*/
	//Immagine ridimensionata
	Mat img_resized=imread(path_img_resized,1);
	//Mappa dell'utente
	Mat map=imread(path_map,1);
    string output_filename_resized, final_output;

	/*
	 * Salvo il risultato ridimensionato con la versione corrente
	 */
	ostringstream oss;
    oss << "_result_" << version;
	string text_to_add=oss.str();
	output_filename_resized=add_string_before_extension(path_img_resized,text_to_add);

    ostringstream oss_2;
    oss_2 << "_hair_map";
    string text_to_add_2=oss_2.str();
    final_output=add_string_before_extension(path_img_resized,text_to_add_2);

	/*
	 * Elimino la versione precedente se esiste
	 */
	if(version>1){
		ostringstream oss_old;
		oss_old<<"_result_"<<--version;
		string text_to_add_old=oss_old.str();
		remove(add_string_before_extension(path_img_resized,text_to_add_old).c_str());
	}

	/*
	* Definisco la maschera
	*/
	Mat markers;
    map = map(Rect(0,0,img_resized.cols, img_resized.rows));
    markers=extract_map_from_image(map,img_resized.rows,img_resized.cols);

	//cout << "markers: "<<markers.rows<<"x"<<markers.cols<<endl;
	Mat bgd, fgd;
    int iterations = 2;

    if(version>1){

        //Leggo i dati salvati nelle iterazioni precedenti
        FileStorage fsRead("../tmp/temp.yml", FileStorage::READ);

        if (fsRead.isOpened()){
            fsRead["bgd"] >> bgd;
            fsRead["fgd"] >> fgd;
        }

        fsRead.release();

    }

	/*
	 * chiamo grabCut
	 */
    grabCut(img_resized, markers, cv::Rect(), bgd, fgd, iterations, cv::GC_INIT_WITH_MASK);

    //Salvo i dati necessari per effettuare il training
    FileStorage fsWrite("../tmp/temp.yml", FileStorage::WRITE);
    fsWrite << "bgd" << bgd;
    fsWrite << "fgd" << fgd;
    fsWrite.release();

	// let's get all foreground and possible foreground pixels
	Mat mask_fgpf = ( markers == GC_FGD) | ( markers == GC_PR_FGD);

	// and copy all the foreground-pixels to a temporary image
    Mat result(img_resized.size(),CV_8UC3,Scalar(255,255,255));
    img_resized.copyTo(result,mask_fgpf);

	resize(result,result,img_resized.size());
	imwrite(output_filename_resized,result);

    imwrite(final_output,mask_fgpf);

	/*
	 * Stampo il path del risultato resized per la web app
	 */
	cout<<output_filename_resized;
	return 0;
}
