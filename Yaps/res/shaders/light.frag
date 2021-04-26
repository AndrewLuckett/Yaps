#version 400 core

out vec4 colour;

in vec2 texCo;

uniform sampler2D texSampler;

void main() {
    vec4 raw = texture(texSampler,texCo);
    //RGBA
    raw[3] = 1;
    //Full alpha ignore particle velocity
    colour = raw;
    //colour = vec4(1.0,0.0,1.0,1.0);
};
