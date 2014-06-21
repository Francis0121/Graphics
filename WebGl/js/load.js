var projection_matrix = mat4.create();
var view_matrix = mat4.create();
var model_matrix = mat4.create();
var view_model_matrix = mat4.create();
var projection_view_model_matrix = mat4.create();

$(function() {
	// ~ Javascript Debug Start
	webgl.debug = true;
	if(webgl.debug){
		webgl.error = $('<div class="error"></div>');
		$('body').append(webgl.error);
	}
	//~ Javascript Debug End
	
	webgl.webGLStart();
});

/**
 * Web GL Start
 */
webgl.webGLStart = function(){
	webgl.init();
	
	shader.initShader();
	buffer.initBuffer();
	texture.initTexture();
	
	webgl.gl.clearColor(1.0, 1.0, 1.0, 1.0);
    webgl.gl.enable(webgl.gl.DEPTH_TEST);
    webgl.attribute = {
    	tLoop : 0, // Top Loop
    	dLoop : 0, // Down Loop
    	fLoop : 0, // Frame Loop
    	// Screen Size
    	scaleFlag : false,
    	orthoWidth : 3.0, 
    	orthoHeight : 4.0,
    	motionRate : 0.03
    };
    setTimeout(webgl.drawScreen, 100);
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
//	canvas.onmousemove = webgl.handleMouseMove;
	
	webgl.errorHandler('Create Canvas', 1);
};

/**
 * Draw
 */
webgl.drawScreen = function(){
	var gl = webgl.gl;
	var shaderProgram = webgl.shaderProgram;
	
	gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
    gl.useProgram(shaderProgram);
    
    // ~ Camera

    //mat4.perspective(projection_matrix, 45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0);	
    mat4.ortho(projection_matrix, -webgl.attribute.orthoWidth-0.1, webgl.attribute.orthoWidth+0.1, -webgl.attribute.orthoHeight, webgl.attribute.orthoHeight+0.2, 0.1, 100.0);
	mat4.lookAt(view_matrix, [0, 0, 1], [0, 0, 0], [0, 1, 0]);
    mat4.identity(model_matrix);
    
    // ~ Matrix
    
    mat4.multiply(view_model_matrix, view_matrix, model_matrix);
	mat4.multiply(projection_view_model_matrix, projection_matrix, view_model_matrix);
	
	webgl.attribute.tLoop = webgl.attribute.fLoop;
	webgl.attribute.dLoop = webgl.attribute.fLoop;
	
	for(var i=0; i<5; i++){
		webgl.drawTop(gl, shaderProgram);
		if(++webgl.attribute.tLoop == 5)
			webgl.attribute.tLoop = 0;
		
		webgl.drawDown(gl, shaderProgram);
		if(--webgl.attribute.dLoop == -1)
			webgl.attribute.dLoop = 4;
	}
	
	
	gl.useProgram(null);
};

webgl.drawTop = function(gl, shaderProgram){
	var tLoop = webgl.attribute.tLoop;
	var size = buffer.indexBufferList[tLoop].numItems;
	
	for(var i=0; i<(size/12); i++){	
		gl.activeTexture(gl.TEXTURE0);
		
	    gl.bindTexture(gl.TEXTURE_2D, webgl.texList[i]);
	    gl.uniform1i(shaderProgram.texid_loc, 0);
	    
	    gl.bindBuffer(gl.ARRAY_BUFFER, buffer.topPositionBuffer);
	    gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0 );
	
	    gl.bindBuffer(gl.ARRAY_BUFFER, buffer.texCoordBufferList[tLoop]);	
	    gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, 2, gl.FLOAT, false, 0, 0);

    	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffer.indexBufferList[tLoop]);
		gl.uniformMatrix4fv(shaderProgram.mvp_matrix_loc, false, projection_view_model_matrix);
		gl.drawElements(gl.TRIANGLES, 6, gl.UNSIGNED_SHORT, i*12);
	}
};

webgl.drawDown = function(gl, shaderProgram){
	var dLoop = webgl.attribute.dLoop;
	var size = buffer.indexBufferList[dLoop].numItems;
	
	for(var i=0; i<(size/12); i++){	
		gl.activeTexture(gl.TEXTURE0);
		
	    gl.bindTexture(gl.TEXTURE_2D, webgl.texList[5-i]);
	    gl.uniform1i(shaderProgram.texid_loc, 0);
	    
	    gl.bindBuffer(gl.ARRAY_BUFFER, buffer.downPositionBuffer);
	    gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0 );
	
	    gl.bindBuffer(gl.ARRAY_BUFFER, buffer.texCoordBufferList[dLoop]);	
	    gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, 2, gl.FLOAT, false, 0, 0);

    	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffer.indexBufferList[dLoop]);
		gl.uniformMatrix4fv(shaderProgram.mvp_matrix_loc, false, projection_view_model_matrix);
		gl.drawElements(gl.TRIANGLES, 6, gl.UNSIGNED_SHORT, i*12);
	}
};

