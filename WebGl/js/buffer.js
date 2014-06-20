/**
 * Buffer Initiate
 */
buffer.initBuffer = function(){
	var gl = webgl.gl;
	
	// ~ Vertices
	buffer.cubeVertexPositionBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, buffer.cubeVertexPositionBuffer);
	var vertices = [
		// Front face
		1.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 0.0,
		1.0, 0.0, 0.0 ];
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
	buffer.cubeVertexPositionBuffer.numItems = 4;
	
    // ~ Textures
	buffer.cubeVertexTextureCoordBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, buffer.cubeVertexTextureCoordBuffer);
	var textureCoords = [
		// Front face
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0 ];
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoords), gl.STATIC_DRAW);
    buffer.cubeVertexTextureCoordBuffer.numItems = 4
    
    // ~ Index
	buffer.cubeVertexIndexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffer.cubeVertexIndexBuffer);
    var cubeVertexIndices = [
       //Front face
       0, 1, 2,      
       0, 2, 3];
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(cubeVertexIndices), gl.STATIC_DRAW);
    buffer.cubeVertexIndexBuffer.numItems = 6;
};