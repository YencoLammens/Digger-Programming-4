#pragma once
#include "RenderComponent.h"
#include <string>
#include <memory>
#include <chrono>
#include "Font.h"
#include "Texture2D.h"
#include "Transform.h"
namespace dae
{
	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent(GameObject* parent, std::shared_ptr<Font> font);
		~FPSComponent() override = default;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		

	private:
		void UpdateFPS();
		GameObject* m_owner;

		glm::vec3 m_position;

		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
		int m_frameCount;
		float m_elapsedTime;
		float m_fps;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTime;
	};
}


