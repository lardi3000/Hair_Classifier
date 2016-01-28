<?php
	require_once 'utils.php';
	require_once 'db_utils.php';
	connettiDB('localhost','root','','hair_db2');
	$query="SELECT * FROM images";
	$result=mysql_query($query);
	while($row=mysql_fetch_array($result)){
				echo '<div class="img_container">';
					echo '<img src="'.get_relative_path($row['image_path']).'" width="250">';
					echo '<img src="'.get_relative_path($row['map_path']).'" width="250">';
					echo '<a class="delete_img" href="javascript:delete_img('.$row['ID'].');" title="delete"></a>';
				echo '</div>';
			}
?>