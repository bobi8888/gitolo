uniform float time;

void main() {
    vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);

    // Create a pulsating alpha effect.
    texColor.a *= abs(sin(time));

    gl_FragColor = texColor;
}