#version 330

in vec4 inPos;
uniform mat4 MVP;

void main() {

    vec4 outPos = MVP * inPos;

    gl_Position = outPos;

}
