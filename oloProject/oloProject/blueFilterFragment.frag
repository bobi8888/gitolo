uniform sampler2D texture;
        
        void main()
        {
            // Sample the original texture color using the automatically provided texture coordinate.
            vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);
            
            // Blend the original color with blue (RGB: 0,0,1) by 50%.
            vec3 tinted = mix(texColor.rgb, vec3(0.0, 0.0, 1.0), 0.5);
            
            // Output the tinted color while preserving the original alpha.
            gl_FragColor = vec4(tinted, texColor.a);
        }