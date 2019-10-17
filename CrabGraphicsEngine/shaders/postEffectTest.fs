#version 330

in vec2 UV;

out vec4 fragColor;

uniform sampler2D frame;

void main() {

    fragColor = 1-texture(frame, UV);
    fragColor.w = 1.0;

}
