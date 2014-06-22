attribute vec3 a_vertex;
uniform mat4 mvp_matrix;

void main(void) {
	gl_Position = mvp_matrix * vec4(a_vertex, 1.0);
}