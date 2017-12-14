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


in vec3 Normal;
in vec3 FragPos;  

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

vec4 product(vec4 a, vec4 b)
{
	return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

vec4 max_to_one(vec4 col)
{
	float max_val = max(col.x, max(col.y, col.z));
	if(max_val > 1.0){
		return vec4(col.x / max_val, col.y / max_val, col.z / max_val, 1.0);
	}else{
		return col;
	}
}


void main()
{

	// ambient
    vec4 ambient = light.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position.xyz - FragPos);
	if (light.position.w == 0){
		lightDir = light.position.xyz;
	}
    float Kd = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = light.diffuse * (Kd * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float Ks = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec4 specular = light.specular * (Ks * material.specular);  
        
    vec4 result = ambient + diffuse + specular;
	result = max_to_one(result);
    FragColor = result;
	//FragColor = vec4(result, 1.0);

} 