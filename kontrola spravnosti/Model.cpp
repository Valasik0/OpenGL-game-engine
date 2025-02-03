#include "Model.h"
#include "Shader.h"
#include <stdlib.h>
#include <stdio.h>

Model::Model(const float points[], GLint vertexSize, int verticesCount, Shader* shader) {
	this->VBO = 0;
	this->VAO = 0;
	this->vertexSize = vertexSize;
	this->points = points;
    this->verticesCount = verticesCount;
    this->shader = shader;
}

void Model::initModel() {
    glGenBuffers(1, &this->VBO); // Generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertexSize * this->verticesCount * sizeof(float), this->points, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &this->VAO); // Generate the VAO
    glBindVertexArray(this->VAO); // Bind the VAO

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    // Set up vertex position attribute

    glVertexAttribPointer(0, this->vertexSize/2, GL_FLOAT, GL_FALSE, this->vertexSize * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0); // Enable vertex position attribute

    // Set up color attribute (assuming it starts right after the vertex position in the data)
    glVertexAttribPointer(1, this->vertexSize / 2, GL_FLOAT, GL_FALSE, this->vertexSize * sizeof(float), (GLvoid*)(this->vertexSize / 2 * sizeof(float)));
    glEnableVertexAttribArray(1); // Enable color attribute

    //glBindVertexArray(this->VAO); // Bind the VAO
}

void Model::bindArray() {
    glBindVertexArray(this->VAO);
}

int Model::getVerticesCount() {
    return this->verticesCount;
}