#pragma once
#include "Observer.h"
namespace dae
{
    class Achievements : public Observer
    {
    public:
        //virtual void OnNotify();
        
        void OnNotify(const GameEvent& event, GameObject* go) override;
		

    private:
        //void Unlock(Achievement achievement)
        //{
        //    // Unlock if not already unlocked...
        //}

    };
}

