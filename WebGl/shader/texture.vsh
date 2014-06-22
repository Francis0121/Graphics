attribute vec3 a_vertex;
attribute vec2 a_texcoord;

uniform mat4 mvp_matrix;

varying vec2 v_texcoord;

void main(void) {
	gl_Position = mvp_matrix * vec4(a_vertex, 1.0);
	v_texcoord = a_texcoord;
}