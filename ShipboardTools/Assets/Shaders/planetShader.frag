#version 450 compatibility
in vec2 textureCoordinate;
in vec3 updatedNormal;
in vec3 fragmentPosition;

uniform vec3 ambientLight;
uniform vec3 diffuseLight;
uniform vec3 color;
uniform sampler2D textureData;
uniform vec3 lightPosition;

out vec4 FragColor;

void main(){
	//vec3 norm = normalize(updatedNormal);
	//vec3 lightDir = normalize(lightPosition - fragmentPosition);
	//float diffuseStrength = max(dot(norm, lightDir), 0.0);
	//vec3 diffuseComponent = diffuseStrength * diffuseLight;
	
        FragColor = vec4(0.0, 1.0, 1.0, 1.0); //texture(textureData, textureCoordinate) * vec4((ambientLight+diffuseComponent)*color, 1.0);
}
