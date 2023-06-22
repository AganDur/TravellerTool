#version 450
in vec2 textureCoords;

uniform vec3 color;
uniform sampler2D textureData;

void main() {
    gl_FragColor = texture(textureData, textureCoords) * (vec4(color, 1));
}
