#version 450
in vec2 texCoord;
in vec3 n;
in vec3 FragPos;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 color;
uniform sampler2D text;
uniform vec3 lightPos;

void main(){
	vec3 norm = normalize(n);
	vec3 lightDir = normalize(lightPos - FragPos);
	float d = max(dot(norm, lightDir), 0.0);
	vec3 diff = d * diffuse;
	
	gl_FragColor = texture(text, texCoord) * vec4((ambient+diff)*color, 1.0); 
}