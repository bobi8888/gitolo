//varying out vec4 vert_pos;

void main()
{
   // Transform the vertex position
       // vert_pos =    gl_ModelViewProjectionMatrix * gl_Vertex;
       // gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
   // Transform the texture coordinates
       // gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

   // Forward the vertex color
       // gl_FrontColor = gl_Color;
}