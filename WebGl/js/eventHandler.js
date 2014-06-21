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
		span.append('<span class="head">[DEBUG]</span>');
		break;
	default:
		span = $('<span class="default"></span>');
		span.append('<span class="head">[DEFAULT]</span>');
	}

	if(error.message != undefined && error.message != ''){
		message = error.message;
	}
	
	span.append(message);
	webgl.error.append(span).append('<br/>');
};

/**
 * Mouse Down Event
 */
webgl.handleMouseDown = function(){
	webgl.errorHandler('Mouse Down', 1);

};

/**
 * Mouse Up Event
 */
webgl.handleMouseUp = function(){
	if(webgl.attribute.fLoop < 4)
		++webgl.attribute.fLoop;
	else
		webgl.attribute.fLoop = 0
	//.else if(--webgl.attribute.fLoop == -1)
	//	webgl.attribute.fLoop = 4;
	
	webgl.drawScreen();
	webgl.errorHandler('Mouse Up ' + webgl.attribute.fLoop + ' ', 1);	
};

/**
 * Mouse Wheel
 */

webgl.handleMouseWheel = function(event){
	var orthoHeight = webgl.attribute.orthoHeight,
		orthoWidth = webgl.attribute.orthoWidth,
		motionRate = webgl.attribute.motionRate,
		scaleFlag = webgl.attribute.scaleFlag;
	
	scaleFlag = true;
	
	var delta = 0;
	if (!event) 
		event = window.event;
	if (event.wheelDelta) {
		delta = event.wheelDelta/120;
		if (window.opera) 
			delta = -delta;
	} else if (event.detail) 
		delta = -event.detail/3;
	
	if(delta > 0){		
		orthoHeight*=1.1;
		orthoWidth*=1.1;
		if(motionRate < 0.03){
			motionRate += 0.005;
		}
	}else{
		if(orthoHeight > 0.5){
			orthoHeight*=0.9;
			orthoWidth*=0.9;
		}
		if(motionRate > 0.005){
			motionRate -= 0.005;
		}
	}
	
	if( orthoHeight > 4 ){
		scaleFlag = false;
		orthoHeight = 4;
		orthoWidth = 3;
	}
	
	webgl.attribute.orthoHeight = orthoHeight;
	webgl.attribute.orthoWidth = orthoWidth;
	webgl.attribute.motionRate = motionRate;
	webgl.drawScreen();
	
	webgl.errorHandler('Mouse Wheel ', 1);
};
