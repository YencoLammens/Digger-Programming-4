#include "Controller.h"
#include <Xinput.h>
#include <Windows.h>
void dae::Controller::RetrieveState()
{

    DWORD dwResult;
    for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        // Simply get the state of the controller from XInput.
        dwResult = XInputGetState(i, &state);

        if (dwResult == ERROR_SUCCESS)
        {
            // Controller is connected
        }
        else
        {
            // Controller is not connected
        }
    }
}

void dae::Controller::HandleDeadZone()
{
    XINPUT_STATE state = m_ControllersArr[i].state;

    float LX = state.Gamepad.sThumbLX;
    float LY = state.Gamepad.sThumbLY;

    //determine how far the controller is pushed
    float magnitude = sqrt(LX * LX + LY * LY);

    //determine the direction the controller is pushed
    float normalizedLX = LX / magnitude;
    float normalizedLY = LY / magnitude;

    float normalizedMagnitude = 0;

    //check if the controller is outside a circular dead zone
    if (magnitude > INPUT_DEADZONE)
    {
        //clip the magnitude at its expected maximum value
        if (magnitude > 32767) magnitude = 32767;

        //adjust magnitude relative to the end of the dead zone
        magnitude -= INPUT_DEADZONE;

        //optionally normalize the magnitude with respect to its expected range
        //giving a magnitude value of 0.0 to 1.0
        normalizedMagnitude = magnitude / (32767 - INPUT_DEADZONE);
    }
    else //if the controller is in the deadzone zero out the magnitude
    {
        magnitude = 0.0;
        normalizedMagnitude = 0.0;
    }
}
