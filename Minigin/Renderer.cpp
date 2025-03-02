#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include <chrono>
#include <iostream>
#include "include/imgui_plot.h"


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










//All functions that have to do with IMGUI and the Graph plot generation, if you are reading this Mr. Vanden Abeele, I'm sorry, 
//I at least wanted to do you the favour of putting it in the "beerput" down here
//I did not reuse the code because of lack of time, and wanting to prioritize making it work, later on making the code more bearable

void dae::Renderer::ExecuteExercise1() const
{
	static int amountOfSamples{ 10 };
	static int lastAmountOfSamples = lastAmountOfSamples;
	const static int amountOfCoordinates{ 11 };
	static std::vector<float> graphData(amountOfCoordinates);
	static bool showGraph = false;



	ImGui::Begin("Exercise 1");

	ImGui::InputInt("##hidden", &amountOfSamples, 0, 0);
	ImGui::SameLine(0, 5);
	if (ImGui::Button("-"))
	{
		amountOfSamples--;
	}
	//ImGui::Button("-");
	ImGui::SameLine(0, 5);
	if (ImGui::Button("+"))
	{
		amountOfSamples++;
	}
	ImGui::SameLine(0, 11);
	ImGui::Text("# samples");
	if (ImGui::Button("Trash the cache"))
	{

		lastAmountOfSamples = amountOfSamples;

		//Calculate the times
		graphData = TakeTimesExercise1(lastAmountOfSamples);

		showGraph = true;
	}

	if (showGraph)
	{
		ImGui::PlotConfig conf;
		conf.values.ys = graphData.data();
		conf.values.count = amountOfCoordinates;
		conf.values.color = ImColor(255, 0, 0);
		conf.scale.min = -1;
		conf.scale.max = graphData[0];
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 200);
		conf.line_thickness = 2.f;
		ImGui::Plot("##graph", conf);
	}





	ImGui::End();
}

void dae::Renderer::ExecuteExercise2() const
{
	static int amountOfSamples{ 100 };
	static int lastAmountOfSamples = lastAmountOfSamples;
	const static int amountOfCoordinates{ 11 };
	static std::vector<float> graphData(amountOfCoordinates);
	static std::vector<float> graphDataAlt(amountOfCoordinates);
	static bool showGraph2 = false;
	static bool showGraph2Alt = false;




	ImGui::Begin("Exercise 2");

	ImGui::InputInt("##hidden", &amountOfSamples, 0, 0);
	ImGui::SameLine(0, 5);
	if (ImGui::Button("-")) {
		amountOfSamples--;
	}
	ImGui::SameLine(0, 5);
	if (ImGui::Button("+")) {
		amountOfSamples++;
	}
	ImGui::SameLine(0, 10);
	ImGui::Text("# samples");
	if (ImGui::Button("Trash the cache with GameObject3D"))
	{
		lastAmountOfSamples = amountOfSamples;

		//Calculate the times
		graphData = TakeTimesExercise2(lastAmountOfSamples);

		showGraph2 = true;
	}

	if (showGraph2)
	{
		ImGui::PlotConfig conf;

		conf.values.ys = graphData.data();
		conf.values.count = amountOfCoordinates;
		conf.values.color = ImColor(0, 255, 0);
		conf.scale.min = -1;
		conf.scale.max = graphData[0];
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 200);
		conf.line_thickness = 2.f;
		ImGui::Plot("##graph", conf);

	}
	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		lastAmountOfSamples = amountOfSamples;

		//Calculate the times
		graphDataAlt = TakeTimesExercise2Alt(lastAmountOfSamples);

		showGraph2Alt = true;
	}

	if (showGraph2Alt)
	{
		ImGui::PlotConfig conf;

		conf.values.ys = graphDataAlt.data();
		conf.values.count = amountOfCoordinates;
		conf.values.color = ImColor(0, 0, 255);
		conf.scale.min = -1;
		conf.scale.max = graphDataAlt[0];
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 200);
		conf.line_thickness = 2.f;
		ImGui::Plot("##graph2", conf);

	}


	if (showGraph2 && showGraph2Alt)
	{
		ImGui::Text("Combined:");
		ImGui::PlotConfig conf;
		//Both should be plotted, but the colors don't make an appearance, or it just doesn't draw it in general even if the values are there
		const float* graphDataCombo[] = { graphData.data(), graphDataAlt.data() };
		conf.values.ys_list = graphDataCombo;
		conf.values.count = amountOfCoordinates;
		const ImU32 colorCombo[] = { ImColor(0, 255, 0), ImColor(0, 0, 255) };
		conf.values.colors = colorCombo;
		conf.scale.min = -1;

		if (graphData[0] > graphDataAlt[0])
		{
			conf.scale.max = graphData[0];
		}
		else
		{
			conf.scale.max = graphDataAlt[0];
		}
		
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(200, 200);
		conf.line_thickness = 2.f;
		
		ImGui::Plot("##graphs", conf);
	}



	ImGui::End();
}




struct TransformGameObject3D
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};

class GameObject3D
{
public:
    TransformGameObject3D transform;
    int ID{0};
};

class GameObject3DAlt
{
public:
	TransformGameObject3D* transform;
	int ID{ 0 };
};

std::vector<float> dae::Renderer::TakeTimesExercise1(const int& amountOfSamples) const
{
	
	//std::vector<int> massiveIntArray = std::unique_ptr<int>;
	//std::vector<int> massiveIntArray(number);
	std::vector<float> tempVector; //gets the timeDifference values every loop
	std::vector<std::vector<float>> timingsVector; //stores the vectors with all their time differences
	std::vector<float> averageOfAllTimingsVector; //averages of all the time difference vectors
	const int numberOfInts{ 1053200 };
	int numberOfSteps{ 11 }; //amount of steps that is always the same when 2^11
	
	std::vector<std::unique_ptr<int>> massiveIntArray;
	for (int i = 0; i < numberOfInts; ++i)
	{
		massiveIntArray.push_back(std::make_unique<int>(i));
	}
	const auto startTime{ std::chrono::high_resolution_clock::now() };

	//Stuffs all the timings into the timingsVector per sampleSize
	for (int sampleIdx{0}; sampleIdx < amountOfSamples; ++sampleIdx)
	{
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto startTimePerStepsize{ std::chrono::high_resolution_clock::now() };


			for (int i = 0; i < massiveIntArray.size(); i += stepsize)
			{

				*massiveIntArray[i] *= 2;
				//startTimePerStepsize = std::chrono::high_resolution_clock::now();

			}
			auto endTimePerStepsize = std::chrono::high_resolution_clock::now();
			const auto timeDifference = std::chrono::duration_cast<std::chrono::microseconds>(endTimePerStepsize - startTimePerStepsize).count();

			std::cout << "stepsize " << stepsize << ": " << timeDifference << std::endl;

			tempVector.push_back(static_cast<float>(timeDifference));

		}


		timingsVector.push_back(tempVector);

		
	}
	tempVector.clear();
	
	//Accumulates and calculates the average time per stepSize, and stuffs it into averagesVector
	float accumulator{0};
	for (int stepSize = 1; stepSize < numberOfSteps; ++stepSize)
	{
		

			for (int sampleIdx{ 0 }; sampleIdx < timingsVector.size(); ++sampleIdx)
			{
				accumulator += timingsVector[sampleIdx][stepSize];

				

			}
			accumulator /= numberOfSteps;
			averageOfAllTimingsVector.push_back(accumulator);
	}
	return averageOfAllTimingsVector;

}

std::vector<float> dae::Renderer::TakeTimesExercise2(const int& amountOfSamples) const
{
	std::vector<float> tempVector; //gets the timeDifference values every loop
	std::vector<std::vector<float>> timingsVector; //stores the vectors with all their time differences
	std::vector<float> averageOfAllTimingsVector; //averages of all the time difference vectors
	const int numberOfInts{ 1053200 };
	int numberOfSteps{ 11 }; //amount of steps that is always the same when 2^11

	std::vector<std::unique_ptr<GameObject3D>> massiveGOArray;
	for (int i = 0; i < numberOfInts; ++i)
	{
		massiveGOArray.push_back(std::make_unique<GameObject3D>());
	}
	const auto startTime{ std::chrono::high_resolution_clock::now() };

	//Stuffs all the timings into the timingsVector per sampleSize
	for (int sampleIdx{ 0 }; sampleIdx < amountOfSamples; ++sampleIdx)
	{
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto startTimePerStepsize{ std::chrono::high_resolution_clock::now() };


			for (int i = 0; i < massiveGOArray.size(); i += stepsize)
			{

				massiveGOArray[i]->ID += 2;
				//startTimePerStepsize = std::chrono::high_resolution_clock::now();

			}
			auto endTimePerStepsize = std::chrono::high_resolution_clock::now();
			const auto timeDifference = std::chrono::duration_cast<std::chrono::microseconds>(endTimePerStepsize - startTimePerStepsize).count();

			std::cout << "stepsize " << stepsize << ": " << timeDifference << std::endl;

			tempVector.push_back(static_cast<float>(timeDifference));

		}


		timingsVector.push_back(tempVector);


	}
	tempVector.clear();

	//Accumulates and calculates the average time per stepSize, and stuffs it into averagesVector
	float accumulator{ 0 };
	for (int stepSize = 1; stepSize < numberOfSteps; ++stepSize)
	{


		for (int sampleIdx{ 0 }; sampleIdx < timingsVector.size(); ++sampleIdx)
		{
			accumulator += timingsVector[sampleIdx][stepSize];



		}
		accumulator /= numberOfSteps;
		averageOfAllTimingsVector.push_back(accumulator);
	}
	return averageOfAllTimingsVector;

}

std::vector<float> dae::Renderer::TakeTimesExercise2Alt(const int& amountOfSamples) const
{
	std::vector<float> tempVector; //gets the timeDifference values every loop
	std::vector<std::vector<float>> timingsVector; //stores the vectors with all their time differences
	std::vector<float> averageOfAllTimingsVector; //averages of all the time difference vectors
	const int numberOfInts{ 1053200 };
	int numberOfSteps{ 11 }; //amount of steps that is always the same when 2^11

	std::vector<std::unique_ptr<GameObject3DAlt>> massiveGOArray;
	for (int i = 0; i < numberOfInts; ++i)
	{
		massiveGOArray.push_back(std::make_unique<GameObject3DAlt>());
	}
	const auto startTime{ std::chrono::high_resolution_clock::now() };

	//Stuffs all the timings into the timingsVector per sampleSize
	for (int sampleIdx{ 0 }; sampleIdx < amountOfSamples; ++sampleIdx)
	{
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto startTimePerStepsize{ std::chrono::high_resolution_clock::now() };


			for (int i = 0; i < massiveGOArray.size(); i += stepsize)
			{

				massiveGOArray[i]->ID += 2;
				//startTimePerStepsize = std::chrono::high_resolution_clock::now();

			}
			auto endTimePerStepsize = std::chrono::high_resolution_clock::now();
			const auto timeDifference = std::chrono::duration_cast<std::chrono::microseconds>(endTimePerStepsize - startTimePerStepsize).count();

			std::cout << "stepsize " << stepsize << ": " << timeDifference << std::endl;

			tempVector.push_back(static_cast<float>(timeDifference));

		}


		timingsVector.push_back(tempVector);


	}
	tempVector.clear();

	//Accumulates and calculates the average time per stepSize, and stuffs it into averagesVector
	float accumulator{ 0 };
	for (int stepSize = 1; stepSize < numberOfSteps; ++stepSize)
	{


		for (int sampleIdx{ 0 }; sampleIdx < timingsVector.size(); ++sampleIdx)
		{
			accumulator += timingsVector[sampleIdx][stepSize];



		}
		accumulator /= numberOfSteps;
		averageOfAllTimingsVector.push_back(accumulator);
	}
	return averageOfAllTimingsVector;

}
