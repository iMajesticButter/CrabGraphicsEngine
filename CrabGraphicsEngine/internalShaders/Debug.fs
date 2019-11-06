#version 330

//--------------------------------------------------------------------------------------------------------
//     THIS SHADER IS USED BY THE RENDERER INTERNALLY, DO NOT MOVE OR MODIFY!!!!!!!!!!!!!!!!!!
//--------------------------------------------------------------------------------------------------------

out vec4 fragColor;

uniform vec3 Color;

void main() {
    //fragColor.rgb = Color;
    //fragColor.a = 1.0;
    fragColor = vec4(1,1,1,1);
}
