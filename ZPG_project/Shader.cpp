#include "Shader.h"
#include "Camera.h"
#include "Light.h"

Shader::Shader(ShaderType shaderType, const char* vertex_path, const char* fragment_path) : 
	ShaderLoader(vertex_path, fragment_path, &this->shaderProgramID) {
	this->shaderType = shaderType;
	this->flashlightPosition = -1;
}

void Shader::useProgram() {
	glUseProgram(this->shaderProgramID);
}

void Shader::unsetShader() {
	glUseProgram(0);
}

void Shader::passUniformLocation(glm::mat4 matrix, const char* name){
	GLint idUniform = glGetUniformLocation(this->shaderProgramID, name);
	if (idUniform >= 0) {
		glUniformMatrix4fv(idUniform, 1, GL_FALSE, &matrix[0][0]);
	}
}

void Shader::passUniformLocation(glm::vec3 vec, const char* name) {
	GLint idUniform = glGetUniformLocation(this->shaderProgramID, name);
	if (idUniform >= 0) {
		glUniform3fv(idUniform, 1, &vec[0]);
	}
}

void Shader::passUniformLocation(float value, const char* name) {
	GLint idUniform = glGetUniformLocation(this->shaderProgramID, name);
	if (idUniform >= 0) {
		glUniform1f(idUniform, value);
	}
}

void Shader::passUniformLocation(int value, const char* name) {
	GLint idUniform = glGetUniformLocation(this->shaderProgramID, name);
	if (idUniform >= 0) {
		glUniform1i(idUniform, value);
	}
}

void Shader::passUniformLocation(GLuint value, const char* name) {
	GLint idUniform = glGetUniformLocation(this->shaderProgramID, name);
	if (idUniform >= 0) {
		glUniform1i(idUniform, value);
	}
}


ShaderType Shader::getShaderType(){
	return this->shaderType;
}

void Shader::update(void* object, ChangeType change) {
	useProgram();
	if (change == ChangeType::CameraChanged) {
		Camera& camera = *((Camera*)object);
		passUniformLocation(camera.getView(), "viewMatrix");
		passUniformLocation(camera.getProjection(), "projectionMatrix");
		passUniformLocation(camera.getPosition(), "cameraPosition");
		passUniformLocation(camera.getPosition(), "lights[0].position");
		passUniformLocation(camera.getTarget(), "lights[0].direction");
	}
	else if (change == ChangeType::WindowChanged) {
		Camera& camera = *((Camera*)object);
		passUniformLocation(camera.getProjection(), "projectionMatrix");
	}
	else if (change == ChangeType::LightColorChanged) {
		Light& light = *((Light*)object);
		passUniformLocation(light.getLightColor(), "lightColor");
	}
	else if (change == ChangeType::LightTurnedOffOn) {
		Light& light = *((Light*)object);
		passUniformLocation(light.isLightOn(), "lights[0].isOn");
	}
}