#version 330

//in vec3 VColor;
//in float oTest;
in vec2 uvCoord;

out vec4 color;
uniform sampler2D tex;
uniform vec3 tint;

void main() {

    color.xyz = texture(tex, uvCoord).xyz * tint;
    color.w = 0.5;

}
