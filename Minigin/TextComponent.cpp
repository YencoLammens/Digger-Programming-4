#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font)
    : m_needsUpdate(true), m_text(text), m_font(font), m_textTexture(nullptr)
{
    SetText(text);
}

void dae::TextComponent::Update()
{
    if (m_needsUpdate)
    {
        const SDL_Color color = { 255, 255, 255, 255 }; // only white text is supported now
        const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
        if (surf == nullptr)
        {
            throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
        }
        auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
        if (texture == nullptr)
        {
            throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
        }
        SDL_FreeSurface(surf);
        m_textTexture = std::make_shared<Texture2D>(texture);
        m_needsUpdate = false;
    }
}

void dae::TextComponent::Render() const
{
    if (m_textTexture != nullptr)
    {
        const auto& pos = m_transform.GetPosition();
        Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
    }
}

void dae::TextComponent::SetText(const std::string& text)
{
    m_text = text;
    m_needsUpdate = true;
}

void dae::TextComponent::SetPosition(float x, float y)
{
    m_transform.SetPosition(x, y, 0.0f);
}

dae::BaseComponent::Type dae::TextComponent::GetType() const
{
    return Type::Text;
}
