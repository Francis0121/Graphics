var projection_matrix = mat4.create();
var view_matrix = mat4.create();
var model_matrix = mat4.create();
var view_model_matrix = mat4.create();
var projection_view_model_matrix = mat4.create();
var matStack = new Array();
//~ Final Variable
webgl.ROTATION_STATUS = {
	STOP : 0,
	DOWN : 1,
	UP : 2
};

webgl.INTRINSIC = {
	ORTHO : 0,
	PERSPECTIVE : 1
};

webgl.ERROR_STATUS = {
	DEBUG : 2,
	INFO : 1,
	DEFAULT : 0,
};

webgl.attribute = {
	tLoop : 0, // Top Loop
	dLoop : 0, // Down Loop
	fLoop : 0, // Frame Loop
	dragging : false,
	// Screen Size
	scaling : false,
	orthoWidth : 3.0, 
	orthoHeight : 4.0,
	// Screen move
	motionRate : 0.03,
	lookX : 0.0,
	lookY : 0.0,
	bPosX : 0.0, // Before Position X 
	bPosY : 0.0,  // Before Position Y
	// Rotation
	isTop : webgl.ROTATION_STATUS.STOP,
	isDown : webgl.ROTATION_STATUS.STOP,
	topAngle : 0.0,
	downAngle : 0.0,
	// Floating
	floating : true,
	fSpeed1 : 0.001,
	fSpeed2 : 0.002,
	xMax : 0.8, 
	yMax : 0.9, 
	xMin : 0.3, 
	yMin : 0.1,
	// RandomList
	randTexTopIndex : new Array(),
	randTexDownIndex : new Array(),
	// Other
	intrinsic : webgl.INTRINSIC.ORTHO
};

$(function() {
	
	// ~ Javascript Debug Start
	webgl.debug = true;
	webgl.debugMode = webgl.ERROR_STATUS.DEFAULT;
	if(webgl.debug){
		webgl.error = $('<div class="error"></div>');
		$('body').append(webgl.error);
	}
	//~ Javascript Debug End
	
	webgl.webGLStart();
	
	webgl.externalEvent();
});

/**
 * Web GL Start
 */
webgl.webGLStart = function(){
	 
	webgl.init();
	
	buffer.initBuffer();
	texture.initTexture();
	
	webgl.gl.clearColor(1.0, 1.0, 1.0, 1.0);
    webgl.gl.enable(webgl.gl.DEPTH_TEST);
      
    webgl.makeRandTexIndex();
    
    shader.loadingAfterStart();
};

webgl.makeRandTexIndex = function(){
	webgl.attribute.randTexTopIndex = new Array();
	webgl.attribute.randTexDownIndex = new Array();
	
	while(webgl.attribute.randTexTopIndex.length !=6){
		var value = Math.floor(Math.random() * 10);
		if(jQuery.inArray(value, webgl.attribute.randTexTopIndex) == -1){
			webgl.attribute.randTexTopIndex.push(value);
		}
	}
	
	while(webgl.attribute.randTexDownIndex.length !=6){
		var value = Math.floor(Math.random() * 10);
		if(jQuery.inArray(value, webgl.attribute.randTexDownIndex) == -1){
			webgl.attribute.randTexDownIndex.push(value);
		}
	}
};

/**
 * Animate
 */
webgl.animate = function(){
	requestAnimFrame(webgl.animate);
	webgl.rotationEffect();
	webgl.drawScreen();
};

/**
 * Web GL initiate
 */
webgl.init = function(){
	var canvas = document.getElementById('webgl_canvas');
	try {
		webgl.gl = canvas.getContext('experimental-webgl');
		webgl.gl.viewportWidth = canvas.width;
		webgl.gl.viewportHeight = canvas.height;
	} catch (error) {
		webgl.errorHandler(error, 2);
	}
	
	if (!webgl.gl) {
		webgl.errorHandler('Could not initialize WebGL, sorry', 2);
	}
	
	canvas.onmousedown = webgl.handleMouseDown;
	canvas.onmouseup = webgl.handleMouseUp;
	canvas.onmousewheel = webgl.handleMouseWheel;
	canvas.onmousemove = webgl.handleMouseMove;
	
	webgl.errorHandler('Create Canvas', 1);
};

/**
 * Draw
 */
webgl.drawScreen = function(){
	var gl = webgl.gl;
	
	gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
    // ~ Camera
    mat4.identity(projection_matrix);
    mat4.identity(view_matrix);

    if(webgl.attribute.intrinsic == webgl.INTRINSIC.ORTHO){
		mat4.ortho(projection_matrix, 
			-webgl.attribute.orthoWidth-0.1, 
			webgl.attribute.orthoWidth+0.1, 
			-webgl.attribute.orthoHeight, 
			webgl.attribute.orthoHeight+0.2, 
			0.1, 100.0);
		mat4.lookAt(view_matrix, 
			[webgl.attribute.lookX, webgl.attribute.lookY, 1], 
			[webgl.attribute.lookX, webgl.attribute.lookY, 0], 
			[0, 1, 0]);
    }else if(webgl.attribute.intrinsic == webgl.INTRINSIC.PERSPECTIVE){
    	mat4.perspective(projection_matrix, 9, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0);		
    	mat4.lookAt(view_matrix, [4, 0, 1], [0, 0, 0], [0, 1, 0]);
    }
    	
    mat4.identity(model_matrix);
    
    // ~ Matrix
    
	webgl.attribute.tLoop = webgl.attribute.fLoop;
	webgl.attribute.dLoop = webgl.attribute.fLoop;
	
	mat4.identity(projection_view_model_matrix);
	
	for(var i=0; i<5; i++){
		// ~ Top
		model_matrix = mat4.create();
		view_model_matrix = mat4.create();
		projection_view_model_matrix = mat4.create();
		
		mat4.translate(model_matrix, model_matrix, [0, 0, -i*5]);
		if( webgl.attribute.isTop != webgl.ROTATION_STATUS.STOP && i == 0){
			mat4.rotateX(model_matrix, model_matrix, webgl.attribute.topAngle*Math.PI/180); 
		}
		
		mat4.multiply(view_model_matrix, view_matrix, model_matrix);
		mat4.multiply(projection_view_model_matrix, projection_matrix, view_model_matrix);
		
		webgl.drawTop(gl);
		if(++webgl.attribute.tLoop == 5)
			webgl.attribute.tLoop = 0;
		
		// ~ Down
		model_matrix = mat4.create();
		view_model_matrix = mat4.create();
		projection_view_model_matrix = mat4.create();
		
		mat4.translate(model_matrix, model_matrix, [0, 0, -i*5]);
		if(webgl.attribute.isDown != webgl.ROTATION_STATUS.STOP && i == 0){
			mat4.rotateX(model_matrix, model_matrix, webgl.attribute.downAngle*Math.PI/180);
		}
		
		mat4.multiply(view_model_matrix, view_matrix, model_matrix);
		mat4.multiply(projection_view_model_matrix, projection_matrix, view_model_matrix);
		
		webgl.drawDown(gl);
		if(--webgl.attribute.dLoop == -1)
			webgl.attribute.dLoop = 4;
		
	}
	
	if(webgl.attribute.scaling){
		$('canvas').css('cursor', 'pointer');
	}else{
		$('canvas').css('cursor', 'default');
	}
	$('input#motionRate').val(webgl.attribute.motionRate);
};

webgl.drawTop = function(gl){
	var textureShader = webgl.textureShader;
	var colorShader = webgl.colorShader;
	
	var tLoop = webgl.attribute.tLoop;
	var size = buffer.indexBufferList[tLoop].numItems;

	gl.useProgram(colorShader);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, buffer.topPositionBuffer);
    gl.vertexAttribPointer(colorShader.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0 );
	
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffer.indexBufferList[tLoop]);
    gl.uniformMatrix4fv(colorShader.mvp_matrix_loc, false, projection_view_model_matrix);
    gl.drawElements(gl.TRIANGLES, size/2, gl.UNSIGNED_SHORT, size);
    
    gl.useProgram(null);
    
	gl.useProgram(textureShader);
	for(var i=0; i<(size/12); i++){	
		gl.activeTexture(gl.TEXTURE0);
		
	    gl.bindTexture(gl.TEXTURE_2D, webgl.texList[webgl.attribute.randTexTopIndex[i]]);
	    gl.uniform1i(textureShader.texid_loc, 0);
	    
	    gl.bindBuffer(gl.ARRAY_BUFFER, buffer.topPositionBuffer);
	    gl.vertexAttribPointer(textureShader.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0 );
	
	    gl.bindBuffer(gl.ARRAY_BUFFER, buffer.texCoordBufferList[tLoop]);	
	    gl.vertexAttribPointer(textureShader.textureCoordAttribute, 2, gl.FLOAT, false, 0, 0);

    	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffer.indexBufferList[tLoop]);
		gl.uniformMatrix4fv(textureShader.mvp_matrix_loc, false, projection_view_model_matrix);
		gl.drawElements(gl.TRIANGLES, 6, gl.UNSIGNED_SHORT, i*12);
	}
	gl.useProgram(null);
};

webgl.drawDown = function(gl){
	var textureShader = webgl.textureShader;
	var colorShader = webgl.colorShader;
	
	var dLoop = 4-webgl.attribute.dLoop;
	var size = buffer.indexBufferList[dLoop].numItems;
	
	gl.useProgram(colorShader);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, buffer.downPositionBuffer);
    gl.vertexAttribPointer(colorShader.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0 );
	
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffer.indexBufferList[dLoop]);
    gl.uniformMatrix4fv(colorShader.mvp_matrix_loc, false, projection_view_model_matrix);
    gl.drawElements(gl.TRIANGLES, size/2, gl.UNSIGNED_SHORT, size);
    
    gl.useProgram(null);
	
	gl.useProgram(textureShader);
	for(var i=0; i<(size/12); i++){	
		gl.activeTexture(gl.TEXTURE0);
		
	    gl.bindTexture(gl.TEXTURE_2D, webgl.texList[webgl.attribute.randTexDownIndex[i]]);
	    gl.uniform1i(textureShader.texid_loc, 0);
	    
	    gl.bindBuffer(gl.ARRAY_BUFFER, buffer.downPositionBuffer);
	    gl.vertexAttribPointer(textureShader.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0 );
	
	    gl.bindBuffer(gl.ARRAY_BUFFER, buffer.texCoordBufferList[dLoop]);	
	    gl.vertexAttribPointer(textureShader.textureCoordAttribute, 2, gl.FLOAT, false, 0, 0);

    	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffer.indexBufferList[dLoop]);
		gl.uniformMatrix4fv(textureShader.mvp_matrix_loc, false, projection_view_model_matrix);
		gl.drawElements(gl.TRIANGLES, 6, gl.UNSIGNED_SHORT, i*12);
	}
	gl.useProgram(null);
};

