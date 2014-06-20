if (typeof webgl == 'undefined') {
	webgl = {};
}

$(function() {
	webgl.gl;
	// ~ Javascript Debug Start
	webgl.debug = true;
	if(webgl.debug){
		webgl.error = $('<div class="error"></div>');
		$('body').append(webgl.error);
	}
	//~ Javascript Debug End
	
	webgl.webGLStart();
});

webgl.webGLStart = function(){
	var canvas = document.getElementById('webgl_canvas');
	webgl.init(canvas);
	webgl.errorHandler('Create Canvas', 1);
	
	webgl.texture_id;
	webgl.initTexture();
};

webgl.init = function(canvas){
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
};

webgl.initTexture = function(){
	var gl = webgl.gl;
	
	webgl.texture_id = gl.createTexture();
	webgl.texture_id.image = new Image();
	webgl.texture_id.image.onload = function () {
		gl.bindTexture(gl.TEXTURE_2D, webgl.texture_id);
		
		gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, webgl.texture_id.image);
		
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
		
		gl.bindTexture(gl.TEXTURE_2D, null);
	}
	webgl.texture_id.image.src = 'image/IU_1.jpg';
};
