#version 450
layout (location=0) in vec3 posAttr;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texCoords;

uniform mat4 matrix;
uniform mat4 model;
uniform mat4 transform;

out vec2 texCoord;
out vec3 n;
out vec3 FragPos;

void main(){
	gl_Position = matrix * transform * vec4(posAttr, 1.0);
	texCoord = texCoords;
	n= mat3(transpose(inverse(model))) * normal;
	//n=normal;
	FragPos = vec3(model * transform * vec4(posAttr,1.0));
}