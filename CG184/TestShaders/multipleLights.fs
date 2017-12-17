#version 330 core
out vec4 FragColor;

#define NR_POINT_LIGHTS 10

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
uniform Light light[NR_POINT_LIGHTS];

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

vec4 CalculatePointLight(Light _light, vec3 _normal, vec3 _fragPos, vec3 _viewPos);

void main()
{
    vec4 result;
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalculatePointLight(light[i], Normal, FragPos, viewPos);

    FragColor = result;
}


vec4 CalculatePointLight(Light _light, vec3 _normal, vec3 _fragPos, vec3 _viewPos)
{
    vec4 ambient = _light.ambient * material.ambient;

    // diffuse
    vec3 norm       = normalize(_normal);
    vec3 lightDir   = normalize(_light.position.xyz - _fragPos);
    if (_light.position.w == 0){
    	lightDir = _light.position.xyz;
    }

    float Kd     = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = _light.diffuse * (Kd * material.diffuse);

    // specular
    vec3 viewDir    = normalize(_viewPos - _fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float Ks        = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec4 specular   = _light.specular * (Ks * material.specular);

    vec4 result = ambient + diffuse + specular;
    result = max_to_one(result);
    return result;
}