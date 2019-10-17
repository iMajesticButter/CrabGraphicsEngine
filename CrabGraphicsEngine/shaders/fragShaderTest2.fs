#version 330

//in vec3 VColor;
//in float oTest;
in vec2 uvCoord;

out vec4 color;
uniform sampler2D tex;
uniform vec3 tint;

void main() {
    vec4 texCol = texture(tex, uvCoord);
    color.xyz = texCol.xyz * tint;
    color.w = texCol.w;

}
