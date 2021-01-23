#pragma once
class TerrainObject : public GameObject
{
public:
	TerrainObject(const String& name, bool oneWay) : m_oneWay(oneWay) {}
	TerrainObject(const String& name);

	EditorObjectType GetObjectType() const override;
	virtual GameObject* Copy() override;
	void InspectorDraw() override;

	bool m_oneWay = false;

	void ToJson(nlohmann::json& j) const override {
		GameObject::ToJson(j);
		j["Disable collision"] = m_disabledCollision;
		j["One way"] = m_oneWay;
	}
	void FromJson(const nlohmann::json& j) override {
		GameObject::FromJson(j);
		j.at("Disable collision").get_to(m_disabledCollision);
		j.at("One way").get_to(m_oneWay);
	}
};

