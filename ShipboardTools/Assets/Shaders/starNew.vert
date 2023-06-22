#version 450
layout (location=0) in vec3 vertex;
layout (location=1) in vec2 textureCoordinates;

out vec2 textureCoords;

uniform mat4 projMatrix;
uniform mat4 mvMatrix;

void main() {
    textureCoords = textureCoordinates;

    gl_Position = projMatrix * mvMatrix * vec4(vertex, 1);
}
