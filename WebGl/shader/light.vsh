attribute vec3 a_vertex;
attribute vec3 a_vertexnormal;
attribute vec2 a_texcoord;

uniform mat4 mv_matrix;
uniform mat4 p_matrix;
uniform mat3 n_matrix;

varying vec2 v_texcoord;
varying vec3 v_transformednormal;
varying vec4 v_position;

void main(void) {
	v_position = mv_matrix * vec4(a_vertex, 1.0);
	gl_Position = p_matrix * v_position;
	v_texcoord = a_texcoord;
	v_transformednormal = n_matrix * a_vertexnormal;
}