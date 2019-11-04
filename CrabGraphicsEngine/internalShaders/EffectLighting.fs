#version 330

in vec2 UV;

out vec4 fragColor;

uniform sampler2D frame;
uniform sampler2D light_texture;

void main() {

    fragColor = texture(frame, UV) * texture(light_texture, UV);
    fragColor.w = 1.0;

}
