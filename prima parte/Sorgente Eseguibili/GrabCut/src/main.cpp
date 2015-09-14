#include "main.hpp"

/*
 * Versione: numero incrementale che indica quante volte è stato chiamato il prigramma sull'immagine ridimensionata
 * Se versione==-1 richiede il risultato definitivp, quindi chiamo graCut sull'immagine originale
 */
int main(int argc, char ** argv){

	string path_img_original=argv[1];
	string path_img_resized=argv[2];
	string path_map=argv[3];
/*
	string path_img_original="/opt/lampp/htdocs/hairdetector/tmp/1.jpg";
	string path_img_resized="/opt/lampp/htdocs/hairdetector/tmp/1_resized.jpg";
	string path_map="/opt/lampp/htdocs/hairdetector/tmp/1_map.png";
	*/
	int version=atoi(argv[4]);


	//Immagine originale
	Mat img_original=imread(path_img_original,1);
	//Immagine ridimensionata
	Mat img_resized=imread(path_img_resized,1);
	//Mappa dell'utente
	Mat map=imread(path_map,1);
	string output_filename_original,output_filename_resized;
	string hair_map;


	/*
	 * Salvo il risultato ridimensionato con la versione corrente
	 */
	ostringstream oss;
	oss << "_result_" << version;
	string text_to_add=oss.str();
	output_filename_resized=add_string_before_extension(path_img_resized,text_to_add);
	/*
	 * Elimino la versione precedente se esiste
	 */
	if(version>1){
		ostringstream oss_old;
		oss_old<<"_result_"<<--version;
		string text_to_add_old=oss_old.str();
		remove(add_string_before_extension(path_img_resized,text_to_add_old).c_str());
	}

	output_filename_original=add_string_before_extension(path_img_original,"_result");



	/*
	* Definisco la maschera
	*/
	Mat markers;
	resize(map,map,img_original.size());
	markers=extract_map_from_image(map,img_original.rows,img_original.cols);

	//cout << "markers: "<<markers.rows<<"x"<<markers.cols<<endl;
	Mat bgd, fgd;
	int iterations = 2;
	/*
	 * chiamo grabCut
	 */
	grabCut(img_original, markers, cv::Rect(), bgd, fgd, iterations, cv::GC_INIT_WITH_MASK);
	// let's get all foreground and possible foreground pixels
	Mat mask_fgpf = ( markers == GC_FGD) | ( markers == GC_PR_FGD);

	// and copy all the foreground-pixels to a temporary image
	Mat result(img_original.size(),CV_8UC3,Scalar(255,255,255));
	img_original.copyTo(result,mask_fgpf);

	//imwrite(output_filename_original,result);
	resize(result,result,img_resized.size());
	imwrite(output_filename_resized,result);

	/*
	 * Costruisco la mappa dei capelli
	 */
	ostringstream oss2;
	oss2 << "_hair_map";
	string text_to_add2=oss2.str();
	hair_map=add_string_before_extension(path_img_original,text_to_add2);
	imwrite(hair_map,mask_fgpf);

	/*
	 * Stampo il path del risultato resized per la web app
	 */
	cout<<output_filename_resized;
	return 0;
}
