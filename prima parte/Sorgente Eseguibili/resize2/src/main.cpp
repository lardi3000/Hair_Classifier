#include "main.hpp"


int main(int argc, char ** argv)
{

    string filename=argv[1];
    int max_dim=atoi(argv[2]);
    string output_filename=add_string_before_extension(filename,"_resized");
    cout<<filename<<endl<<max_dim<<endl<<output_filename<<endl;
    Mat img=imread(filename.c_str(),1);
    int width=img.cols;
    int height=img.rows;
    int new_width,new_height;
    if(width<=max_dim&&height<=max_dim){
    	new_width=width;
    	new_height=height;
    }else{
    	if(width>height){
    		new_width=max_dim;
    		new_height=floor(new_width*height/width);
    	}else{
    		new_height=max_dim;
    		new_width=floor(new_height*width/height);
    	}
    }
    Mat img_r(new_height,new_width,CV_8UC3);
	resize(img, img_r, img_r.size(), 0, 0, INTER_LINEAR);
	imwrite(output_filename,img_r);
	return 0;
}
