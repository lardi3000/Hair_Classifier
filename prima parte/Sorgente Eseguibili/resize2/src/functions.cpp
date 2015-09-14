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
