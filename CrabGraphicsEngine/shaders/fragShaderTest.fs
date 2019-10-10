#version 330

out vec3 color;
uniform vec2 mousePos;

void main() {

    float dist = distance(mousePos, gl_FragCoord.xy)/400;
    dist = clamp(1-dist, 0, 1);
    color = vec3( clamp(gl_FragCoord.x/500,0,1), clamp(gl_FragCoord.y/500,0,1), 0) * dist;
    //color = vec3(1,1,1);

}
