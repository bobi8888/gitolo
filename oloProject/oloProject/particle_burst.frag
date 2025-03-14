uniform float time;

void main() {
    vec4 col = gl_Color;     // Retrieve the incoming vertex color.

    col.a *= abs(sin(time));     // Modulate alpha with a sine function for a pulsating effect.

    gl_FragColor = col;
}