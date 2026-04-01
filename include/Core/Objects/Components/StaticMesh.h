#pragma once

#include "Core/Objects/Components/Component.h"
#include "Core/Interfaces/Renderable.h"
#include "Data/Model.h"
#include "Data/Material.h"
#include <optional>

// TO DO: Add Renderable Interface 

class StaticMesh: public Component, public IRenderable
{
public:
	StaticMesh(AssetHandle<Model> pModelHandle);

	std::vector<Property> GetProperties() override;
	void Draw() override;

private:
	AssetHandle<Model> modelHandle;
	Model* cached_model = nullptr;

	std::optional<AssetHandle<Material>> overrideMaterial;
	std::vector<Material> materialInstances;

	void Init();
};