var canvas, ctx, canvas2, ctx2, flag = false,
prevX = 0,
currX = 0,
prevY = 0,
currY = 0,
currX_for_crop=0,
currY_for_crop=0,
dot_flag = false,
fg=true,
bg=false,
green='#00ff00',
red='#ff0000',
color=green;
var dimensionePennello = 1;

var calcolato=false; //true = è già stata eseguita una segmentazione
var image_canvas_2 = new Image(); //Mantiene il risultato, una volta eseguita la segmentazione

function init() {
    canvas = document.getElementById('myCanvas');
    ctx = canvas.getContext("2d");
    canvas2 = document.getElementById('myCanvas2');
    ctx2 = canvas2.getContext("2d");
    w = canvas.width;
    h = canvas.height;
    dimensionePennello = 1;
    
	image_canvas_2 = new Image();	
	image_canvas_2.onload = function(){
		ctx2.drawImage(image_canvas_2,0,0);
	};		
	
    canvas.addEventListener("mousemove", function (e) {
    	if(bg)
    		$('#myCanvas').css( 'cursor', 'url(images/cursor_red.png), auto' );
    	if(fg)
    		$('#myCanvas').css( 'cursor', 'url(images/cursor_green.png), auto' );
    	
        	findxy('move', e);
        //	findxy_for_crop(e);
        //	 cloneCanvas();
        
       
    }, false);
    canvas.addEventListener("mousedown", function (e) {
        findxy('down', e);
    }, false);
    canvas.addEventListener("mouseup", function (e) {
        findxy('up', e);
    }, false);
    canvas.addEventListener("mouseout", function (e) {
        findxy('out', e);
	//	if(!calcolato)
     //   	erase('myCanvas2');
     //   else
      //  	show_result();
    }, false);
}

function select_fg(){
	fg=true;
	bg=false;
	color=green;
}

function select_bg(){
	bg=true;
	fg=false;
	color=red;
}

function clear(){
	erase('myCanvas');
	calcolato=false;
	erase('myCanvas2');
	dimensionePennello = 1;
}

function findxy_for_crop(e){
	currX_for_crop = e.clientX - canvas.offsetLeft;
    currY_for_crop = e.clientY - canvas.offsetTop;
}

function findxy(res, e) {
	
   if (res == 'down') {
        prevX = currX;
        prevY = currY;
        currX = e.clientX - canvas.offsetLeft;
        currY = e.clientY - canvas.offsetTop;

        flag = true;
        dot_flag = true;
        if (dot_flag) {
            ctx.beginPath();
            ctx.fillStyle = color;
            ctx.fillRect(currX, currY, 1, 1);
            ctx.closePath();
            dot_flag = false;
        }
    }
    if (res == 'up' || res == "out") {
        flag = false;
    }
    if (res == 'move') {
        if (flag) {
            prevX = currX;
            prevY = currY;
            currX = e.clientX - canvas.offsetLeft;
            currY = e.clientY - canvas.offsetTop;
            draw();
        }
    }
}

function draw() {	
   
    ctx.beginPath();
     ctx.lineWidth = dimensionePennello;
    ctx.moveTo(prevX, prevY);
    ctx.lineTo(currX, currY);
    ctx.strokeStyle = color;
    
    ctx.stroke();
    ctx.closePath();
}

function erase(id) {
	var can=document.getElementById(id);
    var con = can.getContext('2d');
    con.clearRect(0, 0, w, h);
}

//Modifica la dimensione del pennello
function aumentaPennello(){
	dimensionePennello = dimensionePennello +1;
}

function diminuisciPennello(){
		dimensionePennello = dimensionePennello -1;
		if(dimensionePennello <= 0){
			dimensionePennello = 1;
		}
		
}

/*
 * Salva la mappa estratta dal contesto della prima canvas
 */
function save_map() {
	var canvasData = canvas.toDataURL("image/png");
	var ajax = new XMLHttpRequest();
	$.post('php/save_map.php',{'img_data':canvasData});	
}

/*
 * Mostra nella seconda canvas lo zoom della prima 
 */
function cloneCanvas() {	
    var context2 = canvas2.getContext('2d');
    
	//var canvas3=document.getElementById('myCanvas3');
    //var context3 = canvas2.getContext('2d');
    //set dimensions
    canvas2.width = canvas.width;
    canvas2.height = canvas.height;

    //apply the old canvas to the new one
    //context2.drawImage(canvas, 0, 0);
	var sourceX = currX_for_crop-50;
    var sourceY = currY_for_crop-50;
    var sourceWidth = 100;
    var sourceHeight = 100;
    var destWidth = 500;
    var destHeight = 500;
    var destX = 0;
    var destY = 0;
    
    var imageObj = new Image();
	imageObj.src =$('#canvas_container_1').attr('bg_path');
    context2.drawImage(imageObj, sourceX, sourceY, sourceWidth, sourceHeight, destX, destY, destWidth, destHeight);
    context2.drawImage(canvas, sourceX, sourceY, sourceWidth, sourceHeight, destX, destY, destWidth, destHeight);
  	if(fg)
  		imageObj.src='images/cursor_green_big.png';
  	if(bg)
  		imageObj.src='images/cursor_red_big.png';
  	context2.drawImage(imageObj,0,0,50,50,250,250,50,50);
}

/*
 * Esegue la segmentazione e mostra il risultato nella seconda canvas
 */
function get_hair(){
	$('#container').append('<img id="loading_image" src="images/loading.gif" width="100" height="100">');
	$.when(save_map()).then(function(){
		$.ajax({
			  url:'php/get_hair.php'
			}).done(function(out){
//alert(out);
				image_canvas_2.src = out;
				$('#loading_image').remove();
			});
	});
}

/*
 * Upload del risultato al DB
 */
function upload_result(){
	$('#container').append('<img id="loading_image" src="images/loading.gif" width="100" height="100">');
	$.when(save_map()).then(function(){
		$.ajax({
			  url:'php/def_result.php'
			}).done(function(out){
				image_canvas_2.src =out;
				$('#loading_image').remove();
			});
	});
}

function show_result(){
	console.log(image_canvas_2.src);
	calcolato=true;
    ctx2.drawImage(image_canvas_2,0,0);
	$('#test').text('');
}