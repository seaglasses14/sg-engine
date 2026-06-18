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
	StaticMesh();
	StaticMesh(AssetHandle<Model> pModelHandle);

	std::vector<Property> GetProperties() override;

	bool SetModelHandle(AssetHandle<Model> pModelHandle);
	bool SetMaterialAtSlot(AssetHandle<Material> pMaterialHandle, unsigned int slot = 0);
	void Draw(RenderContext context) override;
	bool IsVisible() override;

	bool isVisible = true;

private:
	AssetHandle<Model> modelHandle;
	Model* cached_model = nullptr;
	std::unordered_map<unsigned int, AssetHandle<Material>> materials;

	//std::optional<AssetHandle<Material>> overrideMaterial;
	//std::vector<Material> materialInstances;

	void Init();
};