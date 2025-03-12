        uniform float u_time;

        void main()
        {
            // Get normalized coordinates for the rectangle (range: 0.0 to 1.0)
            vec2 uv = gl_TexCoord[0].xy;
            
            // Compute a time-based oscillation for the blue channel.
            float blue = 0.5 + 0.5 * sin(u_time * 3.0);

            // Set the fragment color based on the texture coordinate and time.
            gl_FragColor = vec4(uv.x, uv.y, blue, 1.0);
        }