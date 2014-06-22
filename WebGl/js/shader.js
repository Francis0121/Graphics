/**
 * Compile Shader file
 */
shader.compileShader = function(gl, type, str) {
	var tempShader;
	if (type == 'fragment') {
		tempShader = gl.createShader(gl.FRAGMENT_SHADER);
	} else if (type == 'vertex') {
		tempShader = gl.createShader(gl.VERTEX_SHADER);
	} else {
		return null;
	}

	gl.shaderSource(tempShader, str);
	gl.compileShader(tempShader);

	if (!gl.getShaderParameter(tempShader, gl.COMPILE_STATUS)) {
		alert(gl.getShaderInfoLog(tempShader));
		return null;
	}

	return tempShader;
}

/**
 * Load external shader file and link between fragment shader and vertex shader.
 * 
 * It is a very important! After Shader is loading. Animate Begins.
 */
shader.loadingAfterStart = function(){
	SHADER_LOADER.load(function (data){
		/** Shader is Loading */
		// ~ Texture Shader
		var gl = webgl.gl;
		var textureShader = gl.createProgram();
		var texVertexShader =  shader.compileShader(gl, 'vertex', data.texture.vertex),
			texFragmentShader = shader.compileShader(gl, 'fragment', data.texture.fragment);
		
		gl.attachShader(textureShader, texVertexShader);
	    gl.attachShader(textureShader, texFragmentShader);
	    gl.linkProgram(textureShader);
	    
	    if (!gl.getProgramParameter(textureShader, gl.LINK_STATUS)) {
	    	webgl.errorHandler('Could not initialise shaders', 2);
	    }
	    
	    gl.useProgram(textureShader);
	
	    textureShader.vertexPositionAttribute = gl.getAttribLocation(textureShader, 'a_vertex');
	    gl.enableVertexAttribArray(textureShader.vertexPositionAttribute);
	    
	    textureShader.textureCoordAttribute = gl.getAttribLocation(textureShader, 'a_texcoord');
	    gl.enableVertexAttribArray(textureShader.textureCoordAttribute);
	    
	    textureShader.mvp_matrix_loc = gl.getUniformLocation(textureShader, 'mvp_matrix');
	    textureShader.texid_loc = gl.getUniformLocation(textureShader, 'uTexture');
		
	    webgl.textureShader = textureShader;
	    webgl.errorHandler('Link Texture shader', 1);
		
	    // ~ Only White Color Shader
	    var colorShader = gl.createProgram();
		var colorVertexShader =  shader.compileShader(gl, 'vertex', data.color.vertex),
			colorFragmentShader = shader.compileShader(gl, 'fragment', data.color.fragment);
		
	    gl.attachShader(colorShader, colorVertexShader);
	    gl.attachShader(colorShader, colorFragmentShader);
	    gl.linkProgram(colorShader);
	    
	    if (!gl.getProgramParameter(colorShader, gl.LINK_STATUS)) {
	    	webgl.errorHandler('Could not initialise color shader', 2);
	    }
	    gl.useProgram(colorShader);
	
	    colorShader.vertexPositionAttribute = gl.getAttribLocation(colorShader, 'a_vertex');
	    gl.enableVertexAttribArray(colorShader.vertexPositionAttribute);
	    
	    colorShader.mvp_matrix_loc = gl.getUniformLocation(colorShader, 'mvp_matrix');
		
	    webgl.colorShader = colorShader;
	    webgl.errorHandler('Link Color shader', 1);
	    
	    /** Animate Begin */ 
	    webgl.animate();
	    setTimeout(webgl.onFloatingRestart, 1000);
	});
};