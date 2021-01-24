#include "stdafx.h"

TrampolineObject::TrampolineObject(const String& name) : GameObject(name, false) {
	SetTexture(GetAssetManager()->Get<StreamedTexture>("Trampoline"));
	SetSize(Vector2(64, 32));
	SetColor(Color::Yellow());

	SetOnCollision([&](GameObject* self, GameObject* other, CollisionType type) {
		OnCollision(self, other, type);
		return false;
	});
	m_layer = "Objects";
}

EditorObjectType TrampolineObject::GetObjectType() const {
	return EditorObjectType::TRAMPOLINE;
}

GameObject* TrampolineObject::Copy() {
	return new GameObject(*this);
}

void TrampolineObject::OnCollision(GameObject* self, GameObject* other, CollisionType type) {
	if (other->IsOfType<PlayerObject>() || other->IsOfType<WalkingEnemy>()) {
		PhysicsObject obj = other->m_physicsObject;

		if (type == CollisionType::TOP || obj.m_velocity.y < 0) {
			other->m_physicsObject.m_velocity.y = GetVelocityOnJump(obj);
		}
	}
}

float TrampolineObject::GetVelocityOnJump(PhysicsObject obj) {
	obj.m_velocity.y = Math::Abs(obj.m_velocity.y * 0.2f) + m_trampolineStrength;

	if (obj.m_velocity.y > m_trampolineStrength * 1.2f) {
		obj.m_velocity.y = m_trampolineStrength * 1.2f;
	}

	return obj.m_velocity.y;
}

void TrampolineObject::InspectorDraw() {
	GameObject::InspectorDraw();
	InspectorDrawer::Float(this, "Bounce Strength", m_trampolineStrength);
}