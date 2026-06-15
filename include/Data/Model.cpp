#include "Model.h"

#include <stb_image/stb_image.h>
#include "glad/glad.h"
#include "Core/Log.h"

Model::Model(char* path, bool gamma)
	:gammaCorrection(gamma)
{
	loadModel(path);
}
void Model::Draw()
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		AssetHandle<Material>& material = materials[meshes[i].materialSlot];
		AssetManager::Get().GetMaterial(material)->Activate();
		meshes[i].Draw();
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	// Other useful flags:
	// aiProcess_GenNormals
	// aiProcess_SplitLargeMeshes
	// aiProcess_OptimizeMeshes

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG_ERROR("ASSIMP::Error Description:");
		LOG_ERROR(importer.GetErrorString());
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Mesh newMesh = processMesh(mesh, scene);
		meshes.push_back(newMesh);
		materials.insert({ newMesh.materialSlot, AssetHandle<Material>{} });
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// Vertices

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}
		else
		{
			vertex.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		if (mesh->HasTextureCoords(0))
		{
			// We are assuming the model doesn't have multiple sets of Texture Coordinates
			// So we take the first
			vector.x = mesh->mTextureCoords[0][i].x;
			vector.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords.x = vector.x;
			vertex.TexCoords.y = vector.y;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		
		if (mesh->HasTangentsAndBitangents())
		{
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.Tangent = vector;
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.Bitangent = vector;
		}
		else
		{
			vertex.Tangent = glm::vec3(0.f, 0.f, 0.f);
			vertex.Bitangent = glm::vec3(0.f, 0.f, 0.f);
		}

		vertices.push_back(vertex);
	}

	// Indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	
	// MaterialSlot
	int materialSlot = 0;
	if (mesh->mMaterialIndex >= 0)
		materialSlot = mesh->mMaterialIndex;

	/*
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, TX_TYPE_DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, TX_TYPE_SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, TX_TYPE_NORMAL);
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, TX_TYPE_HEIGHT);
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}
	*/
	return Mesh(vertices, indices, materialSlot);
}
/*
std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}

	return textures;
}
*/
unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrChannels;
	// We use unsigned char* as a pointer to data
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format = GL_RED;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		else
		{
			LOG_ERROR(std::string("Texture has unsupported number of channels at path: ") + path);
		}	

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, (GLint)format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		LOG_ERROR(std::string("Texture failed to load at path: ") + path);
		stbi_image_free(data);
	}
	return textureID;
}