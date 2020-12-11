#version 330 core
out vec4 fragColor;

in vec2 textureCoordinates;

uniform vec3 lightColor;

uniform sampler2D sunTexture;

void main()
{
    fragColor = texture(sunTexture, textureCoordinates) * vec4(lightColor, 1.0f);
}