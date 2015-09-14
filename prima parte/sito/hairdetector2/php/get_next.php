<?php
	require_once('utils.php');
	start_session();
	$_SESSION['current_index']++;
	if($_SESSION['current_index']==$_SESSION['images_number'])
		$_SESSION['current_index']=0;
	header("location: open_image.php");//redirect
?>