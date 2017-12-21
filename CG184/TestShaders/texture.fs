#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float mixValue;
uniform bool textured;

// texture samplers
uniform sampler2D DiffuseMap;
uniform sampler2D SpecularMap;

void main()
{
	// linearly interpolate between both textures
	vec4 texColor;
	if(textured)
	{
		texColor = mix(texture(DiffuseMap, TexCoord), texture(SpecularMap, TexCoord), mixValue) * vec4(ourColor, 1.0);
	}
	else
	{
		//texColor = vec4(ourColor, 1.0);
		texColor = vec4(0.0, 1.0, 0.0, 1.0);
	}

    texColor = vec4(0.0, 1.0, 0.0, 1.0);
	FragColor = texColor;
	//FragColor = texture(texture1, TexCoord);
}