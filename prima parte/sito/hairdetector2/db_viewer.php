<html>
	<head>
		<title>Database</title>
		<link rel="stylesheet" type="text/css" href="db_viewer_style.css"/>
		<script src="//ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>	
		<?php
			require_once 'php/utils.php';
			require_once 'php/db_utils.php';
			start_session();
			$_SESSION['img_salvata_nel_db'] = FALSE;
		?>
	</head>
	<body>
		<a href="index.php">HOME</a>
		<?php
			echo '<div id="imgs_container">';
			echo '</div>';
		?>
	</body>
	<script type="text/javascript">
		$(document).ready(function(){
			$('#imgs_container').load('php/print_db.php');
		});
		function delete_img(id){
			$.post('php/delete_img_from_db.php',{id:id},function(){
				$('#imgs_container').load('php/print_db.php');
			});
		}
	</script>
</html>