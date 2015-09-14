<?php
	function start_session(){
		if(!isset($_SESSION)) 
    	{ 
        session_start(); 
    	}
	}
	
	/*
	 * Aggiunge del testo prima dell'estensione
	 */
	function add_text_before_extension($filename,$text_to_add){
		$pos=strrpos($filename,'.');
		$new_filename=substr($filename,0,$pos);
		$new_filename.=$text_to_add;
		$new_filename.=substr($filename,$pos);
		return $new_filename;
	}
	/*
	 * Dato un path assoluto, estrae il nome del file e cambia la directory
	 */
	function change_directory($original_path,$new_directory){
		$pos=strrpos($original_path,'/');
		$new_path=substr($original_path,$pos+1);
		$new_path=$new_directory.$new_path;
		return $new_path;
	}
	
	function get_resized_path($path){
		return add_text_before_extension($path,'_resized');
	}
	
	function get_relative_path($path){
		return substr($path,17);
	}
	function get_map_path($path){
		return change_extension(add_text_before_extension($path, '_map'),'png');
	}
	function get_hair_map_path($path){
		return add_text_before_extension($path, '_hair_map');
	}
	
	function change_extension($filename,$new_extension){
		$pos=strrpos($filename,'.');
		$new_filename=substr($filename,0,$pos+1);
		$new_filename.=$new_extension;
		return $new_filename;
	}
	//toglie resized e la versione 
	function get_result_path($result_resize){
		$extension=substr($result_resize,strrpos($result_resize,'.'));
		$pos=strrpos($result_resize,'_resized_');
		$result_path=substr($result_resize,0,$pos);
		$result_path.=$extension;
		return add_text_before_extension($result_path,'_result');
	}
	
/**
* Scarica un file in http/https
*
* @param string $FromLocation
* @param string $ToLocation
* @return boolean
*/
function copySecureFile($FromLocation,$ToLocation,$VerifyHost=true)
{
	// Initialize CURL with providing full https URL of the file location
	$Channel = curl_init($FromLocation);
 
	// Open file handle at the location you want to copy the file: destination path at local drive
	$File = fopen ($ToLocation, "w");
 
	// Set CURL options
	curl_setopt($Channel, CURLOPT_FILE, $File);
 
	// We are not sending any headers
	curl_setopt($Channel, CURLOPT_HEADER, 0);
 
	// Disable PEER SSL Verification: If you are not running with SSL or if you don't have valid SSL
	curl_setopt($Channel, CURLOPT_SSL_VERIFYPEER, FALSE);
 
	// Disable HOST (the site you are sending request to) SSL Verification,
	// if Host can have certificate which is nvalid / expired / not signed by authorized CA.
	curl_setopt($Channel, CURLOPT_SSL_VERIFYHOST, $VerifyHost);
 
	// Execute CURL command
	curl_exec($Channel);
 
	// Close the CURL channel
	curl_close($Channel);
 
	// Close file handle
	fclose($File);
 
	// return true if file download is successfull
	return file_exists($ToLocation);
}

?>