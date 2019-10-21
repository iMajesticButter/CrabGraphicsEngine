#version 330

//--------------------------------------------------------------------------------------------------------
//     THIS SHADER IS USED BY THE RENDERER INTERNALLY, DO NOT MOVE OR MODIFY!!!!!!!!!!!!!!!!!!
//--------------------------------------------------------------------------------------------------------

#define PI 3.141

in vec2 UV;

out vec4 fragColor;

uniform sampler2D frame;
uniform float Time_ms;
uniform vec3 lightColor;
uniform vec2 resolution;
uniform vec2 lightPos;
uniform float falloff;
uniform float intencity;

float sample(vec2 coord, float r) {
	return step(r, texture2D(frame, coord).r);
}

void main() {

    vec2 dir = vec2((UV.x-0.5)*2, (UV.y-0.5)*2);

    float angle = atan(dir.y, dir.x);

    vec2 tc = vec2(angle/(PI*2), 0);

    float r = length(dir);

    float center = sample(tc, r);

    fragColor = vec4(center);

}
