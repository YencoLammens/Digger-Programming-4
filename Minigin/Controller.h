#pragma once
#include <Xinput.h>
namespace dae
{
    class Controller
    {


    public:
        void RetrieveState();
        void HandleDeadZone();

    private:
        DWORD m_dwResult;
       

    };
}



