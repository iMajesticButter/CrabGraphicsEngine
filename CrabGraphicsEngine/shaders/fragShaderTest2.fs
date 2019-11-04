#version 330

//in vec3 VColor;
//in float oTest;
in vec2 uvCoord;

out vec4 color;
uniform sampler2D tex;
uniform sampler2D light_texture;
uniform vec3 tint;
uniform vec2 resolution;

void main() {
    vec4 texCol = texture(tex, uvCoord);
    color.xyz = texture2D(light_texture, gl_FragCoord.xy / resolution.xy).rgb * texCol.xyz * tint;
    color.w = texCol.w;

}
