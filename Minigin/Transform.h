#pragma once
#include <glm.hpp>
#include "GameObject.h"

namespace dae
{
	class Transform final
	{
	public:
		Transform(GameObject* parent);
		const glm::vec3& GetLocalPosition() const;
		void SetLocalPosition(const glm::vec3& pos);
		void SetLocalPosition(float x, float y, float z);
		const glm::vec3& GetWorldPosition();
		void UpdateWorldPosition();
		void IsPositionDirty(bool isDirty);
		
	private:
		glm::vec3 m_localPosition;
		glm::vec3 m_worldPosition;
		bool m_positionIsDirty = false;
		GameObject* m_parent = nullptr;
	};
}
