#version 450
layout (location=0) in vec3 posAttr;
uniform mat4 matrix;
uniform mat4 transform;

void main(){
	gl_Position = matrix * transform * vec4(posAttr, 1.0);
}