# version 400
layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;

out vec4 worldPos;
out vec3 worldNorm;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main ( void )
{
    worldPos = modelMatrix * vec4 (vp, 1.0);
    worldNorm = normalize(transpose(inverse(mat3(modelMatrix))) * vn);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);
}