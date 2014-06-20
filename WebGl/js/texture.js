/**
 * Texture Initiate
 */
texture.initTexture = function(){
	var gl = webgl.gl;
	var texture_id = webgl.texture_id;
	
	texture_id = gl.createTexture();
    texture_id.image = new Image();
	//texture_id.image = document.createElementNS('http://www.w3.org/1999/xhtml','image');
    texture_id.image.onload = function () {
    	gl.bindTexture(gl.TEXTURE_2D, texture_id);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, texture_id.image);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.bindTexture(gl.TEXTURE_2D, null);
    }

    texture_id.image.src = './image/IU_1.jpg';
	webgl.errorHandler('Create Texture', 1);
};
