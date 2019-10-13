#version 330

in vec3 VColor;
in float oTest;
in vec2 uvCoord;

out vec4 color;
uniform vec2 mousePos;
uniform float lightRange;
uniform sampler2D tex;
uniform sampler2D tex2;

void main() {

    //float dist = distance(mousePos, gl_FragCoord.xy)/400/lightRange;
    //dist = clamp(1-dist, 0, 1)+oTest/2;
    //color = VColor * dist;
    //color = VColor * oTest;
    //color = vec4(1,1,1,1);
    vec4 tex1Col = texture(tex, uvCoord);
    color = tex1Col + texture(tex2, uvCoord) * (1.0 - tex1Col.w);
}
