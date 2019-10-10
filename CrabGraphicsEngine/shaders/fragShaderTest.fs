#version 330

in vec3 VColor;

out vec3 color;
uniform vec2 mousePos;
uniform float lightRange;

void main() {

    float dist = distance(mousePos, gl_FragCoord.xy)/400/lightRange;
    dist = clamp(1-dist, 0, 1);
    color = VColor * dist;
    //color = VColor;
    //color = vec3(1,1,1);

}
