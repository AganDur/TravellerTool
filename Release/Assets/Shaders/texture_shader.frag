#version 450
in vec2 texCoord;
uniform sampler2D text;

void main(){
	gl_FragColor = texture(text, texCoord);
}