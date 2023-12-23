#version 450
in vec2 textureCoords;

uniform vec3 color;
uniform sampler2D textureData;

out vec4 outColor;

void main() {
    outColor = texture(textureData, textureCoords) * (vec4(color, 1));
}
