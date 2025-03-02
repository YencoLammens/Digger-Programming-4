#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"


int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	//Imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

void dae::Renderer::ExecuteExercise1() const
{
	static int value = 10;



	ImGui::Begin("Exercise 1");

	//ImGui::InputText("##hidden", text, IM_ARRAYSIZE(text));
	ImGui::InputInt("##hidden", &value, 0, 0);
	ImGui::SameLine(0, 5);
	if (ImGui::Button("-")) {
		value--;
	}
	//ImGui::Button("-");
	ImGui::SameLine(0, 5);
	if (ImGui::Button("+")) {
		value++;
	}
	ImGui::SameLine(0, 10);
	ImGui::Text("# samples");
	ImGui::Button("Trash the cache");
	// Plot the graph
	//ImGui::PlotLines("NJUH 2", values, IM_ARRAYSIZE(values));

	ImGui::End();
}

void dae::Renderer::ExecuteExercise2() const
{
	static int value = 100;



	ImGui::Begin("Exercise 2");

	ImGui::InputInt("##hidden", &value, 0, 0);
	ImGui::SameLine(0, 5);
	if (ImGui::Button("-")) {
		value--;
	}
	ImGui::SameLine(0, 5);
	if (ImGui::Button("+")) {
		value++;
	}
	ImGui::SameLine(0, 10);
	ImGui::Text("# samples");
	if (ImGui::Button("Trash the cache with GameObject3D")) 
	{
		
	}
	if (ImGui::Button("Trash the cache with GameObject3DAlt")) 
	{
		
	}
	

	ImGui::End();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	//SceneManager::GetInstance().Render();
	
	for (const auto& component : m_renderComponentsArr)
	{
		component->Render();
	}
	//_____________________________________________________________________________________________
	//Imgui stuff
	ImGui_ImplOpenGL3_NewFrame();
	//no m_window overload?
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();


	//Exercise 1
	ExecuteExercise1();

	//Exercise 2
	ExecuteExercise2();
	

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//end of imgui stuff
	//______________________________________________________________________________________________
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }

void dae::Renderer::AddRenderComponent(RenderComponent* renderComponent)
{
	m_renderComponentsArr.push_back(renderComponent);
}


