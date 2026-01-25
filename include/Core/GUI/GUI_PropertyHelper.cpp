#include "Core/GUI/GUI_PropertyHelper.h"
#include "imgui.h"

void GUI_PropertyHelper::DrawWidget(Property& pr)
{
	switch (pr.type)
	{
	case Vec3f:
		WidgetVec3f(pr);
		break;
	default:
		break;
	}
}

void GUI_PropertyHelper::WidgetVec3f(Property& pr)
{
	ImGui::DragFloat3(pr.label.c_str(), static_cast<float*>(pr.data), 1.f, 0.f, 0.f, "%.3f", ImGuiSliderFlags_ColorMarkers);
}
