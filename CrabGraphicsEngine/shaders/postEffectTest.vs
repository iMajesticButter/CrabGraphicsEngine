#version 330

in vec4 in_Position;
in vec2 in_UV;

out vec2 UV;

void main() {

    UV = in_UV;

    gl_Position = in_Position;

}
