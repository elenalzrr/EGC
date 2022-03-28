#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;
 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function

	vec4 col1 = texture2D(texture_1, texcoord);
	vec4 col2 = texture2D(texture_2, texcoord);

	//out_color = col1;
	out_color = mix(col1, col2, .5f);
	if (out_color.a < 0.5f){
		discard;
	}
}