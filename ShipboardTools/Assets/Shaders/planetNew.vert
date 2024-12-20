#version 450

layout (location=0) in vec3 vertex;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 textureCoordinates;

out vec3 fragmentPosition;
out vec3 vertNormal;
out vec2 textureCoords;

uniform mat4 projMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

void main() {
    fragmentPosition = vec3(mvMatrix*vec4(vertex,1));

    textureCoords = textureCoordinates;

    vertNormal = normalMatrix * normal;

    gl_Position = projMatrix * mvMatrix * vec4(vertex, 1);
}
