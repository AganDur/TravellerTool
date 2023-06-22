#version 450
in vec3 fragmentPosition;
in vec3 vertNormal;
in vec2 textureCoords;

uniform vec3 lightPos;
uniform vec3 color;
uniform vec3 diffuseLight;
uniform vec3 ambientLight;
uniform sampler2D textureData;

void main() {
    vec3 norm = normalize(vertNormal);

    vec3 L = normalize(lightPos - fragmentPosition);
    float NL = max(dot(norm, L), 0.0);
    vec3 diffuse = NL * diffuseLight;

    vec3 col = color * (diffuse + ambientLight);

    gl_FragColor = texture(textureData, textureCoords) * vec4(col, 1);
}
