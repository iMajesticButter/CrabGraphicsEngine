#version 330

//--------------------------------------------------------------------------------------------------------
//     THIS SHADER IS USED BY THE RENDERER INTERNALLY, DO NOT MOVE OR MODIFY!!!!!!!!!!!!!!!!!!
//--------------------------------------------------------------------------------------------------------

in vec4 in_Position;
in vec2 in_UV;

out vec2 UV;

uniform vec4 viewport;

void main() {
    UV = in_UV;
    gl_Position.xyz = vec3(viewport.x + (in_Position.x * viewport.z), viewport.y + (in_Position.y * viewport.w), 0.0);
    gl_Position.w = 1.0;
}
