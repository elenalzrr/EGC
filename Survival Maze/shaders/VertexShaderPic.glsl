#version 430

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

layout(location = 0) out vec3 text_coord;

void main()
{
    text_coord = normalize(v_position);
	gl_Position = Projection * View * Model * vec4(v_position, 1); 
}