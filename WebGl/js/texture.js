/**
 * Texture Initiate
 */
texture.initTexture = function(){
	
    var texList = new Array();
    for(var i=0; i<10; i++){
    	texture.createImage('./image/'+$('select#texture').val()+'/0'+i+'.jpg', texList);
    }
    webgl.texList = texList;
    
    webgl.errorHandler('Create Texture', 1);
};


texture.handleLoadedTexture = function(image) {
	var gl = webgl.gl;
	var textureId = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, textureId);
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
    
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);  
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_LINEAR);
    gl.generateMipmap(gl.TEXTURE_2D);    

    gl.bindTexture(gl.TEXTURE_2D, null);
    webgl.texture_id = textureId;
    webgl.errorHandler('Texture '+ textureId);
};

texture.createImage = function(path, texList){
    var image = new Image();
    image.addEventListener('load', function(){
    	tex = texture.loadTexture(image);
    	texList.push(tex);
    }, false);
    image.src = path;
};

texture.loadTexture = function(image){
	var gl = webgl.gl;
	var tex = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, tex);
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
    
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);  
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_LINEAR);
    gl.generateMipmap(gl.TEXTURE_2D);    

    gl.bindTexture(gl.TEXTURE_2D, null);
    webgl.errorHandler('Image '+ image.src);
    return tex;
};
