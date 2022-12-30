#version 450
layout (location=0) in vec3 posAttr;
layout (location=1) in vec2 texCoords;

uniform mat4 matrix;
uniform mat4 transform;
out vec2 texCoord;
void main(){
	gl_Position = matrix * transform * vec4(posAttr, 1.0);
	texCoord = texCoords;
}