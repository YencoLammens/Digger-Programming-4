#pragma once
#include "BaseComponent.h"
#include <glm.hpp>
#include "GameObject.h"
#include "Transform.h"
namespace dae
{
	class RotatorComponent : public BaseComponent
	{
		
		public:
			RotatorComponent(GameObject* owner, const glm::vec3& targetPosition);
			~RotatorComponent() override = default;

			void Update(float deltaTime) override;
			void FixedUpdate() override;

			glm::vec3 RotateAroundTarget(float centerX, float centerY, float pointX, float pointY, float angleInDegrees);


		private:
			glm::vec3 m_targetPosition;
	};
}


