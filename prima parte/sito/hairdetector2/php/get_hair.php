	
<?php

	require_once('utils.php');
	start_session();
	
	$cmd='/opt/lampp/htdocs/hairdetector2/opencv/GrabCut '.$_SESSION['path_resize'].' '.$_SESSION['map_path'].' '.$_SESSION['version'].' 2>&1';
	$_SESSION['version']++;
	$_SESSION['path_result_resize']=exec($cmd);
	
	//$_SESSION['path_result']=get_result_path($_SESSION['path_result_resize']);
	
	echo get_relative_path($_SESSION['path_result_resize']);
	
?>