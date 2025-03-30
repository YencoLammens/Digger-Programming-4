#include "FPSComponent.h"
#include "Renderer.h"
#include <SDL_ttf.h>
#include <stdexcept>
#include <iostream>

dae::FPSComponent::FPSComponent(GameObject* owner, std::shared_ptr<Font> font)
	: RenderComponent(owner), m_font(font), m_frameCount(0), m_elapsedTime(0), m_fps(0), m_needsUpdate(true), m_position{0,0,0}
{
	
	m_lastTime = std::chrono::high_resolution_clock::now();
    auto& renderer = Renderer::GetInstance();
    _textComponent = std::make_unique<TextComponent>(owner, std::to_string(m_fps), font.get());

    renderer.AddRenderComponent(this);
}

void dae::FPSComponent::Update(float deltaTime)
{
    m_frameCount++;
    m_fps = 1 / deltaTime;
    
    UpdateFPS();

    m_position = GetOwner()->GetTransform()->GetWorldPosition();

}



void dae::FPSComponent::UpdateFPS()
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << m_fps;
    m_text = stream.str() + " FPS";

    _textComponent->SetText(m_text);
    _textComponent->TextToSurface();
}
