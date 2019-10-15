#version 330

//in vec3 VColor;
//in float oTest;
in vec2 uvCoord;

out vec4 color;
uniform vec2 mousePos;
uniform float lightRange;
uniform sampler2D tex;
uniform sampler2D tex2;
uniform float backTest;
uniform vec3 tint;

void main() {

    float dist = distance(mousePos, gl_FragCoord.xy)/400/lightRange;
    dist = clamp(1-dist, 0, 1);
    //color = VColor * dist;
    //color = VColor * oTest;
    //color = vec4(1,1,1,1);
    vec4 tex1Col = texture(tex, uvCoord);
    vec4 col = tex1Col + (texture(tex2, uvCoord) * (1.0 - tex1Col.w)) * backTest;

    //if(col.a < 0.1f) {
    //    discard;
    //}

    //color = (col/2 + vec4(VColor, 1.0)/30) * dist;
    color.xyz = (col.xyz * tint) * dist;
    color.w = col.w;
}
