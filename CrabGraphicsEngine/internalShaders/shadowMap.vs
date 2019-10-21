#version 330

//--------------------------------------------------------------------------------------------------------
//     THIS SHADER IS USED BY THE RENDERER INTERNALLY, DO NOT MOVE OR MODIFY!!!!!!!!!!!!!!!!!!
//--------------------------------------------------------------------------------------------------------

in vec4 in_Position;
in vec2 in_UV;

out vec2 UV;

void main() {
    UV = in_UV;
    gl_Position = in_Position;
}
