precision mediump float;

varying vec2 v_texcoord;
varying vec3 v_transformednormal;
varying vec4 v_position;

uniform bool uShowSpecularHighlights;
uniform bool uUseLighting;
// Material
uniform float uMaterialShininess;
// Ambient 
uniform vec3 uAmbientColor;
// Point
uniform vec3 uPointLightingLocation;
uniform vec3 uPointLightingSpecularColor;
uniform vec3 uPointLightingDiffuseColor;

uniform sampler2D uTexture;

void main(void) {
	vec3 lightWeighting;
	 if (!uUseLighting) {
		lightWeighting = vec3(1.0, 1.0, 1.0);
	} else {
		vec3 lightDirection = normalize(uPointLightingLocation - v_position.xyz);
		vec3 normal = normalize(v_transformednormal);

		float specularLightWeighting = 0.0;
		if (uShowSpecularHighlights) {
			vec3 eyeDirection = normalize(-v_position.xyz);
			vec3 reflectionDirection = reflect(-lightDirection, normal);
			
			specularLightWeighting = pow(max(dot(reflectionDirection, eyeDirection), 0.0), uMaterialShininess);
		}
	
	    float diffuseLightWeighting = max(dot(normal, lightDirection), 0.0);
	    lightWeighting =  
	    	uAmbientColor
	        + uPointLightingSpecularColor * specularLightWeighting
	        + uPointLightingDiffuseColor * diffuseLightWeighting;
	}
    vec4 fragmentColor = texture2D(uTexture, vec2(v_texcoord.s, v_texcoord.t));
    gl_FragColor = vec4(fragmentColor.rgb * lightWeighting, fragmentColor.a);
}