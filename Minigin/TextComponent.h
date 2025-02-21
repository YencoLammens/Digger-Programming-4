#pragma once
#include <string>
#include <memory>
#include "Font.h"
#include "Texture2D.h"
#include "BaseComponent.h"
#include "GameObject.h"


namespace dae
{
	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> font);
		~TextComponent() = default;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void SetText(const std::string& text);


	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
		GameObject* m_owner;

		glm::vec3 m_position;

	};
}


