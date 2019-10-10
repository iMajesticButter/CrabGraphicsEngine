#version 330

in vec4 inPos;
in vec3 inColor;

out vec3 VColor;
uniform mat4 MVP;

void main() {

    VColor = inColor;

    vec4 outPos = MVP * inPos;

    gl_Position = outPos;

}
