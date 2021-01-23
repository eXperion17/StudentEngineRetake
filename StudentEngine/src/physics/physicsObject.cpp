#include "stdafx.h"

void PhysicsObject::Update(const TimeStep& time) {
	if (!m_dynamic) return;
	Move(m_gameObject->m_transform);
}

bool PhysicsObject::CheckCollision(float xa, float ya) {
	for each (auto layer in GetActiveScene()->GetHierarchy().m_layers) {
		for each (auto other in layer->m_objects) {
			/// If any of the two colliding gameObjects ignores collision, then we just skip over it
			if (other->m_disabledCollision || m_gameObject->m_disabledCollision)
				continue;

			if (m_gameObject->m_transform.CollidesWith(other, xa, ya)) {
				auto type = GetCollisionType(xa, ya);
				
				/// Check to see if its a one way, if it is and we collide from the bottom we just skip over it
				if (other->GetObjectType() == EditorObjectType::TERRAIN) {
					TerrainObject* terr = (TerrainObject*)other;
					if (terr->m_oneWay && type == CollisionType::BOTTOM) {
						continue;
					}
				}

				m_gameObject->OnCollision(other, type);
				if (other->OnCollision(m_gameObject, type)) return true;
			}
		}
	}
	return false;
}