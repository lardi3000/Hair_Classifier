<?php 
	require_once('php/utils.php');
	start_session();
?>

<html>
	<head>
		<link rel="stylesheet" type="text/css" href="style/index_style.css"/>
		<title>HairDetector</title>
	</head>
	<body>
		<div id="my_title">
			<h1>Hair Detector</h1>
			<img src="images/graphic.jpg" width="200"></img>	
		</div>
		<div id="container">
			<div class="content">
				<form action="php/upload_images.php" method="post">
					<p>Insert the link to add the image to the database:</p>
					<p><input type="text" name="file" size="50" value="" /></p>
					<?php 
						//Controllo dell'url dell'immagine
						if(isset($_SESSION['img_check']) && $_SESSION['img_check']==TRUE)
							echo '<p style="color:red">Errore nell\'URL</p>';
					?>
					<p><input type="checkbox" name="cc" value="cc" checked="checked"/> Image common creative</p>
					<p><input type="submit" name="submit" value="Start" /></p>
				</form>
			</div>
			<div class="content">
				<?php 
						//Confermo il salvataggio nel db dell'immagine
						if(isset($_SESSION['img_salvata_nel_db']) && $_SESSION['img_salvata_nel_db']==TRUE)
							echo '<p>';
						else {
							//Cancello eventuali immagini rimaste nella cartella tmp
							if(isset($_SESSION['img_salvata_nel_db']) && $_SESSION['img_salvata_nel_db']==FALSE)
								@unlink($_SESSION['path_resize']);
						}
					?>
				<a href="db_viewer.php">Database</a>
				<?php 
						//Confermo il salvataggio nel db dell'immagine
						if(isset($_SESSION['img_salvata_nel_db']) && $_SESSION['img_salvata_nel_db']==TRUE)
							echo '</p><p>Immagine salvata correttamente nel database!</p>';
					?>
			</div>
		</div>
	</body>
</html>