#version 330

//--------------------------------------------------------------------------------------------------------
//     THIS SHADER IS USED BY THE RENDERER INTERNALLY, DO NOT MOVE OR MODIFY!!!!!!!!!!!!!!!!!!
//--------------------------------------------------------------------------------------------------------

//unroll the loop!
#pragma optionNV (unroll all)

#define PI 3.141

in vec2 UV;

out vec4 fragColor;

uniform vec2 resolution;
uniform sampler2D frame;

const float THRESHOLD = 0.75;

void main() {

    float angle = UV.x*(PI*2);

    float smallestDist = 1.0;

    for(float i = 0.0; i < 1024; i += 1.0) {
        //polar to normal coordinates
        vec2 coord = vec2(cos(angle), sin(angle)) * (i/resolution.x);
        coord.x = (coord.x+1)/2;
        coord.y = (coord.y+1)/2;

        //get texture sample
        vec4 texCol = texture(frame, coord);

        //check if sample passes Threshold
        float dst = i/resolution.x;

        //if(texCol.w > THRESHOLD) {
            //set smallestDist
            //smallestDist = min(smallestDist, dst);
        //}

        float val = 1-step(THRESHOLD, texCol.a);
        smallestDist = max(min(smallestDist, dst), smallestDist*val);

    }

    fragColor = vec4(vec3(smallestDist), 1.0f);

}
