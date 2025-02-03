#include "Model.h"
#include "Shader.h"
#include <stdlib.h>
#include <stdio.h>


void Model::loadModel(std::string modelPath) {
    vector<float> data;
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // reduce the number of draw calls
        | aiProcess_JoinIdenticalVertices       // identifies and joins identical vertex data sets within all imported meshes
        | aiProcess_Triangulate;                // triangulates all faces of all meshes 

    const aiScene* scene = importer.ReadFile(modelPath, importOptions);

    if (scene) {
        aiMesh* mesh = scene->mMeshes[0];//Only first mesh 
        printf("Triangles:%d \n", mesh->mNumFaces);
        this->verticesCount = mesh->mNumFaces * 3;

        aiFace* f;
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < 3; j++)
            {
                int id = face.mIndices[j];

                //Vertex position
                aiVector3D pos = mesh->mVertices[id];
                data.push_back(pos.x);
                data.push_back(pos.y);
                data.push_back(pos.z);

                //Vertex normal
                aiVector3D nor = mesh->mNormals[id];
                data.push_back(nor.x);
                data.push_back(nor.y);
                data.push_back(nor.z);

                //Vertex uv
                aiVector3D uv = mesh->mTextureCoords[0][id];
                data.push_back(uv.x);
                data.push_back(uv.y);

            }
        }
    }
    else {
        std::cout << "An error occurred while loading model." << std::endl;
        exit(EXIT_FAILURE);
    };
    //Vertex Array Object (VAO)
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //enable vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 6));
}
        


Model::Model(const float points[], GLint vertexSize, int verticesCount, Shader* shader) {
	this->VBO = 0;
	this->VAO = 0;
	this->vertexSize = vertexSize;
	this->points = points;
    this->verticesCount = verticesCount;
    this->shader = shader;
    this->modelType = ModelLoadedType::NONE;
}

Model::Model(std::string modelPath, Shader* shader, ModelLoadedType type) {
    this->VBO = 0;
    this->VAO = 0;
    this->shader = shader;
    this->verticesCount = 0;
    loadModel(modelPath);
    this->modelType = type;
}

void Model::initModel() {
    glGenBuffers(1, &this->VBO); // Generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertexSize * this->verticesCount * sizeof(float), this->points, GL_STATIC_DRAW);

    glGenVertexArrays(1, &this->VAO); // Generate the VAO
    glBindVertexArray(this->VAO); // Bind the VAO

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    // Set up vertex position attribute

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, this->vertexSize * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0); // Enable vertex position attribute

    // Set up color attribute (assuming it starts right after the vertex position in the data)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, this->vertexSize * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); // Enable color attribute

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, this->vertexSize * sizeof(float), (GLvoid*)((6 * sizeof(float))));
    glEnableVertexAttribArray(2);

}

void Model::bindArray() {
    glBindVertexArray(this->VAO);  
}

int Model::getVerticesCount() {
    return this->verticesCount;
}

std::string Model::getModelPath() {
    return this->modelPath;
}

ModelLoadedType Model::getModelType() {
    return this->modelType;
}