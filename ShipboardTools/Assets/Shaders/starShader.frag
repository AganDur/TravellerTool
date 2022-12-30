#version 450
in vec2 texCoord;
uniform vec4 color;
uniform sampler2D text;

void main(){
	gl_FragColor = texture(text, texCoord) * (color*10.0) ;
}