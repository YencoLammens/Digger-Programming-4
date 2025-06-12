#pragma once
#include <SDL.h>
#include "Singleton.h"
#include "RenderComponent.h"
#include <chrono>

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const float x, const float y, const float angleDegrees) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float angleDegrees, bool flipX) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
		void AddRenderComponent(RenderComponent*);
		void RemoveRenderComponent(RenderComponent* renderComponent);
		


		
		

	private:
		std::vector<RenderComponent*> m_renderComponentsArr;
	};
}

