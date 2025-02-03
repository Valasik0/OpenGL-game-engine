# version 400
in vec4 worldPos;
in vec3 worldNorm;
out vec4 fragColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform vec3 ambientColor;
uniform vec3 objectColor;
uniform float diffuseStrength;

void main (void)
{
	vec3 lightDirection = normalize(lightPosition - vec3(worldPos));
	vec3 normalVector = normalize(worldNorm);

    vec4 diffuse = diffuseStrength * max(dot(lightDirection, normalVector), 0.0) * vec4(lightColor, 1.0);
	vec4 ambient = vec4 (ambientColor ,1.0);
	vec4 color = vec4 (objectColor ,1.0);

	fragColor = (ambient + diffuse) * color ;
}