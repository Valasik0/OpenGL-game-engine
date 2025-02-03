# version 400
#define MAX_LIGHTS 10

in vec4 worldPos;
in vec3 worldNorm;
in vec2 texCoords;
out vec4 fragColor;

uniform vec3 cameraPosition;

uniform vec3 ambientColor;
uniform vec3 objectColor;
uniform float specularStrength;
uniform float diffuseStrength;
uniform sampler2D textureUnitID;
uniform float highlightCoefficient;

uniform int numLights;

struct Light {
	int isOn;
    int type; // 0 = Directional, 1 = Point, 2 = Spotlight
    vec3 position;
    vec3 direction;
    vec3 color;
    float cutOff; // For spotlights
    float outerCutOff; // For spotlights
    float constantAttenuation; // For point and spotlight
    float linearAttenuation; // For point and spotlight
    float quadraticAttenuation; // For point and spotlight
};

uniform Light lights[MAX_LIGHTS];

vec3 normalDirection = normalize(worldNorm);
vec3 viewDirection = normalize(cameraPosition - vec3(worldPos));

float calculateAttenuation(Light light){
	float distance = length(light.position - vec3(worldPos)); //distance from fragment to light position
	float attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * distance + light.quadraticAttenuation * (distance * distance));  

	return attenuation;
}

float calcualteIntensity(Light light, vec3 lightDirection){
	float theta = dot(lightDirection, normalize(-light.direction)); 
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	return intensity;
}

vec3 calculateLightDirection(Light light){
	vec3 lightDirection = vec3(0.0);

	if(light.type == 0){
		lightDirection = normalize(-light.direction);
	}
	else{
		lightDirection = normalize(light.position - vec3(worldPos));
	}
	
	return lightDirection;
}

void main (void)
{
	vec4 finalColor = vec4(0.0);

	for (int i = 0; i < numLights; i++) {
        Light light = lights[i];	

		vec3 lightDirection = calculateLightDirection(light);

		float attenuation = calculateAttenuation(light);
		float intensity = calcualteIntensity(light, lightDirection);

		float dotProduct = dot(lightDirection, normalDirection);

		vec4 diffuse = diffuseStrength * max(dotProduct, 0.0) * vec4(light.color, 1.0);

		if(light.type == 0){
			finalColor += (diffuse) * vec4(objectColor, 1.0);
		}
		else if(light.type == 1){
			finalColor += attenuation * (diffuse) * vec4(objectColor, 1.0);
		}
		else if((light.type == 2 || light.type == 3) && light.isOn == 1){
			finalColor += attenuation * intensity * (diffuse) * vec4(objectColor, 1.0);
		}
	}

	fragColor = vec4(ambientColor, 1.0) +  finalColor * highlightCoefficient;
}