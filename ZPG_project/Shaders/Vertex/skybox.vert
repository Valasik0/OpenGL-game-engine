#version 400
layout(location = 0) in vec3 vp;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 TexCoords;

void main () {
	 TexCoords = vp;
	 mat4 view = mat4(mat3(viewMatrix));
	 gl_Position = projectionMatrix * view * vec4(vp, 1.0);
}
