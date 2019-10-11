#version 330

in vec3 VColor;
in float oTest;

out vec3 color;
uniform vec2 mousePos;
uniform float lightRange;

void main() {

    float dist = distance(mousePos, gl_FragCoord.xy)/400/lightRange;
    dist = clamp(1-dist, 0, 1)+oTest/2;
    color = VColor * dist;
    //color = VColor * oTest;
    //color = vec3(1,1,1);

}
