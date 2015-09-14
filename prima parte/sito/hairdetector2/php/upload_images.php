<?php 

	require_once('utils.php');
	start_session();
	
	//Legge l'url dell'immagine da caricare
	$url_image = $_POST['file'];
	$_SESSION['url_image'] = $url_image;
		
	//Controllo se l'immagine ha il flag common creative spuntato
	if(isset($_POST['cc'])){
		$_SESSION['common_creative'] = TRUE;
	}
	else {
		$_SESSION['common_creative'] = FALSE;
	}	
	

	$name = substr(strrchr($url_image, "/"), 1 );
	$new_name=session_id().$name;
	$complete_path='/opt/lampp/htdocs/hairdetector2/tmp/'.$new_name;
		
	//Provo a scaricare l'immagine
	if (@copySecureFile($url_image,$complete_path) !== false) {
		
		//Controllo che il file scaricato sia un'immagine
		if(getimagesize($complete_path)){
		
			//costruisco l'immagine ridimensionata (lato più lungo = 500 px)
			$cmd=' /opt/lampp/htdocs/hairdetector2/opencv/resize2 '.$complete_path.' 500';	
			exec($cmd);
			$_SESSION['image']=get_resized_path($complete_path);
		
			unlink($complete_path);
	
			$_SESSION['img_check'] = FALSE;
			header("location: open_image.php");//redirect
		
		}
		else {
			$_SESSION['img_check'] = TRUE;
			header("location: ../index.php");//redirect			
		}
	}
	else {
		$_SESSION['img_check'] = TRUE;
		header("location: ../index.php");//redirect
	}
	
?>

