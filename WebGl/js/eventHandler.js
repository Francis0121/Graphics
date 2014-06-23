webgl.errorHandler = function(error, mode){
	if(!webgl.debug){
		return;
	}
	
	var span, message=error;
	switch (mode) {
	case 1:
		span = $('<span class="info"></span>');
		span.append('<span class="head">[INFO]</span>');
		break;
	case 2:
		span = $('<span class="debug"></span>');
		span.append('<span class="head">[WARN]</span>');
		break;
	default:
		span = $('<span class="default"></span>');
		span.append('<span class="head">[DEFAULT]</span>');
	}

	if(error.message != undefined && error.message != ''){
		message = error.message;
	}
	
	switch(webgl.debugMode){
	case webgl.ERROR_STATUS.DEBUG:
		if(	mode == webgl.ERROR_STATUS.DEBUG ){
			span.append(message);
			webgl.error.append(span).append('<br/>');
		}
		break;
	case webgl.ERROR_STATUS.INFO:
		if(	mode == webgl.ERROR_STATUS.INFO ||
			mode == webgl.ERROR_STATUS.DEBUG ){
			span.append(message);
			webgl.error.append(span).append('<br/>');
		}
		break;
	case webgl.ERROR_STATUS.DEFAULT:
		span.append(message);
		webgl.error.append(span).append('<br/>');
		break;
	}
};

/**
 * Mouse Down Event
 */
webgl.handleMouseDown = function(){
	if(webgl.attribute.intrinsic == webgl.INTRINSIC.PERSPECTIVE){
		return;
	}
	if(!webgl.attribute.dragging){		
		webgl.attribute.dragging = true;
	}
	webgl.errorHandler('Mouse Down', 1);
};

/**
 * Mouse Up Event
 */
webgl.handleMouseUp = function(event){
	if(webgl.attribute.intrinsic == webgl.INTRINSIC.PERSPECTIVE){
		return;
	}
	if(!webgl.attribute.scaling){
		webgl.errorHandler('Height='+webgl.gl.viewportHeight/2);
		if(webgl.gl.viewportHeight/2 > event.layerY){
			webgl.errorHandler('PageY top=' + event.layerY);
			webgl.attribute.isTop = webgl.ROTATION_STATUS.DOWN;
			webgl.attribute.topAngle = 0.0;
		}else{
			webgl.errorHandler('PageY down=' + event.layerY);
			webgl.attribute.isDown = webgl.ROTATION_STATUS.DOWN;
			webgl.attribute.downAngle = 0.0;
		}
	}
	
	if(webgl.attribute.dragging){
		webgl.attribute.dragging = false;		
	}
	
	if(webgl.attribute.floating && !webgl.attribute.scaling){
		
		webgl.attribute.xMax = 0.8;
		webgl.attribute.yMax = 0.9;
		webgl.attribute.xMin = 0.2;
		webgl.attribute.yMin = 0.3;
		buffer.texture();

		webgl.attribute.floating = false;
		setTimeout(webgl.onFloatingRestart, 3000);
	}
	
	webgl.errorHandler('Mouse Up ' + webgl.attribute.fLoop + ' ', 1);	
};

/**
 * Mouse Wheel
 */
webgl.handleMouseWheel = function(event){
	if(webgl.attribute.intrinsic == webgl.INTRINSIC.PERSPECTIVE){
		return;
	}
	var orthoHeight = webgl.attribute.orthoHeight,
		orthoWidth = webgl.attribute.orthoWidth,
		motionRate = webgl.attribute.motionRate,
		scaling = webgl.attribute.scaling,
		zoom = webgl.attribute.zoom;
	
	scaling = true;
	
	var delta = 0;
	if (!event) 
		event = window.event;
	if (event.wheelDelta) {
		delta = event.wheelDelta/120;
		if (window.opera) 
			delta = -delta;
	} else if (event.detail) 
		delta = -event.detail/3;
	
	if(webgl.attribute.scalingMode == webgl.SCALING_MODE.CAMERA){
		
		if(delta > 0){		
			orthoHeight*=1.1;
			orthoWidth*=1.1;
		}else{
			if(orthoHeight > 0.5){
				orthoHeight*=0.9;
				orthoWidth*=0.9;
			}
		}
		
		if( orthoHeight > 4 ){
			scaling = false;
			orthoHeight = 4;
			orthoWidth = 3;
			webgl.attribute.lookX = 0.0;
			webgl.attribute.lookY = 0.0;
		}
	}else if(webgl.attribute.scalingMode == webgl.SCALING_MODE.SCALE){
		if(delta > 0){		
			zoom += 0.2;
		}else{
			zoom -= 0.2;
		}
		
		if(zoom < 1){
			zoom = 1;
			scaling = false;
			webgl.attribute.lookX = 0.0;
			webgl.attribute.lookY = 0.0;
		}
	}
	
	
	webgl.attribute.orthoHeight = orthoHeight;
	webgl.attribute.orthoWidth = orthoWidth;
	webgl.attribute.motionRate = motionRate;
	webgl.attribute.scaling = scaling;
	webgl.attribute.zoom = zoom;
	webgl.drawScreen();
	
//	webgl.errorHandler('Mouse Wheel ', 1);
};

/**
 * Mouse Move
 */
webgl.handleMouseMove = function(event){
	if(webgl.attribute.intrinsic == webgl.INTRINSIC.PERSPECTIVE){
		return;
	}
	var lookX = webgl.attribute.lookX,
		lookY = webgl.attribute.lookY,
		bPosX = webgl.attribute.bPosX,
		bPosY = webgl.attribute.bPosY,
		motionRate = webgl.attribute.motionRate;
		
	if(webgl.attribute.scaling && webgl.attribute.dragging){

		if(bPosX < event.layerX){
			lookX-=motionRate;
		}else{
			lookX+=motionRate;
		}

		if(bPosY > event.layerY){
			lookY-=motionRate;
		}else{
			lookY+=motionRate;
		}

		bPosX = event.layerX;
		bPosY = event.layerY;

		webgl.attribute.lookX = lookX;
		webgl.attribute.lookY = lookY;
		webgl.attribute.bPosX = bPosX;
		webgl.attribute.bPosY = bPosY;

//		webgl.errorHandler('Mouse Move X='+event.pageX+ 'Y='+event.pageY, 1);
//		webgl.errorHandler('Look X='+lookY+ 'Y='+lookX, 1);
		
		webgl.drawScreen();
	}

};

webgl.rotationEffect = function(){
	if(webgl.attribute.intrinsic == webgl.INTRINSIC.PERSPECTIVE){
		return;
	}
	var isTop = webgl.attribute.isTop,
		isDown = webgl.attribute.isDown,
		topAngle = webgl.attribute.topAngle,
		downAngle = webgl.attribute.downAngle,
		fLoop = webgl.attribute.fLoop;
	
	if(isTop == webgl.ROTATION_STATUS.DOWN){
		webgl.errorHandler('isTop='+isTop);
		if(topAngle < 45){
			topAngle += 5.0;
		}else if(topAngle < 90){
			topAngle += 8.0;
		}else{
			downAngle = 90;
			isDown = webgl.ROTATION_STATUS.UP;
			isTop = webgl.ROTATION_STATUS.STOP;
			if(++fLoop == 5){
				fLoop = 0;
			}
			webgl.errorHandler('fLoop++');
		}
	}else if(isTop == webgl.ROTATION_STATUS.UP){
		if(topAngle > 45 ){
			topAngle -= 8.0;
		}else if(topAngle > 0){
			topAngle -= 5.0;
		}else{
			isTop = webgl.ROTATION_STATUS.STOP;
		}
	}else if(isDown == webgl.ROTATION_STATUS.DOWN){
		webgl.errorHandler('isDown='+isDown);
		if(downAngle < 90){
			downAngle += 5.0;
		}else if(downAngle < 45){
			downAngle += 8.0;
		}else{
			topAngle = 90;
			isTop = webgl.ROTATION_STATUS.UP;
			isDown = webgl.ROTATION_STATUS.STOP;
			if(--fLoop == -1){
				fLoop = 4;
			}
			webgl.errorHandler('fLoop--');
		}
	}else if(isDown == webgl.ROTATION_STATUS.UP){
		if(downAngle > 45 ){
			downAngle -= 8.0;
		}else if(downAngle > 0){
			downAngle -= 5.0;	
		}else{
			isDown = webgl.ROTATION_STATUS.STOP;
		}
	}
	webgl.attribute.isTop = isTop;
	webgl.attribute.isDown = isDown;
	webgl.attribute.topAngle = topAngle;
	webgl.attribute.downAngle = downAngle;
	webgl.attribute.fLoop = fLoop;
};



webgl.onFloatingRestart = function(){
	webgl.attribute.floating = true;
	setTimeout(webgl.onXdecrease, 10);
	setTimeout(webgl.onYincrease, 10);
};

webgl.onXdecrease = function(){
	if(webgl.attribute.scaling){
		return;
	}
	webgl.attribute.xMin -= webgl.attribute.fSpeed1;
	webgl.attribute.xMax -= webgl.attribute.fSpeed1;

	buffer.texture();
	
	if(webgl.attribute.floating){
		if(webgl.attribute.xMin < 0.05){
			setTimeout(webgl.onXincrease, 500);
		}else{
			setTimeout(webgl.onXdecrease, 30);
		}
	}
};

webgl.onXincrease = function(){
	if(webgl.attribute.scaling){
		return;
	}
	webgl.attribute.xMin += webgl.attribute.fSpeed1;
	webgl.attribute.xMax += webgl.attribute.fSpeed1;

	buffer.texture();
	
	if(webgl.attribute.floating){
		if(webgl.attribute.xMax > 0.95 ){
			setTimeout(webgl.onXdecrease, 500);
		}else{
			setTimeout(webgl.onXincrease, 30);
		}
	}
}

webgl.onYdecrease = function(){
	if(webgl.attribute.scaling){
		return;
	}
	webgl.attribute.yMin -= webgl.attribute.fSpeed2;
	webgl.attribute.yMax -= webgl.attribute.fSpeed2;

	buffer.texture();

	if(webgl.attribute.floating){
		if(webgl.attribute.yMin < 0.05 ){
			setTimeout(webgl.onYincrease, 500);
		}else{
			setTimeout(webgl.onYdecrease, 30);
		}
	}
}

webgl.onYincrease = function(){
	if(webgl.attribute.scaling){
		return;
	}
	webgl.attribute.yMin += webgl.attribute.fSpeed2;
	webgl.attribute.yMax += webgl.attribute.fSpeed2;

	buffer.texture();

	if(webgl.attribute.floating){
		if(webgl.attribute.yMax > 0.95 ){
			setTimeout(webgl.onYdecrease, 500);
		}else{
			setTimeout(webgl.onYincrease, 30);
		}
	}
}
