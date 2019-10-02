#version 330

out vec3 color;
uniform vec2 mousePos;

void main() {

    float dist = distance(mousePos, gl_FragCoord.xy)/100;
    dist = clamp(1-dist, 0, 1);
    color = vec3(gl_FragCoord.x/200, gl_FragCoord.y/200, 0) * dist;

}
