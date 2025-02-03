#version 330
in vec3 out_color;
out vec4 frag_colour;

uniform vec3 objectColor;

void main () {
     frag_colour = vec4 (objectColor, 1.0);
}