#pragma once
#include <glm.hpp>
#include "GameObject.h"

namespace dae
{
	class Transform : public BaseComponent
	{
	public:
		Transform(GameObject* parent);
		const glm::vec3& GetLocalPosition() const;
		void SetLocalPosition(const glm::vec3& pos);
		void SetLocalPosition(float x, float y, float z);
		const glm::vec3& GetWorldPosition();
		void UpdateWorldPosition();
		bool IsPositionDirty();
		void SetPositionDirty();

		void Update(float elapsedSec) override;
		void FixedUpdate() override;
		
	private:
		glm::vec3 m_localPosition;
		glm::vec3 m_worldPosition;
		bool m_positionIsDirty = false;
	};
}
