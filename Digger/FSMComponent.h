#pragma once
#include "BaseComponent.h"
#include <memory>

namespace dae
{
    template<typename StateId, typename State>
	class FSMComponent : public BaseComponent
	{
    public:
        dae::FSMComponent::FSMComponent(GameObject* owner)
            : BaseComponent(owner), currentState(nullptr)
        {

        }

        void dae::FSMComponent::Update(float deltaTime) override
        {

            if (m_currentState) m_currentState->Update(GetOwner(), deltaTime);

        }

        void HandleInput()
        {
            if (m_currentState) m_currentState->HandleInput(GetOwner());
        }

        void HandleEvent()
        {
            if (m_currentState) m_currentState->HandleEvent(GetOwner());
        }

        void ChangeState(EnemyState newState)
        {

            if (m_currentState) m_currentState->exit(*m_owner);
            m_currentState = m_statesMap[newStateId].get();
            m_currentStateId = newStateId;
            if (m_currentState) m_currentState->enter(*m_owner);

        }

        void AddState(EnemyState id, std::unique_ptr<State> state)
        {
            m_statesMap[id] = std::move(state);
        }
    private:
        std::unordered_map<StateId, std::unique_ptr<State>> m_statesMap;
        State* m_currentState = nullptr;
        StateId m_currentStateId;
        State* m_currentStateId;
	};
}
