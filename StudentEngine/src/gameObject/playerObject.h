#pragma once

class PlayerObject : public GameObject {
private:
	float m_movementSpeed;
	bool m_invincible;
	Timer m_invincibilityTimer;
	float m_jumpHeight;

	bool m_usingMultiSheet;
	StreamedTexture* m_idle;
	StreamedTexture* m_runLeft;
	StreamedTexture* m_runRight;
	StreamedTexture* m_jumpLeft;
	StreamedTexture* m_jumpRight;
	StreamedTexture* m_fallLeft;
	StreamedTexture* m_fallRight;
public:
	PlayerObject(const String& name);
	EditorObjectType GetObjectType() const override;
	void Update(const TimeStep& time) override;
	virtual GameObject* Copy() override;
	void InspectorDraw() override;
	PlayerObject* SetMovementSpeed(float speed);
	PlayerObject* SetInvinciblity(bool invincible);
	bool GetInvinciblity();
	bool GetInputLeft();
	bool GetInputRight();
	bool GetInputJump();

	void ToJson(nlohmann::json& j) const override {
		GameObject::ToJson(j);
		j["movement speed"] = m_movementSpeed;
		j["invincible"] = m_invincible;
		j["jump height"] = m_jumpHeight;
	}
	void FromJson(const nlohmann::json& j) override {
		GameObject::FromJson(j);
		j.at("movement speed").get_to(m_movementSpeed);
		j.at("invincible").get_to(m_invincible);
		j.at("jump height").get_to(m_jumpHeight);
	}

	bool Compare(const GameObject* other) override {
		return GameObject::Compare(other) && m_movementSpeed == ((PlayerObject*)other)->m_movementSpeed;
	}
};