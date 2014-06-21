/**
 * Load Shader file
 */
shader.getShader = function(gl, id) {
	var shaderScript = document.getElementById(id);
	if (!shaderScript) {
		return null;
	}

	var str = "";
	var k = shaderScript.firstChild;
	while (k) {
		if (k.nodeType == 3) {
			str += k.textContent;
		}
		k = k.nextSibling;
	}

	var shader;
	if (shaderScript.type == 'x-shader/x-fragment') {
		shader = gl.createShader(gl.FRAGMENT_SHADER);
	} else if (shaderScript.type == 'x-shader/x-vertex') {
		shader = gl.createShader(gl.VERTEX_SHADER);
	} else {
		return null;
	}

	gl.shaderSource(shader, str);
	gl.compileShader(shader);

	if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
		alert(gl.getShaderInfoLog(shader));
		return null;
	}

	return shader;
}

/**
 * Shader Initiate
 */
shader.initShader = function(){
	var gl = webgl.gl;
	var shaderProgram = gl.createProgram();
	
	var fragmentShader = shader.getShader(gl, 'shader-fs');
    var vertexShader = shader.getShader(gl, 'shader-vs');

    gl.attachShader(shaderProgram, vertexShader);
    gl.attachShader(shaderProgram, fragmentShader);
    gl.linkProgram(shaderProgram);
    
    if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
    	webgl.errorHandler('Could not initialise shaders', 2);
    }
    
    gl.useProgram(shaderProgram);

    shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, 'a_vertex');
    gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);
    
    shaderProgram.textureCoordAttribute = gl.getAttribLocation(shaderProgram, 'a_texcoord');
    gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);
    
    shaderProgram.mvp_matrix_loc = gl.getUniformLocation(shaderProgram, 'mvp_matrix');
    shaderProgram.texid_loc = gl.getUniformLocation(shaderProgram, 'uTexture');
	
    webgl.shaderProgram = shaderProgram;
	webgl.errorHandler('Link Shader', 1);
};