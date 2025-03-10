        //Uniform texture is not set externally? Just declared here? Needed to work however
            uniform sampler2D texture;

        // Light position in normalized texture coordinate space [0, 1], set in while loop
            uniform vec2 lightPos; 
           
        // Light radius in texture coordinate space
            uniform float lightRadius;  

        // Color of the diffuse light
            uniform vec3 lightColor;    
            
        // Ambient light color
            uniform vec3 ambientLight;  

uniform bool hasTexture;

        void main()
        {
        // Sample the sprite's texture color.
            vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);

        // Compute the distance from the current fragment to the light's position.
            float dist = distance(gl_TexCoord[0].xy, lightPos);

        // Calculate attenuation: fragments closer than the light radius are lit more intensely.
            float attenuation = clamp(1.0 - (dist / lightRadius), 0.0, 1.0);

        // Diffuse component scales with the attenuation.
            vec3 diffuse = lightColor * attenuation;

        // Combine ambient lighting with the diffuse component.
            vec3 finalLight = ambientLight + diffuse;

        // Multiply the texture color by the final light value.
            gl_FragColor = vec4(texColor.rgb * finalLight, texColor.a);
        }