#version 330

//in vec4 vertCol;

in GS_OUT {
    vec4 pos;
	vec3 col;
    vec3 normal;
	vec2 texCoord;
	vec3 wireframeDist;
} fs_in;

out vec4 FragCol;
 
float edgeFactor()
{
	vec3 d = fwidth(fs_in.wireframeDist);
    vec3 a3 = smoothstep(vec3(0.0), d*0.95, fs_in.wireframeDist);
    return min(min(a3.x, a3.y), a3.z);
}


void main()
{
	FragCol.rgb = mix(vec3(0.0), fs_in.col, edgeFactor());
	FragCol.a = 1.0;
    //FragCol = fs_in.col;
}



//if (wireframe)          // wireframe is a uniform bool
//{
//    vec3 d = fwidth(inData.wireframeDist);
// 
//    vec3 a3 = smoothstep(vec3(0.0), d * 1.5, inData.wireframeDist);
//    float edgeFactor = min(min(a3.x, a3.y), a3.z);
// 
//    endColor = vec4(mix(vec3(1.0), endColor.rgb, edgeFactor), endColor.a);
//    //endColor = vec4(mix(endColor.rgb, vec3(0.0), edgeFactor), mix(0.0, endColor.a, edgeFactor));
//    //endColor = vec4(mix(endColor.rgb, vec3(0.0), edgeFactor), (1.0 - edgeFactor) * 0.95);
//}