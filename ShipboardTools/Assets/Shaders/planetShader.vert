#version 450 compatibility
layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 textureCoordinates;

uniform mat4 projectionViewMatrix;
uniform mat4 modelMatrix;

out vec2 textureCoordinate;
out vec3 updatedNormal;
out vec3 fragmentPosition;

void main(){
	gl_Position = projectionViewMatrix * modelMatrix * vec4(position, 1.0);
	textureCoordinate = textureCoordinates;
	updatedNormal= mat3(transpose(inverse(modelMatrix))) * normal;
	fragmentPosition = vec3(modelMatrix * vec4(position,1.0));
}