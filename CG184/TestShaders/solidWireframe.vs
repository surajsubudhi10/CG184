#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

//out vec4 vertCol;
out VS_OUT {
    vec4 pos;
    vec3 col;
    vec3 normal;
    vec2 texCoord;
} vs_out;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat3 normalMatrix = mat3(transpose(inverse(view * model)));
    
    vs_out.normal		= vec3(projection * vec4(normalMatrix * aNormal, 0.0));
    vs_out.col			= aColor;
    vs_out.pos			= projection * view * model * vec4(aPos, 1.0);
    vs_out.texCoord		= vec2(0.0, 0.0); 

    gl_Position = vs_out.pos;
}