#version 330 core
out vec4 FragColor;

in vec3 outColor;
in vec2 TexCoord;

uniform sampler2D DiffuseMap;

void main()
{
    FragColor = texture(DiffuseMap, TexCoord);
    //FragColor = vec4(1.0); // set all 4 vector values to 1.0
}