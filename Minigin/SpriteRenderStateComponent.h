#pragma once
#include "BaseComponent.h"

namespace dae
{
	class SpriteRenderStateComponent :public BaseComponent
	{
	public:
		SpriteRenderStateComponent(GameObject* owner);

		void Update(float) override {}
		void FixedUpdate(float) override {}

		void SetRotation(float angle);
		float GetRotation() const;

		void SetFlipX(bool flip);
		bool GetFlipX() const;

	private:
		float m_rotation = 0.f;
		bool m_flipX = false;
	};
}

