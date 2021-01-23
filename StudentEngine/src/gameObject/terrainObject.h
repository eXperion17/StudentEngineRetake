#pragma once
class TerrainObject : public GameObject
{
public:
	TerrainObject(const String& name);
	EditorObjectType GetObjectType() const override;
	virtual GameObject* Copy() override;
	void InspectorDraw() override;

	void ToJson(nlohmann::json& j) const override {
		GameObject::ToJson(j);
		j["Disable collision"] = m_disabledCollision;
	}
	void FromJson(const nlohmann::json& j) override {
		GameObject::FromJson(j);
		j.at("Disable collision").get_to(m_disabledCollision);
	}
};

