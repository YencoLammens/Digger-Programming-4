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
		RenderComponent() = default;
		~RenderComponent() override = default;

		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() const;

		void SetTexture(const std::shared_ptr<Texture2D>& texture);
		void SetPosition(float x, float y);

		Type GetType() const override;

	private:
		std::shared_ptr<Texture2D> m_texture;
		Transform m_transform;
	};
}


