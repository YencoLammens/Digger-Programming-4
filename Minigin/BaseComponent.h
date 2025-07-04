#pragma once
namespace dae
{
	class GameObject;
	class BaseComponent
	{
		GameObject* m_pOwner;
	public:
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate(float fixedTimeStep) = 0;
		void LateUpdate() { /* Default implementation does nothing */ };

		void MarkForDeletion() { m_toBeDeleted = true; };
		bool IsMarkedForDeletion() { return m_toBeDeleted; }
	protected:
		explicit BaseComponent(GameObject* pOwner) : m_pOwner(pOwner) {}
		GameObject* GetOwner() const { return m_pOwner; }

	private:
		bool m_toBeDeleted = false;
	};





};