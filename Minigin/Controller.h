#pragma once
#define WIN32_LEAN_AND_MEAN
#include <memory>
#include <Windows.h>
#include <Xinput.h>


#pragma comment(lib, "xinput.lib")

namespace dae
{
    class Controller
    {
    public:
        explicit Controller(int index);
        ~Controller();

        //bool IsConnected() const;
        void Update();
        bool IsButtonReleased(WORD button) const;
        bool IsButtonDown(WORD button) const;
        bool IsButtonUp(WORD button) const;
        bool IsButtonPressed(WORD button) const;
        bool IsDPadUp() const;
        bool IsDPadDown() const;
        bool IsDPadLeft() const;
        bool IsDPadRight() const;
       

    private:
        class Impl;
        std::unique_ptr<Impl> pImpl;

    };

}



//#ifndef CONTROLLER_H
//#define CONTROLLER_H
//
//#include <memory>
//#include <Xinput.h>
//
//namespace dae
//{
//    class Controller {
//    public:
//        explicit Controller(int index);
//        ~Controller();
//
//        bool IsConnected() const;
//        void Update();
//        float GetLeftTrigger() const;
//        float GetRightTrigger() const;
//        float GetLeftThumbX() const;
//        float GetLeftThumbY() const;
//        float GetRightThumbX() const;
//        float GetRightThumbY() const;
//        bool IsButtonPressed(WORD button) const;
//
//
//    private:
//
//    };
//}
//
//
//#endif // CONTROLLER_H
//
//
//
