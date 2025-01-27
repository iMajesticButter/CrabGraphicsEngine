#version 330

//--------------------------------------------------------------------------------------------------------
//     THIS SHADER IS USED BY THE RENDERER INTERNALLY, DO NOT MOVE OR MODIFY!!!!!!!!!!!!!!!!!!
//--------------------------------------------------------------------------------------------------------

#define PI 3.141
#define BIAS 0.005

in vec2 UV;

out vec4 fragColor;

uniform sampler2D frame;
uniform sampler2D ditherPattern;
uniform float Time_ms;
uniform vec3 lightColor;
uniform vec2 resolution;
uniform float falloff;
uniform float intencity;
uniform float softness;

float sample(vec2 coord, float r) {
	return smoothstep(r-BIAS, r, texture2D(frame, coord).r);
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

	float dist = r*falloff;

	float att = clamp(1.0 - dist/1.0, 0.0, 1.0);
	att *= att;

    //fragColor = vec4(lightColor, intencity) * vec4(vec3(1.0), sum * smoothstep(1.0, 0.0, r));
	fragColor = (vec4(lightColor, 1.0) * vec4(sum * att)) * intencity * step(0.001, texture(frame, tc));
	//fragColor += vec4(texture(ditherPattern, gl_FragCoord.xy / 8.0).r / 16.0 - (1.0 / 128.0));
}
