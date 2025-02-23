#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"


dae::TextComponent::TextComponent(GameObject* owner, std::string text, Font* font)
    : RenderComponent(owner), m_needsUpdate(true), m_text(text), m_font(font), m_textTexture(nullptr)
{
    SetText(text);
    
    m_position = GetOwner()->GetTransform()->GetWorldPosition();
    
    auto& renderer = Renderer::GetInstance();

    renderer.AddRenderComponent(this);
    
}

void dae::TextComponent::Update(float)
{
    if (m_needsUpdate)
    {
        TextToSurface();

    }

    m_position = GetOwner()->GetTransform()->GetWorldPosition();
    
    
}

void dae::TextComponent::FixedUpdate()
{
}

void dae::TextComponent::Render() const
{
    if (m_textTexture != nullptr)
    {
        Renderer::GetInstance().RenderTexture(*m_textTexture, m_position.x, m_position.y);
    }
}

void dae::TextComponent::SetText(const std::string& text)
{
    m_text = text;
    m_needsUpdate = true;
}

void dae::TextComponent::TextToSurface()
{
    const SDL_Color color = { 255, 255, 255, 255 }; // only white text is supported now
    const auto surface = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), SDL_Color{ 255, 255, 255 });
    if (surface == nullptr)
    {
        throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
    }
    auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface);
    if (texture == nullptr)
    {
        SDL_FreeSurface(surface);
        throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
    }
    SDL_FreeSurface(surface);
    m_textTexture = std::make_shared<Texture2D>(texture);
    m_needsUpdate = false;
}



