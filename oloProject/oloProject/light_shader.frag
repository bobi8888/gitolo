uniform sampler2D texture;

uniform vec2 lightPos;  // light position in window/pixel coordinates
uniform float windowHeight;

void main()
{
// Get the current pixel's color from the target sprite texture.
// Note: gl_TexCoord[0].xy works with the default SFML shader setup.
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);
    
// Use the built-in gl_FragCoord.xy to get this pixel's window coordinates.
    vec2 pixelPos = vec2(gl_FragCoord.x, windowHeight - gl_FragCoord.y);
    
// Calculate the distance from the light to the current pixel.
    float distance = length(pixelPos - lightPos);
    
// Calculate brightness: tweak the constant (0.008) to control the attenuation.
    /*              brightness               attenuation */
    float brightness = 1.25    / (distance * 0.008 + 1.0);


// Multiply the sprite color by the brightness.
    gl_FragColor = color * brightness;
}