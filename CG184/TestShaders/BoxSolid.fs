#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec3 Normal;
in vec3 FragPos;
  
//uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

//const int numLights = 3;
uniform vec3 lightposnarray[3];//numLights];
uniform vec3 lightcolorarray[3];//[numLights];

vec3 ComputeLight (vec3 lightpos, vec3 normal, vec3 lightcolor, vec3 fragPos, vec3 viewPosition, float shininess) {

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightpos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightcolor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPosition - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightcolor;

    return (diffuse + specular);
}



void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    vec3 tempCol = ambient;
    for(int i = 0; i < 3; i++){
        //tempCol += lightposnarray[i];
        tempCol += ComputeLight (lightposnarray[i], Normal, lightcolorarray[i], FragPos, viewPos, 32);
    }

    //vec3 result = (ambient + diffuse + specular) * ourColor;
    vec3 result = (ambient + diffuse + specular + tempCol) * ourColor;

    FragColor = vec4(result, 1.0);
}