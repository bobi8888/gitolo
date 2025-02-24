in vec4 vert_pos;

uniform sampler2D texture; //unknown how this is being set? there is no setUniform for this?
uniform bool hasTexture;
uniform vec2 lightPos;

void main()
{
	//Ambient light
	//1.0f is max light, 0.0f is no light, the last value is alpha
		vec4 ambient = vec4(0.1f, 0.1f, 0.1f, 1.f);

	//Convert light to view coords
		vec2 lightPosTemp = lightPos;
	//gl_ModelViewProjectionMatrix can only be multiplied by a vec4?
		lightPosTemp = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0, 1)).xy;

	//Calculate the vector from light to pixel (Make circular)
		vec2 lightToFrag = lightPosTemp - vert_pos.xy;
	
	//Length of the vector (distance)
	/*the factor multiplied against length(lightToFrag is the 'size of the light' 
	2.0f is a larger light that 4.0f*/
		float vecLength = clamp(length(lightToFrag) * 2.0f, 0.0f, 1.0f);

	//lookup the pixel in the texture
		vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

	//Muliply by the color & lighting
		if (hasTexture == true)
		{
			gl_FragColor = gl_Color * pixel * (clamp(ambient + vec4(1 - vecLength, 1 - vecLength,1 - vecLength, 1), 0.0f, 1.f));
		}
		else
		{
			gl_FragColor = gl_Color;
		}
}
