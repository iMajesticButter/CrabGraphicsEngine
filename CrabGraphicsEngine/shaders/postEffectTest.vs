#version 330

in vec4 in_Position;
in vec2 in_UV;

out vec2 UV;
uniform float Time_ms;

void main() {

    UV = in_UV;

    gl_Position.xyz = in_Position.xyz *  (1 - (sin(Time_ms * 0.5) + 1) * 0.25);
    gl_Position.w = in_Position.w;

}
