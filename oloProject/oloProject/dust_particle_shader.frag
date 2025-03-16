uniform float time;
uniform mat3 viewTransform;

void main() {
    vec3 textureCoords = viewTransform * vec3(gl_TexCoord[0].xy, 1.0);

    vec4 texColor = texture2D(texture, textureCoords.xy);

    // Create a pulsating alpha effect. or should this be described as a fading effect?
    texColor.a *= abs(sin(time));

    gl_FragColor = texColor;
}