#version 330 core

layout (location = 0) out vec4 color;
uniform sampler2D output_image;

void main()
{
	color = texture(output_image, vec2(gl_FragCoord.xy) / vec2(textureSize(output_image, 0)));
}

        