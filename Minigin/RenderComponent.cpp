#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"

dae::RenderComponent::RenderComponent(GameObject* owner)
	: BaseComponent(owner), m_position{0, 0, 0}
{
	auto& renderer = Renderer::GetInstance();

	renderer.AddRenderComponent(this);
	
}

void dae::RenderComponent::Update(float)
{
	m_position = GetOwner()->GetTransform()->GetWorldPosition();
}

void dae::RenderComponent::FixedUpdate()
{
}

void dae::RenderComponent::Render() const
{
	if (m_texture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_texture, m_position.x, m_position.y);
	}
}

void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	m_texture = texture;
}

//void dae::RenderComponent::Update()
//{
//    //if (m_needsUpdate)
//    //{
//    //    const SDL_Color color = { 255, 255, 255, 255 }; // only white text is supported now
//    //    const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
//    //    if (surf == nullptr)
//    //    {
//    //        throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
//    //    }
//    //    auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
//    //    if (texture == nullptr)
//    //    {
//    //        throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
//    //    }
//    //    SDL_FreeSurface(surf);
//    //    m_textTexture = std::make_shared<Texture2D>(texture);
//    //    m_needsUpdate = false;
//
//    //}
//    //if (m_owner)
//    //{
//    //    m_position = m_owner->GetWorldPosition() * deltaTime;
//    //}
//}




