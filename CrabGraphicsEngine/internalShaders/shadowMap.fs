#version 330

//--------------------------------------------------------------------------------------------------------
//     THIS SHADER IS USED BY THE RENDERER INTERNALLY, DO NOT MOVE OR MODIFY!!!!!!!!!!!!!!!!!!
//--------------------------------------------------------------------------------------------------------

#define PI 3.141

in vec2 UV;

out vec4 fragColor;

uniform vec2 resolution;
uniform sampler2D frame;

const float THRESHOLD = 0.75;

void main() {

    float angle = UV.x*(PI*2);

    float smallestDist = 1.0;

    for(float i = 0.0; i < resolution.x; ++i) {
        //polar to normal coordinates
        vec2 coord = vec2(cos(angle), sin(angle)) * (i/resolution.x);
        coord.x = (coord.x+1)/2;
        coord.y = (coord.y+1)/2;

        //get texture sample
        vec4 texCol = texture(frame, coord);

        //check if sample passes Threshold

        if(texCol.w > THRESHOLD) {
            //set smallestDist
            smallestDist = min(i/resolution.x, smallestDist);
        }
    }

    fragColor = vec4(smallestDist);

}
