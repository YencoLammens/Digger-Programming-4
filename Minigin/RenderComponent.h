#pragma once
#include <memory>
#include "BaseComponent.h"
#include "Texture2D.h"
#include "Transform.h"
namespace dae
{
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(GameObject* owner);
		~RenderComponent() override = default;

		virtual void Update(float elapsedSec) override;
		virtual void FixedUpdate() override;
		virtual void Render() const;

		void SetTexture(const std::shared_ptr<Texture2D>& texture);
		//void SetPosition(float x, float y);


	private:
		std::shared_ptr<Texture2D> m_texture;

		glm::vec3 m_position;
	};
}


