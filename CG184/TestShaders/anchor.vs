#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

out vec4 vertCol;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vertCol = vec4(aColor, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}