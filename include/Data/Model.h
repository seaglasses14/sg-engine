#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Data/Mesh.h"
#include "Data/Material.h"

// Assimp may be slow when using the debug version of the IDE
// We can try using the release version if the loading times are slow
// For a release version, Assimp requires  another build

// TO DO:
// - Add support to non texture material when importing


unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

struct ModelEntry
{
	Mesh mesh;
	Material material;
};

class Model
{
public:
	Model(char* path, bool gamma = false);
	void Draw(Shader& shader);

private:
	std::vector<ModelEntry> entries;
	std::string directory;
	bool gammaCorrection;

	std::vector<Texture> textures_loaded;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};