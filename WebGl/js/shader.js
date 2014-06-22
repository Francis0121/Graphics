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
		
	    // ~ Light
	    webgl.colorShader = colorShader;
	    webgl.errorHandler('Link Color shader', 1);
	    
	    var lightShader = gl.createProgram();
	    var lightVertexShader =  shader.compileShader(gl, 'vertex', data.light.vertex),
	    lightFragmentShader = shader.compileShader(gl, 'fragment', data.light.fragment);
	
	    gl.attachShader(lightShader, lightVertexShader);
	    gl.attachShader(lightShader, lightFragmentShader);
	    gl.linkProgram(lightShader);
	    
	    if (!gl.getProgramParameter(lightShader, gl.LINK_STATUS)) {
	    	webgl.errorHandler('Could not initialise color shader', 2);
	    }
	    gl.useProgram(lightShader);
	    
	    lightShader.vertexPositionAttribute = gl.getAttribLocation(lightShader, 'a_vertex');
	    gl.enableVertexAttribArray(lightShader.vertexPositionAttribute);
	    
	    lightShader.normalPositionAttribute = gl.getAttribLocation(lightShader, 'a_normal');
	    gl.enableVertexAttribArray(lightShader.vertexPositionAttribute);
	    
	    lightShader.mvp_matrix_loc = gl.getUniformLocation(lightShader, 'u_mvp_matrix');
	    lightShader.mv_matrix_loc = gl.getUniformLocation(lightShader, 'u_mv_matrix');
	    lightShader.normal_matrix_loc = gl.getUniformLocation(lightShader, 'u_normal_matrix');
	    
	    lightShader.light_position = gl.getUniformLocation(lightShader, 'u_light_position');
	    lightShader.light_ambient = gl.getUniformLocation(lightShader, 'u_light_ambient');
	    lightShader.light_diffuse = gl.getUniformLocation(lightShader, 'u_light_diffuse');
	    lightShader.light_specular = gl.getUniformLocation(lightShader, 'u_light_specular');
	    
	    lightShader.material_ambient = gl.getUniformLocation(lightShader, 'u_material_ambient');
	    lightShader.material_diffuse = gl.getUniformLocation(lightShader, 'u_material_diffuse');
	    lightShader.material_specular = gl.getUniformLocation(lightShader, 'u_material_specular');
	    lightShader.material_shininess = gl.getUniformLocation(lightShader, 'u_material_shininess');
	    
	    webgl.lightShader = lightShader;
	    webgl.errorHandler('Link Light shader', 1);
	    
	    /** Animate Begin */ 
	    webgl.animate();
	    setTimeout(webgl.onFloatingRestart, 1000);
	});
};