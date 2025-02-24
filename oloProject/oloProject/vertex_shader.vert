out vec4 vert_pos;

void main()
{
		//Comments are from the sfml website about shaders
		//transform the vertex position
	vert_pos = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

		//transform the texture coordinates
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

		//forward the vertex color
	gl_FrontColor = gl_Color;
}