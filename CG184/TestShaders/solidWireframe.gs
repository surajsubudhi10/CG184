#version 330
 
layout(triangles) in;
layout (triangle_strip, max_vertices =3) out;

in VS_OUT {
    vec4 pos;
    vec3 col;
    vec3 normal;
    vec2 texCoord;
} gs_in[];
 
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
 
        // The attribute will be interpolated, so all you have to do is set the ith dimension to 1.0 to get barycentric coordinates
        // specific to this triangle. The frag shader will interpolate and then you can just use
        // a threshold in the frag shader to figure out if you're close to an edge
        
        fs_out.wireframeDist = vec3(0.0);
        fs_out.wireframeDist[i] = 1.0;
 
        EmitVertex();
    }
}