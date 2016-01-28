<?php

/*
 * Connessione Database
 */
function connettiDB($db_host,$db_user,$db_password,$db_name) {
	$connessione = mysql_connect($db_host,$db_user,$db_password) or die("Connessione non riuscita: " . mysql_error());
   	$db_selected = mysql_select_db($db_name, $connessione);
	if (!$db_selected)
    	die ('Errore nella connessione al DB : ' . mysql_error());
}

function insert_image($image,$map,$url,$cc){
	$query='INSERT INTO images (image_path,map_path,link_image,common_creative)
				 VALUES ("'.$image.'","'.$map.'","'.$url.'","'.$cc.'");';
	echo $query;
	mysql_query($query) or die(mysql_error());
}

/*
 * Delete image from db and disk
 */
function delete_image_by_id($id){
	$query='SELECT * FROM images WHERE ID = \''.$id.'\';';
	$result=mysql_query($query);
	$row=mysql_fetch_array($result);
	unlink($row['image_path']);
	unlink($row['map_path']);
	$query='DELETE FROM images WHERE ID = \''.$id.'\';';
	mysql_query($query) or die(mysql_error());
}

?>