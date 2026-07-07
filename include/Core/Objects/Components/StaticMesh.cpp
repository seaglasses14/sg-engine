#include "StaticMesh.h"
#include "Core/Objects/Gobject.h"
#include "Core/Objects/Components/Transform.h"

StaticMesh::StaticMesh()
{
	label = "StaticMesh";
}

StaticMesh::StaticMesh(AssetHandle<Model> pModelHandle)
{
	label = "StaticMesh";
	model.handle = pModelHandle;
	Init();
}

void StaticMesh::Init()
{
	model.cached_data = AssetManager::Get().GetModel(model.handle);
	
	//materialInstances.clear();
}

std::vector<Property> StaticMesh::GetProperties()
{
	return
	{
		{ PropertyType::Asset_Model, &model, "Model", [](){} },
		{ PropertyType::Asset_Material, &materials, "Materials", [](){} },
		{ PropertyType::Bool, &isVisible, "IsVisible", [](){} }
	};
}

bool StaticMesh::SetModelHandle(AssetHandle<Model> pModelHandle)
{
	model.handle = pModelHandle;
	model.cached_data = AssetManager::Get().GetModel(model.handle);

	if(model.cached_data == nullptr)
		return false;

	materials.clear();
	for (unsigned int& value : model.cached_data->usedMaterialSlots)
	{
		AssetHandle<Material> materialHandle("");
		materials.insert({ value, AssetData<Material>{ materialHandle, nullptr } });
	}
	return true;
}

bool StaticMesh::SetMaterialAtSlot(AssetHandle<Material> pMaterialHandle, unsigned int slot)
{
	if (!materials.contains(slot))
		return false;
	materials[slot].handle = pMaterialHandle;
	materials[slot].cached_data = AssetManager::Get().GetMaterial(pMaterialHandle);
	return true;
}

void StaticMesh::Draw(RenderContext context)
{
	if (model.cached_data == nullptr)
		return;
	for (const auto& [key, value] : materials)
	{
		if(value.cached_data == nullptr)
			continue;
		value.cached_data->ChangeUniform("dirLight.direction", context.directLight_direction);
		value.cached_data->ChangeUniform("dirLight.color", context.directLight_color);
		value.cached_data->ChangeUniformMVP(owner->transform->GetModelMatrix(), context.view, context.projection, owner->transform->GetNormalMatrix());
		value.cached_data->Activate();
		model.cached_data->Draw(key);
	}
}

bool StaticMesh::IsVisible()
{
	return isVisible;
}
