//Comments are from the sfml website about shaders

//out vec4 vert_pos;

//layout(location = 0) in vec3 position;

//void main()
//{
//transform the vertex position
	//vert_pos = gl_ModelViewProjectionMatrix * gl_Vertex;

	//gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

//transform the texture coordinates
	//gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

//forward the vertex color
	//gl_FrontColor = gl_Color;
//}

        uniform vec2 texSize;

        void main()
        {
            // Normalize the texture coordinates by dividing by the texture size.
            vec2 normTexCoord = gl_MultiTexCoord0.xy / texSize;
            gl_TexCoord[0] = vec4(normTexCoord, 0.0, 1.0);

            // Standard vertex position transformation.
            gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        }