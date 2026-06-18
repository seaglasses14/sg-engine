#include "ObjectFactory.h"
#include "Core/Log.h"
#include "Core/Objects/GObject.h"
#include "Core/Objects/Components/StaticMesh.h"
#include "Core/Objects/Components/CDirectLight.h"
#include "Core/Objects/Components/Transform.h"
#include <iostream>
#include "object.h"
#include "glm/glm.hpp"

/*
Object Shapes::genPlane(Material* pMaterial, float size)
{
	if (size <= 0)
		LOG_ERROR("SHAPES_PLANE: Invalid size");
	unsigned int VAO, VBO;
	std::vector<float> data;
	float halfSize = size / 2;
	data.insert(data.end(), { -halfSize, 0,  halfSize });
	data.insert(data.end(), { halfSize, 0,  halfSize });
	data.insert(data.end(), { -halfSize, 0, -halfSize });
	data.insert(data.end(), { -halfSize, 0, -halfSize });
	data.insert(data.end(), { halfSize, 0,  halfSize });
	data.insert(data.end(), { halfSize, 0, -halfSize });

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return Object(VAO, VBO, 0, pMaterial, true, false, data.size());
}

Object Shapes::genSimpleCube(Material* pMaterial, float edge_length)
{
	if (edge_length <= 0)
		LOG_ERROR("SHAPES_CUBE: Invalid size");
	unsigned int VAO, VBO, EBO;
	std::vector<float> data;
	float halfSize = edge_length / 2;
	
	data.insert(data.end(), {
		-halfSize, -halfSize, -halfSize,
		 halfSize, -halfSize, -halfSize,
		 halfSize,  halfSize, -halfSize,
		-halfSize,  halfSize, -halfSize,
		-halfSize, -halfSize,  halfSize,
		 halfSize, -halfSize,  halfSize,
		 halfSize,  halfSize,  halfSize,
		-halfSize,  halfSize,  halfSize
	});
	
	
	std::vector<unsigned int> indices;
	indices.insert(indices.end(), {
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1
	});
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return Object(VAO, VBO, EBO, pMaterial, true, true, indices.size());
}

Object Shapes::genCube(Material* pMaterial, float edge_length)
{
	if (edge_length <= 0)
		LOG_ERROR("SHAPES_CUBE: Invalid size");
	unsigned int VAO, VBO; // EBO;
	std::vector<float> data;
	float halfSize = edge_length / 2;
	
	//data.insert(data.end(), {
	//	-halfSize, -halfSize, -halfSize,
	//	 halfSize, -halfSize, -halfSize,
	//	 halfSize,  halfSize, -halfSize,
	//	-halfSize,  halfSize, -halfSize,
	//	-halfSize, -halfSize,  halfSize,
	//	 halfSize, -halfSize,  halfSize,
	//	 halfSize,  halfSize,  halfSize,
	//	-halfSize,  halfSize,  halfSize
	//});
	
	data.insert(data.end(), {
		// positions // normals // texture coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	});
	
	//std::vector<unsigned int> indices;
	//indices.insert(indices.end(), {
	//	0, 1, 3, 3, 1, 2,
	//	1, 5, 2, 2, 5, 6,
	//	5, 4, 6, 6, 4, 7,
	//	4, 0, 7, 7, 0, 3,
	//	3, 2, 7, 7, 2, 6,
	//	4, 5, 0, 0, 5, 1
	//});
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	return Object(VAO, VBO, 0, pMaterial, true, false, data.size());
}
*/
Object* ObjectFactory::genWorldGrid(Material* pMaterial, unsigned int size, float stride)
{
	if (size <= 0 && stride <= 0)
		LOG_ERROR("SHAPES_WORLDGRID: Invalid size or stride");
	unsigned int VAO, VBO;
	std::vector<float> data;
	unsigned int halfSize = size / 2;
	float startX = static_cast<float>(size - 1) * stride / 2;
	float startZ = static_cast<float>(size - 1) * stride / 2;
	for (float i = 0.0f; i < size; i += 1.0f)
	{
		data.insert(data.end(), { -startX + i * stride, 0,  startZ });
		data.insert(data.end(), { -startX + i * stride, 0, -startZ });
		data.insert(data.end(), { -startX, 0, startZ - i * stride });
		data.insert(data.end(), {  startX, 0, startZ - i * stride });
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return new Object(VAO, VBO, 0, pMaterial, false, false, data.size());
}
/*
Object Shapes::genUVSphere(Material* pMaterial, int stacks, int slices, float radius)
{
	if (stacks <= 0 && slices <= 0)
		LOG_ERROR("SHAPES_UVSPHERE: Invalid stacks or slices");
	unsigned int VAO, VBO, EBO;
	const float PI = 3.14159f;

	std::vector<float> data;
	std::vector<unsigned int> indices;

	for (int i = 0; i <= stacks; ++i)
	{
		float V = static_cast<float>(i) / static_cast<float>(stacks);
		float phi = V * PI;

		for (int j = 0; j <= slices; ++j)
		{
			float U = static_cast<float>(j) / static_cast<float>(slices);
			float theta = U * (PI * 2);

			float x = cos(theta) * sin(phi) * radius;
			float y = cos(phi) * radius;
			float z = sin(theta) * sin(phi) * radius;

			//Position
			data.push_back(x);
			data.push_back(y);
			data.push_back(z);
			
			//Normals
			glm::vec3 normal(x, y, z);
			normal = glm::normalize(normal);

			data.push_back(normal.x);
			data.push_back(normal.y);
			data.push_back(normal.z);
			
			//Tex Coords
			data.push_back(1 - U);
			data.push_back(1 - V);
		}
	}

	for (int i = 0; i < (slices + 1) * stacks; ++i)
	{
		indices.push_back(static_cast<unsigned int>(i));
		indices.push_back(static_cast<unsigned int>(i + slices + 1));
		indices.push_back(static_cast<unsigned int>(i + slices));

		indices.push_back(static_cast<unsigned int>(i + slices + 1));
		indices.push_back(static_cast<unsigned int>(i));
		indices.push_back(static_cast<unsigned int>(i + 1));
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	return Object(VAO, VBO, EBO, pMaterial, true, true, indices.size());
}
*/

GObject* ObjectFactory::Empty(const std::string& label, Scene* scene)
{
	return new GObject(label, scene);
}

GObject* ObjectFactory::Cube(const std::string& label, Scene* scene)
{
	GObject* obj = new GObject(label, scene);
	StaticMesh* sMesh = new StaticMesh();

	sMesh->SetModelHandle(AssetHandle<Model>({"assets/raw/models/DefaultCube.obj"}));
	sMesh->SetMaterialAtSlot(AssetHandle<Material>({"DefaultMaterial"}));
	sMesh->owner = obj;
	obj->components.push_back(sMesh);
	return obj;
}

GObject* ObjectFactory::DirectLight(const std::string &label, Scene* scene)
{
	GObject* obj = new GObject(label, scene);
	obj->transform->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

	StaticMesh* sMesh = new StaticMesh();
	sMesh->SetModelHandle(AssetHandle<Model>({"assets/raw/models/DefaultCube.obj"}));
	sMesh->SetMaterialAtSlot(AssetHandle<Material>({"BaseMaterial"}));
	sMesh->owner = obj;

	CDirectLight* light = new CDirectLight();
	light->owner = obj;
	light->SetEnabled();

	obj->components.push_back(sMesh);
	obj->components.push_back(light);

    return obj;
}
