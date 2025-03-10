#include "Controller.h"
#include <windows.h>
#include <Xinput.h>
#include <cmath>

class dae::Controller::Impl {
public:
    explicit Impl(int index) : controllerIndex(index) 
    {
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        ZeroMemory(&previousState, sizeof(XINPUT_STATE));
    }

    /*bool IsConnected() 
    {
        
        return (XInputGetState(controllerIndex, &state) == ERROR_SUCCESS);
    }*/

    void Update() 
    {
        previousState = state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        XInputGetState(controllerIndex, &state);
    }

    bool IsButtonReleased(WORD button) const 
    {
        return ((previousState.Gamepad.wButtons & button) != 0) &&
            ((state.Gamepad.wButtons & button) == 0);
    }

   /* float GetLeftTrigger() const 
    {
        return state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ?
            state.Gamepad.bLeftTrigger / 255.0f : 0.0f;
    }

    float GetRightTrigger() const 
    {
        return state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ?
            state.Gamepad.bRightTrigger / 255.0f : 0.0f;
    }

    float ApplyDeadzone(SHORT value, SHORT deadzone) const 
    {
        if (std::abs(value) < deadzone) {
            return 0.0f;
        }
        float sign = (value > 0) ? 1.0f : -1.0f;
        return sign * (std::abs(value) - deadzone) / (32767.0f - deadzone);
    }*/


    bool IsButtonDown(WORD button) const 
{
        return (state.Gamepad.wButtons & button) != 0;
    }
    bool IsButtonUp(WORD button) const
    {
        return (previousState.Gamepad.wButtons & button) != 0;
    }
    bool IsButtonPressed(WORD button) const
    {
        return (state.Gamepad.wButtons & button) != 0;
    }
    bool IsDPadUp() const {
        return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
    }

    bool IsDPadDown() const {
        return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0;
    }

    bool IsDPadLeft() const {
        return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
    }

    bool IsDPadRight() const {
        return (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;
    }

private:
    int controllerIndex;
    XINPUT_STATE state;
    XINPUT_STATE previousState;
};

dae::Controller::Controller(int index) : pImpl(std::make_unique<Impl>(index)){}
dae::Controller::~Controller() = default;

//bool dae::Controller::IsConnected() const { return pImpl->IsConnected(); }
void dae::Controller::Update() { pImpl->Update(); }
bool dae::Controller::IsButtonReleased(WORD button) const { return pImpl->IsButtonReleased(button); }
bool dae::Controller::IsButtonDown(WORD button) const { return pImpl->IsButtonPressed(button); }
bool dae::Controller::IsButtonUp(WORD button) const { return pImpl->IsButtonPressed(button); }
bool dae::Controller::IsButtonPressed(WORD button) const { return pImpl->IsButtonPressed(button); }

bool dae::Controller::IsDPadUp() const { return pImpl->IsDPadUp(); }
bool dae::Controller::IsDPadDown() const { return pImpl->IsDPadDown(); }
bool dae::Controller::IsDPadLeft() const { return pImpl->IsDPadLeft(); }
bool dae::Controller::IsDPadRight() const { return pImpl->IsDPadRight(); }
