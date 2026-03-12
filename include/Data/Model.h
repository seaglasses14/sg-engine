#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Mesh.h"

// Assimp may be slow when using the debug version of the IDE
// We can try using the release version if the loading times are slow
// For a release version, Assimp requires another build

// TO DO:
// - Add support to non texture material when importing


unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
	Model(char* path);
	void Draw(Shader& shader);

private:
	std::vector<Mesh> meshes;
	std::string directory;

	std::vector<Texture> textures_loaded;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};