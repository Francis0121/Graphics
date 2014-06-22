precision mediump float;

varying vec2 v_texcoord;

uniform sampler2D uTexture;

void main(void) {
	gl_FragColor = texture2D(uTexture, v_texcoord);
}