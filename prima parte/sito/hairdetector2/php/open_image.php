<?php 

	require_once('utils.php');
	start_session();
	
	//La versione parte da 1 e si incrementa ad ogni esecuzione di GrabCut
	$_SESSION['version']=1;

	//Legge il path dell'immagine
	$_SESSION['path_resize'] = $_SESSION['image'];
	$_SESSION['path_original'] = $_SESSION['image'];

	//Cancella eventuali dati temporanei vecchi
	if(is_readable("../tmp/dati.yml")){
		unlink("../tmp/dati.yml");
	}
	
	//Crea il path della mappa
	$_SESSION['map_path']=get_map_path($_SESSION['path_original']);
	
	echo $_SESSION['image'];
	echo "<br/>";
	echo $_SESSION['path_original'];
	echo "<br/>";
			
	header("location: ../segmentation.php");//redirect
	
?>

