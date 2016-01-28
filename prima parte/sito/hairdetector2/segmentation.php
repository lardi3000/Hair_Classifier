<html>
	<head>
		<title>HairDetector</title>
		<link rel="stylesheet" type="text/css" href="style.css"/>
		<script src="//ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
		<script type="text/javascript" src="js/canvas_manager.js"></script>
		<?php
			require_once 'php/utils.php';
			start_session();
			$_SESSION['img_salvata_nel_db'] = FALSE;
		?>
	</head>
	<body onload="init()">
		<div class="menu_bar">			
				<a href="index.php" id="import_btn" title="home"></a>
				<a href="php/def_result.php" id="upload_btn" title="upload to DB"></a>
				<div class="text_menu"><?php echo $_SESSION['path_resize'];?></div>
		</div>
		<div id="container">
			<div class="canvas_container" id="canvas_container_1" bg_path="<?php echo get_relative_path($_SESSION['path_resize']); ?>" style="background-image: url('<?php echo get_relative_path($_SESSION['path_resize']); ?>')">
				<canvas id="myCanvas" width="500" height="500"></canvas>
			</div>
			<div class="canvas_container"  id="canvas_container_2">
				<canvas  id="myCanvas2" width="500" height="500"></canvas>
			</div> 
		</div>
		<div id='test'></div>
		<div class="menu_bar">		
			<a href="javascript:select_fg()" id="fg_btn" title="foreground"></a>
			<a href="javascript:select_bg()" id="bg_btn" title="background"></a>
			<a href="javascript:aumentaPennello()" id="plus_btn" title="plus"></a>
			<a href="javascript:diminuisciPennello()" id="minus_btn" title="minus"></a>
			<a href="javascript:clear()" id="clear_btn" title="clear"></a>		
			<a href="javascript:get_hair()" id="hair_btn" title="get hair"></a>			
		</div>

	</body>
	<script type="text/javascript">
		
	</script>
</html>
