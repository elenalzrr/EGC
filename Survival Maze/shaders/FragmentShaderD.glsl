#version 330

in vec3 frag_normal;
in vec3 frag_color;
in vec3 frag_position;
in vec2 frag_texture;
in float noise;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec3 out_texture;

void main()
{
	out_color = vec4(frag_normal * noise, 1);

}