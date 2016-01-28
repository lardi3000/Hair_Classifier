<?php

	require_once('db_utils.php');
	connettiDB('localhost','root','','hair_db');
	delete_image_by_id($_POST['id']);
	
	
?>