#version 330

//--------------------------------------------------------------------------------------------------------
//     THIS SHADER IS USED BY THE RENDERER INTERNALLY, DO NOT MOVE OR MODIFY!!!!!!!!!!!!!!!!!!
//--------------------------------------------------------------------------------------------------------

in vec2 UV;

out vec4 fragColor;

uniform sampler2D tex;
uniform float alpha;

void main() {
    vec4 texColor = texture(tex, UV);
    if(texColor.w < 0.1)
        discard;
    fragColor.xyz = texColor.xyz;
    fragColor.w = clamp(texColor.w, alpha, 1);
}
