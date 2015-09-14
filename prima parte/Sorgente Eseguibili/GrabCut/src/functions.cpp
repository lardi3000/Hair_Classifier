#include "functions.hpp"

/*
 * Aggiunge text_to_add a filename prima dell'estensione
 * Es:
 * filename='immaigne.png'
 * text_to_add='_modificata'
 * return 'immagine_modificata.png'
 */
string add_string_before_extension(string filename,string text_to_add){
	int pos=filename.find_last_of(".");
	string new_filename;
	new_filename=filename.substr(0,pos)+text_to_add+filename.substr(pos);
	return new_filename;
}
/*
 * Riceve in ingresso un'immagine 500x500 che contiente linee verdi e rosse
 * verde=FG
 * rosso=BG
 * w,h sono le dimensioni dell'immagine ridimensionata e devo limitare la mappa a quelle dimensioni
 */
Mat extract_map_from_image(Mat img,int h,int w){

	Mat map(h,w,CV_8UC1,Scalar(GC_PR_BGD));
	for(int r=0;r<img.rows;r++)
		for(int c=0;c<img.cols;c++){
			int blu=(int)img.at<Vec3b>(r,c)[0];
			int green=(int)img.at<Vec3b>(r,c)[1];
			int red=(int)img.at<Vec3b>(r,c)[2];
			if(red==255&&green==0&&blu==0)
				map.at<unsigned char>(r,c)=GC_BGD;
			if(red==0&&green==255&&blu==0)
				map.at<unsigned char>(r,c)=GC_FGD;
		}

	return map;
}
