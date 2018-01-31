#version 330 core
 
layout(triangles) in;
layout (triangle_strip, max_vertices =3) out;
 
// Input types
//in VertexData
//{
//    vec3 normal;
//    vec3 position;
//    vec3 color;
//    vec3 nm_normal;
//    vec4 rotation;
// 
//    float selected;
// 
//    flat int index;
//    flat int anchorState;
//} inData[];

in VS_OUT {
    vec4 pos;
	vec3 col;
    vec3 normal;
	vec2 texCoord;
} gs_in[];

 
// Output to fragment shader types. Everything but wireframeDist is just a passthrough
//out FragData
//{
//    vec3 normal;
//    vec3 position;
//    vec3 color;
//    vec3 nm_normal;
//    vec4 rotation;
// 
//    float selected;
// 
//    flat int index;
//    flat int anchorState;
// 
//    // Noperspective so the interpolation is in screen-space
//    noperspective vec3 wireframeDist;
//} outData;
 
out GS_OUT {
    vec4 pos;
	vec3 col;
    vec3 normal;
	vec2 texCoord;
	vec3 wireframeDist;
} fs_out;

 
void main()
{
    for(int i = 0; i < 3; i++)
    {
        gl_Position = gl_in[i].gl_Position;
 
        fs_out.pos				=  gs_in[i].pos		;
		fs_out.col				=  gs_in[i].col		;
		fs_out.normal			=  gs_in[i].normal	;
		fs_out.texCoord			=  gs_in[i].texCoord;
 
        // This is the easiest scheme I could think of. The attribute will be interpolated, so
        // all you have to do is set the ith dimension to 1.0 to get barycentric coordinates
        // specific to this triangle. The frag shader will interpolate and then you can just use
        // a threshold in the frag shader to figure out if you're close to an edge
        
		fs_out.wireframeDist = vec3(0.0);
        fs_out.wireframeDist[i] = 1.0;
 
        EmitVertex();
    }
}