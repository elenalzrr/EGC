#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 Color;
uniform float time;
out vec3 frag_color;
out vec2 frag_texture;
out vec3 frag_position;
out vec3 frag_normal;
out float noise;

float rand3D(in vec3 co){
    return fract(sin(dot(co.xyz ,vec3(12.9898,78.233,144.7272))) * 43758.5453);
}

float turbulence(vec3 p){
	float w = 50.f;
	float t = -0.5;

	for (float f = 1.0; f <= 10.0; f++) {
		float power = pow(2, f);
		t+= abs(rand3D(vec3(power *p)));
	}
	return t;
}

void main()
{
	frag_color		= Color;
	frag_texture	= v_texture;
	frag_position	= v_position;
	frag_normal		= v_normal; 
	noise = 10.0 *  -0.1 * turbulence(0.8 * v_normal);
	float b = time * 2.0 * rand3D(0.05 * v_position);
	float displacement = +1. * noise + b;
	gl_Position = Projection * View * Model * vec4(v_position + v_normal * displacement, 1.0);
}
 