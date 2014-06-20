uniform mat4 u_mvp_matrix;
attribute vec4 a_vertex;
attribute vec2 a_texcoord;

varying vec2 v_texcoord;

void main()
{
	v_texcoord = a_texcoord;
	gl_Position = u_mvp_matrix * a_vertex;
}