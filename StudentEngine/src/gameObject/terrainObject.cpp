#include "stdafx.h"

TerrainObject::TerrainObject(const String& name) : GameObject(name, false) {
	SetSize(Vector2(64, 64));
	Set9Slice(true);
	SetTexture(GetAssetManager()->Get<StreamedTexture>("Basic Tile"));
	m_layer = "Background";
}

/*TerrainObject::TerrainObject(const String& name, bool oneWay) : GameObject(name, false) {
	SetSize(Vector2(64, 64));
	Set9Slice(true);
	SetTexture(GetAssetManager()->Get<StreamedTexture>("9slice"));
	m_layer = "Background";
	m_oneWay = oneWay;
}*/

EditorObjectType TerrainObject::GetObjectType() const {
	return EditorObjectType::TERRAIN;
}

GameObject* TerrainObject::Copy() {
	return new TerrainObject(*this);
}

void TerrainObject::InspectorDraw() {
	GameObject::InspectorDraw();
	InspectorDrawer::Bool(this, "Disable collision", m_disabledCollision);
	InspectorDrawer::Bool(this, "One way", m_oneWay);

	ImGui::AlignTextToFramePadding();
	ImGui::Text("Terrain Texture");
	float width = ImGui::GetContentRegionAvail().x;
	const char* buttonText = "Select";
	ImGui::SameLine(width - 8.0 - ImGui::CalcTextSize(m_sprite.m_texture->GetName().c_str(), NULL, true).x - ImGui::CalcTextSize(buttonText, NULL, true).x);
	ImGui::LabelText("##terrainTexture", m_sprite.m_texture->GetName().c_str());
	ImGui::SameLine(width - ImGui::CalcTextSize(buttonText, NULL, true).x);
	if (ImGui::Button("Select")) {
		GetAssetSelect()->PrepareValidTextures("Terrain", [&](AssetBase* asset) {
			GameObject* selectedObject = GetEditorScene()->GetHierarchy().GetSelected();
			if (selectedObject->IsOfType<TerrainObject>()) {
				// Necessary to reset the sprite
				m_sprite = Sprite();
				SetAtlasValues(1, 0, 0);
				m_sprite.m_9Slice = true;
				static_cast<PlayerObject*>(selectedObject->SetTexture((StreamedTexture*)asset));
			}
		});
		GetAssetSelect()->Open();
	}
}