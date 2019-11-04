#version 330

in vec2 UV;

out vec4 fragColor;

uniform sampler2D frame;
uniform sampler2D dither_pattern;

void main() {

    fragColor = texture(frame, UV);
    fragColor += vec4(texture(dither_pattern, gl_FragCoord.xy / 8.0).r / 16.0 - (1.0 / 128.0));

}
