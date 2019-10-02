#version 330

in vec3 inPos;

void main() {

    gl_Position.xyz = inPos;
    gl_Position.w = 1.0;

}
