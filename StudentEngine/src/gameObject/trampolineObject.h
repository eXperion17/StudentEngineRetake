#pragma once
class TrampolineObject : public GameObject {
private:
	float m_trampolineStrength = 35;
public:
	TrampolineObject(const String& name);
	EditorObjectType GetObjectType() const override;
	virtual GameObject* Copy() override;
	void InspectorDraw() override;
	void OnCollision(GameObject* self, GameObject* other, CollisionType type);

	float GetVelocityOnJump(PhysicsObject obj);

	void ToJson(nlohmann::json& j) const override {
		GameObject::ToJson(j);
		j["Bounce Strength"] = m_trampolineStrength;
	}

	void FromJson(const nlohmann::json& j) override {
		GameObject::FromJson(j);
		j.at("Bounce Strength").get_to(m_trampolineStrength);
	}
};

