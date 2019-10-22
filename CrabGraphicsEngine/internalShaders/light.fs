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
uniform float softness;

float sample(vec2 coord, float r) {
	return step(r, texture2D(frame, coord).r);
}

void main() {

    vec2 dir = vec2((UV.x-0.5)*2, (UV.y-0.5)*2);

    float angle = atan(dir.y, dir.x);

    vec2 tc = vec2(angle/(PI*2), 0);

    float r = length(dir);

    float center = sample(tc, r);

	float blur = (1.0/resolution.x) * smoothstep(0.0, 1.0, r) * softness;

	float sum = 0.0;

	sum += sample(vec2(tc.x - 4.0*blur, tc.y), r) * 0.05;
	sum += sample(vec2(tc.x - 3.0*blur, tc.y), r) * 0.09;
	sum += sample(vec2(tc.x - 2.0*blur, tc.y), r) * 0.12;
	sum += sample(vec2(tc.x - 1.0*blur, tc.y), r) * 0.15;

	sum += center * 0.16;

	sum += sample(vec2(tc.x + 4.0*blur, tc.y), r) * 0.15;
	sum += sample(vec2(tc.x + 3.0*blur, tc.y), r) * 0.12;
	sum += sample(vec2(tc.x + 2.0*blur, tc.y), r) * 0.09;
	sum += sample(vec2(tc.x + 1.0*blur, tc.y), r) * 0.05;

    fragColor = vec4(lightColor, 1.0) * vec4(vec3(1.0), sum * smoothstep(1.0, 0.0, r*falloff)) * intencity;

}
