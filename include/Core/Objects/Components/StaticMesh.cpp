#include "StaticMesh.h"
#include "Core/Objects/Gobject.h"
#include "Core/Objects/Components/Transform.h"

StaticMesh::StaticMesh()
{
	label = "StaticMesh";
}

StaticMesh::StaticMesh(AssetHandle<Model> pModelHandle)
	: modelHandle(pModelHandle)
{
	label = "StaticMesh";
	Init();
}

void StaticMesh::Init()
{
	cached_model = AssetManager::Get().GetModel(modelHandle);
	
	//materialInstances.clear();
}

std::vector<Property> StaticMesh::GetProperties()
{
	return
	{
		{ PropertyType::AssetHandle_Model, &modelHandle, "Model", [](){} },
		{ PropertyType::Bool, &isVisible, "IsVisible", [](){} }
	};
}

bool StaticMesh::SetModelHandle(AssetHandle<Model> pModelHandle)
{
	modelHandle = pModelHandle;
	cached_model = AssetManager::Get().GetModel(modelHandle);

	if(cached_model == nullptr)
		return false;

	materials.clear();
	for (unsigned int& value : cached_model->usedMaterialSlots)
	{
		materials.insert({ value, AssetHandle<Material>("") });
	}
	return true;
}

bool StaticMesh::SetMaterialAtSlot(AssetHandle<Material> pMaterialHandle, unsigned int slot)
{
	if (!materials.contains(slot))
		return false;
	materials[slot] = pMaterialHandle;
	return true;
}

void StaticMesh::Draw(RenderContext context)
{
	if (cached_model == nullptr)
		return;
	for (const auto& [key, value] : materials)
	{
		Material* mat = AssetManager::Get().GetMaterial(value);
		mat->ChangeUniform("dirLight.direction", context.directLight_direction);
		mat->ChangeUniform("dirLight.color", context.directLight_color);
		mat->ChangeUniformMVP(owner->transform->GetModelMatrix(), context.view, context.projection, owner->transform->GetNormalMatrix());
		mat->Activate();
		cached_model->Draw(key);
	}
}

bool StaticMesh::IsVisible()
{
	return isVisible;
}
