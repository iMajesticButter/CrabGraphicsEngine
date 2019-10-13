#version 330

in vec4 inPos;
in vec3 inColor;
in float test;
in vec2 in_uvCoord;

out vec3 VColor;
out float oTest;
out vec2 uvCoord;
uniform mat4 MVP;

void main() {

    VColor = inColor;
    oTest = test;
    uvCoord = in_uvCoord;

    vec4 outPos = MVP * inPos;

    gl_Position = outPos;

}
