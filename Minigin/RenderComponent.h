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
		RenderComponent(const RenderComponent&) = delete;
		RenderComponent& operator=(const RenderComponent&) = delete;
		RenderComponent(RenderComponent&&) = delete;
		RenderComponent& operator=(RenderComponent&&) = delete;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float fixedTimeStep) override;
		virtual void Render() const;

		void SetTexture(const std::shared_ptr<Texture2D>& texture);
		//void SetPosition(float x, float y);

		void SetEnabled(bool enabled) { m_enabled = enabled; }

	private:
		std::shared_ptr<Texture2D> m_texture;

		glm::vec3 m_position;

		bool m_enabled{ true };
	};
}


