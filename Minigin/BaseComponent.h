#pragma once
namespace dae
{
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) = delete;

		BaseComponent& operator=(const BaseComponent&) = delete;
		BaseComponent& operator=(const BaseComponent&&) = delete;

		virtual ~BaseComponent() = default;


		//Methods
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;


		bool m_ToBeDeleted = false;

	protected:

		

	private:
	};




};