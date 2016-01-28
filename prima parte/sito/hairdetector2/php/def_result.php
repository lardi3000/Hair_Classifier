<?php
	require_once('utils.php');
	require_once('db_utils.php');
	start_session();
	
	//Controllo che la mappa esista
	if(is_readable($_SESSION['path_resize'])){
	
		$_SESSION['img_salvata_nel_db'] = TRUE;
		
		$_SESSION['hair_map_path']=get_hair_map_path($_SESSION['path_resize']);
		connettiDB('localhost','root','','hair_db2');
		
		/*
		 * Sposto nella cartella db_images l'originale e la mappa generata da GrabCut
		 */
		$image_db_path=change_directory($_SESSION['path_resize'],'/opt/lampp/htdocs/hairdetector2/db_images/');
		$hair_db_path=change_directory($_SESSION['hair_map_path'],'/opt/lampp/htdocs/hairdetector2/db_images/');	
		rename($_SESSION['path_resize'],$image_db_path);
		rename($_SESSION['hair_map_path'],$hair_db_path);
		
		/*
		 * Inserisco nel DB
		 */
		 insert_image($image_db_path,$hair_db_path,$_SESSION['url_image'],$_SESSION['common_creative']);
		 	
		/*
		 * Tolgo l'immagine corrente dalla coda
		*/
		$new_stack=array();
		for($i=0;$i<$_SESSION['images_number'];$i++){
			if($i!=$_SESSION['current_index'])
				$new_stack[]=$_SESSION['images'][$i];
		}
		$_SESSION['images_number']--;
		$_SESSION['current_index']--;
		$_SESSION['images']=$new_stack;
		
	}

	/*
	 * Elimino le immagini temporanee
	 */
	@unlink($_SESSION['path_original']);
	@unlink($_SESSION['map_path']);
	@unlink($_SESSION['path_result_resize']);

	/*
	 * Redirect
	 */
	header("location: ../index.php");
	
?>
