#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec3 in_colour;
out vec3 out_color;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main () {
     gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (vp, 1.0);
	 out_color = in_colour;
}