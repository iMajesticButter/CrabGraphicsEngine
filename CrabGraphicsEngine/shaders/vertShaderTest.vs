#version 330

in vec4 in_Position;
in vec3 in_Color;
in vec2 in_UV;
layout(location = 3) in float test;

out vec3 VColor;
out float oTest;
out vec2 uvCoord;
uniform mat4 MVP;

void main() {

    VColor = in_Color;
    oTest = test;
    uvCoord = in_UV;

    vec4 outPos = MVP * in_Position;
    //vec4 outPos = inPos;

    gl_Position = outPos;

}
