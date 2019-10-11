#version 330

in vec4 inPos;
in vec3 inColor;
in float test;

out vec3 VColor;
out float oTest;
uniform mat4 MVP;

void main() {

    VColor = inColor;
    oTest = test;

    vec4 outPos = MVP * inPos;

    gl_Position = outPos;

}
