/**
 * Buffer Initiate
 */
buffer.initBuffer = function(){
	var gl = webgl.gl;

	buffer.vertice();
	
	buffer.texture();
	
	buffer.indecies();	
	
	buffer.normal();
};
/**
 * Vertex Normal Buffer
 */
buffer.normal = function(){
	var gl = webgl.gl;
	buffer.vertexNormalBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, buffer.vertexNormalBuffer);
	var normals = [
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,

	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0,
	   0.0, 0.0, 1.0
	];
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normals), gl.STATIC_DRAW);
	buffer.vertexNormalBuffer.numItems = 20;
};

/**
 * Vertice Buffer Initiate
 */
buffer.vertice = function(){
	var gl = webgl.gl;
	// ~ Top Vertice
	buffer.topPositionBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, buffer.topPositionBuffer);
	var vertices = [
		2.95, 4.05, 0.0,
		0.05, 4.05, 0.0,
		0.05, 2.15, 0.0,
		2.95, 2.15, 0.0,
		
		2.95, 2.05, 0.0,
		0.05, 2.05, 0.0,
		0.05, 0.10, 0.0,
		2.95, 0.10, 0.0,
		
		-0.05, 4.05, 0.0,
		-2.95, 4.05, 0.0,
		-2.95, 2.15, 0.0,
		-0.05, 2.15, 0.0,
		
		-0.05, 2.05, 0.0,
		-2.95, 2.05, 0.0,
		-2.95, 0.10, 0.0,
		-0.05, 0.10, 0.0,
		
		2.95, 0.0, 0.0,
		0.05, 0.0, 0.0,
		-0.05, 0.0, 0.0,
		-2.95, 0.0, 0.0
	];
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
	buffer.topPositionBuffer.numItems = 20;
	// ~ Down Vertice
	buffer.downPositionBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, buffer.downPositionBuffer);
	var vertices = [
		2.95, 0.0, 0.0,
		0.05, 0.0, 0.0,
		0.05, -1.85, 0.0,
		2.95, -1.85, 0.0,
		
		2.95, -1.95, 0.0,
		0.05, -1.95, 0.0,
		0.05, -3.85, 0.0,
		2.95, -3.85, 0.0,
		
		-0.05, 0.0, 0.0,
		-2.95, 0.0, 0.0,
		-2.95, -1.85, 0.0,
		-0.05, -1.85, 0.0,
		
		-0.05, -1.95, 0.0,
		-2.95, -1.95, 0.0,
		-2.95, -3.85, 0.0,
		-0.05, -3.85, 0.0,
		
		2.95, -4.0, 0.0,
		0.05, -4.0, 0.0,
		-0.05, -4.0, 0.0,
		-2.95, -4.0, 0.0
	];
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
	buffer.downPositionBuffer.numItems = 20;
	webgl.errorHandler('Buffer Vertice initiate', 1);
};

/**
 * Texture Buffer initiate 
 */
buffer.texture = function(){
	var gl = webgl.gl;
	
	var xMax = webgl.attribute.xMax, 
		yMax = webgl.attribute.yMax, 
		xMin = webgl.attribute.xMin, 
		yMin = webgl.attribute.yMin;
	
	var texCoordBuffer, texCoordBufferList = new Array();
	var textureCoords = [
     	[
	     	xMax, yMax,	0, 0,		0, 0,		0, 0,
			0, 0,		0, 0,		0, 0,		xMax, yMin,
			0, 0,		xMin, yMax,	0, 0,		0, 0,
			0, 0,		0, 0,		xMin, yMin,	0, 0,
			0, 0,		0, 0,		0, 0,		0, 0
		],
     	[
			xMax, yMax, xMin, yMax, 0, 0,  		0, 0,
			0, 0, 		0, 0,  		xMin, yMin, xMax, yMin,
			yMax, xMax, yMin, xMax, 0, 0,  		0, 0,
			0, 0,  		0, 0,  		yMin, xMin, yMax, xMin
     	],
     	[
			xMax, yMax, 0, 0,  		0, 0,  		xMax, yMin,
			yMax, xMax, 0, 0,  		0, 0,  		yMax, xMin,
			0, 0,  		xMin, yMax, xMin, yMin, 0, 0,
			0, 0,  		yMin, xMax, yMin, xMin, 0, 0
     	],
     	[
			xMax, yMax, 0, 0,  		0, 0,  		xMax, yMin,
			xMax, yMax, xMin, yMax, xMin, yMin, xMax, yMin,
			0, 0,  		xMin, yMax, xMin, yMin, 0, 0,
			xMax, yMax, xMin, yMax, xMin, yMin, xMax, yMin
     	],
     	[
			xMax, yMax, xMin, yMax, xMin, yMin, xMax, yMin,
			xMax, yMax, xMin, yMax, xMin, yMin, xMax, yMin,
			yMax, xMax, yMin, xMax, yMin, xMin, yMax, xMin,
			yMax, xMax, yMin, xMax, yMin, xMin, yMax, xMin
     	],
	];
	
	for(var i=0; i<5; i++){
		texCoordBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, texCoordBuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoords[i]), gl.STATIC_DRAW);
		texCoordBuffer.numItems = 20;
	    texCoordBufferList.push(texCoordBuffer);
	}
	
    buffer.texCoordBufferList = texCoordBufferList;
};

/**
 * Indecies Initiate
 */
buffer.indecies = function(){
	var gl = webgl.gl;
	var indexBuffer, indexBufferList = new Array();
	var indices = 
	[
	 	[
	 	 	0, 9, 14, 14, 7, 0,  // Image
	 	 	7, 14, 19, 19, 16, 7 // Border
	 	],
	 	[
			0, 1, 6, 6, 7, 0,
			8, 9, 14, 14, 15, 8,
			1, 8, 15, 15, 6, 1,
			7, 14, 19, 19, 16, 7
	 	],
	 	[
			0, 9, 10, 10, 3, 0,
			4, 13, 14, 14, 7, 4,
			3, 10, 13, 13, 4, 3,
			7, 14, 19, 19, 16, 7
	 	],
	 	[
			0, 9, 10, 10, 3, 0,
			12, 13, 14, 14, 15, 12,
			4, 5, 6, 6, 7, 4,
			3, 10, 13, 13, 4, 3,
			7, 14, 19, 19, 16, 7,
			5, 12, 15, 15, 6, 5	 	 
	 	],
	 	[
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4,
			8, 9, 10, 10, 11, 8,
			12, 13, 14, 14, 15, 12,
			3, 10, 13, 13, 4, 3,
			7, 14, 19, 19, 16, 7,
			5, 12, 15, 15, 6, 5,
			1, 8, 11, 11, 2, 1	 	 	
	 	]
	];

	for(var i=0; i<5; i++){
		indexBuffer = gl.createBuffer();
	    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
	    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices[i]), gl.STATIC_DRAW);
	    indexBuffer.numItems = indices[i].length;
	    webgl.errorHandler('Indecies '+indices[i].length, 1);
	    indexBufferList.push(indexBuffer);
	}
    
    buffer.indexBufferList = indexBufferList;
    webgl.errorHandler('Indecies Buffer initiate', 1);
};

