#pragma once
namespace dae
{
	class BaseComponent
	{
	public:

		enum class Type
		{
			Render,
			Text,
			FPS,
			// Add other component types as needed
		};

		BaseComponent() = default;

		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) = delete;

		BaseComponent& operator=(const BaseComponent&) = delete;
		BaseComponent& operator=(const BaseComponent&&) = delete;

		virtual ~BaseComponent() = default;


		//Methods
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual Type GetType() const = 0;
		

	protected:

		bool m_ToBeDeleted = false;

	private:
	};




};