#pragma once
#include <string>
#include <memory>
#include "RenderComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "Transform.h"

namespace dae
{
	class TextComponent : public RenderComponent
	{
	public:
		TextComponent(const std::string& text, std::shared_ptr<Font> font);
		~TextComponent() override = default;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void SetText(const std::string& text);
		virtual void SetPosition(float x, float y);


	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
		Transform m_transform;

	};
}


