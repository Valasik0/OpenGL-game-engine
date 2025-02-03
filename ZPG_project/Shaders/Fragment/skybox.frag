#version 400
out vec4 fragColor;

uniform samplerCube skybox;

in vec3 TexCoords;
void main () {
    vec4 texColor = texture(skybox, TexCoords) * 0.5;
    texColor.rgb *= 0.5;  // Multiply the color by the brightness coefficient
    fragColor = texColor;
}