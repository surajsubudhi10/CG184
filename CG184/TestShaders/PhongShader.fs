
#version 330 core
out vec4 FragColor;

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
	vec4 emission;
	float shininess;
}; 

struct Light {
    vec4 position;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
	vec3 attenuation;
};


in vec3 FragPos;  
in vec3 Normal;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;


void main()
{
	vec3 result = vec3(1.0);
    FragColor = vec4(result, 1.0);
} 