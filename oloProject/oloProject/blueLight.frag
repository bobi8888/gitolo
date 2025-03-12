uniform sampler2D texture;
        
void main()
{            
    vec4 texColor = texture2D(texture, gl_TexCoord[0].xy); // Sample the original texture color.
            
// Calculate the distance of the current fragment from the center of the sprite.
    vec2 center = vec2(0.5, 0.5);
    float dist = distance(gl_TexCoord[0].xy, center);
            
    // Compute a glow intensity that is highest at the center and fades out.
    // Here, smoothstep defines the falloff: for distances <= 0.3 the glow is full,
    // and it fades to 0 by a distance of 0.6.
                                        
    float glowIntensity = 1.0 - smoothstep(
        0.01, /*full glow*/
        0.99, /*distance until 0 glow*/
        dist
    );
            
    vec4 blueGlow = vec4(0.0, 0.0, glowIntensity, 0.0); // Create a blue glow on top of the base texture

    vec4 finalColor = texColor + blueGlow; // Combine the original texture color with the blue glow
            
    gl_FragColor = vec4(min(finalColor.rgb, vec3(1.0)), texColor.a); // Ensure that the final RGB components do not exceed 1.0.

}