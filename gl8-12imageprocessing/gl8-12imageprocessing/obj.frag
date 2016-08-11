#version 430 core

layout (location = 0) out vec4 color;
layout (binding = 0) uniform sampler2D tex;

void main()
{
	
	vec4 rgba = texture(tex, vec2(1.0, -1.0) * vec2(gl_FragCoord.xy) / vec2(textureSize(tex, 0)));

	color =abs(rgba);
}

        