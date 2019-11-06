#version 330

//--------------------------------------------------------------------------------------------------------
//     THIS SHADER IS USED BY THE RENDERER INTERNALLY, DO NOT MOVE OR MODIFY!!!!!!!!!!!!!!!!!!
//--------------------------------------------------------------------------------------------------------

in vec2 UV;

out vec4 fragColor;

uniform sampler2D frame;
uniform sampler2D light_texture;

void main() {

    fragColor = texture(frame, UV) * texture(light_texture, UV);
    fragColor.w = 1.0;

}
