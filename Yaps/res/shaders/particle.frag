#version 400 core

out vec4 colour;

in vec2 texCo;

uniform sampler2D texSampler;

void main() {
    vec4 raw = texture(texSampler,texCo);
    if (raw[3] != 0){
        raw /= 1.25;
    }
    raw[3] = 1;
    colour = raw;
};
