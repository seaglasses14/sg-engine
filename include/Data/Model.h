#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Data/Mesh.h"
#include "Data/Material.h"
#include <unordered_map>

// Assimp may be slow when using the debug version of the IDE
// We can try using the release version if the loading times are slow
// For a release version, Assimp requires  another build

// TO DO:
// - Add support to non texture material when importing

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
	Model(const char* path, bool gamma = false);
	void Draw(unsigned int slot = 0);

	std::vector<unsigned int> usedMaterialSlots;

private:
	//std::vector<ModelEntry> entries;
	std::unordered_map<unsigned int, std::vector<Mesh>> meshesMap;
	//std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;

	//std::vector<Texture> textures_loaded;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	//std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};