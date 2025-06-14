#pragma once
#include <string>
#include <memory>
#include "Font.h"
#include "Texture2D.h"
#include "RenderComponent.h"
#include "GameObject.h"



namespace dae
{
	class TextComponent : public RenderComponent
	{
	public:
		TextComponent(GameObject* owner, std::string text, Font* font);
		~TextComponent() = default;
		TextComponent(const TextComponent&) = delete;
		TextComponent& operator=(const TextComponent&) = delete;
		TextComponent(TextComponent&&) = delete;
		TextComponent& operator=(TextComponent&&) = delete;

		void Update(float deltaTime) override;
		void SetText(const std::string& text);
		void TextToSurface();


	private:
		bool m_needsUpdate;
		std::string m_text;
		Font* m_font;
		std::shared_ptr<Texture2D> m_textTexture;

		glm::vec3 m_position;

		

	};
}


