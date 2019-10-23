#version 330

//--------------------------------------------------------------------------------------------------------
//     THIS SHADER IS USED BY THE RENDERER INTERNALLY, DO NOT MOVE OR MODIFY!!!!!!!!!!!!!!!!!!
//--------------------------------------------------------------------------------------------------------

in vec2 UV;

out vec4 fragColor;

uniform sampler2D tex;
uniform sampler2D ditherSampler;
uniform float alpha;

void main() {
    vec4 texColor = texture(tex, UV);
    //if(texColor.w < 0.1)
    //    discard;
    fragColor.xyz = texColor.xyz;
    fragColor.w = clamp(texColor.w, alpha, 1);
    fragColor += vec4(texture(ditherSampler, gl_FragCoord.xy / 8.0).r / 32.0 - (1.0 / 128.0));
}
