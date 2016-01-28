<?php
		require_once 'utils.php';
		start_session();
		$imageData=$_POST['img_data'];		
		$filteredData=substr($imageData, strpos($imageData, ",")+1);	
		$unencodedData=base64_decode($filteredData);
		$fp = fopen($_SESSION['map_path'], 'wb' );
		fwrite( $fp, $unencodedData);
		fclose( $fp );
?>