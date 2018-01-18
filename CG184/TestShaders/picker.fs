#version 330

uniform int code;
out vec4 FragCol;
 
void main()
{
    FragCol = vec4(code/255.0, 0, 0, 0);
}