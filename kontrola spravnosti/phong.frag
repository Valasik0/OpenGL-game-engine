# version 400
in vec4 worldPos;
in vec3 worldNorm;
out vec4 fragColor;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec3 lightColor;

uniform vec3 ambientColor;
uniform vec3 objectColor;
uniform float specularStrength;
uniform float diffuseStrength;

void main (void)
{	
	vec3 viewDirection = normalize(cameraPosition - vec3(worldPos));
	vec3 lightDirection = normalize(lightPosition - vec3(worldPos));
	vec3 normalDirection = normalize(worldNorm);
	vec3 reflectionDirection = reflect(-lightDirection, normalDirection);

	float dotProduct = dot(lightDirection, normalDirection);
	float specValue = pow(max(dot(viewDirection, reflectionDirection), 0.0), 32);
   	vec3 specularVec = specularStrength * specValue * lightColor;

	vec4 diffuse = diffuseStrength * max(dotProduct, 0.0) * vec4(lightColor, 1.0);
	vec4 ambient = vec4 (ambientColor ,1.0);
	vec4 color = vec4 (objectColor, 1.0);

	vec4 specular;

	if ( dotProduct < 0.0) {
		specular = vec4 (0.0 , 0.0 , 0.0 , 0.0);
	} else{
		specular = vec4(specularVec, 1.0);
	}

	fragColor = (ambient + diffuse + specular) * color ;
}