#version 330 core
out vec4 fragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D venusTexture;

in vec3 fragPos;
in vec3 normal;
in vec2 textureCoordinates;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength * lightColor;

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir),0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec4 result = vec4((ambient + diffuse + specular), 1.0f) * texture(venusTexture, textureCoordinates);
    fragColor = result;
}