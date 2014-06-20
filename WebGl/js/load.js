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
	
	webgl.gl.clearColor(1.0, 1.0, 0.0, 1.0);
    webgl.gl.enable(webgl.gl.DEPTH_TEST);
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
	webgl.errorHandler('Create Canvas', 1);
};

/**
 * Draw
 */
webgl.drawScreen = function(){
	var gl = webgl.gl;
	var texture_id = webgl.texture_id;
	var shaderProgram = webgl.shaderProgram;
	
	gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
    gl.useProgram(shaderProgram);
    
    mat4.ortho(projection_matrix, -3.0, 3.0, -4.0, 4.0, 0.1, 100.0);		
	mat4.lookAt(view_matrix, [0, 0, 4], [0, 0, 0], [0, 1, 0]);
    mat4.identity(model_matrix);
    
    mat4.multiply(view_model_matrix, view_matrix, model_matrix);
	mat4.multiply(projection_view_model_matrix, projection_matrix, view_model_matrix);
	
    gl.bindBuffer(gl.ARRAY_BUFFER, buffer.cubeVertexPositionBuffer);
    gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

    /*gl.bindBuffer(gl.ARRAY_BUFFER, buffer.cubeVertexTextureCoordBuffer);
    gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, 2, gl.FLOAT, false, 0, 0);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, texture_id);
    gl.uniform1i(shaderProgram.texid_loc, 0);*/

    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffer.cubeVertexIndexBuffer);
   
	gl.uniformMatrix4fv(shaderProgram.mvp_matrix_loc, false, projection_view_model_matrix);
    
	gl.drawElements(gl.TRIANGLES, buffer.cubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
	gl.useProgram(null);
};


