// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "game/cSlowRateManager.h"
#include "game/GameMenuStatus.h"

DWORD WINAPI thing(LPVOID) noexcept
{
    DWORD base = (DWORD)GetModuleHandleA(NULL);
    while (true)
    {
        static bool TimeStopEnabled = false;
        GameMenuStatus GameState = *(GameMenuStatus*)(base + 0x17E9F9C);
        bool IsForegroundWindow = *(bool*)(base + 0x19D509C);
        if ((GetAsyncKeyState(84) & 1) && GameState == InGame && IsForegroundWindow)
        {
            cSlowRateManager* cSlowRate = GetcSlowRateManager();
            TimeStopEnabled = cSlowRate->GetSlowRate(GAMEWORLDSPEED) == 1.0f;

            if (!TimeStopEnabled)
            {
                cSlowRate->SetSlowRate(GAMEWORLDSPEED, 1.0f);
                cSlowRate->SetSlowRate(PLSPEED, 1.0f);
                cSlowRate->SetSlowRate(WORLDSLOWTIME, 1.0f);
            }
        }
        if (TimeStopEnabled && GameState == InGame && IsForegroundWindow)
        {
            cSlowRateManager_SetSlowRate(GAMEWORLDSPEED, 0.0001f);
            cSlowRateManager_SetSlowRate(PLSPEED, 9999.958008f);
            cSlowRateManager_SetSlowRate(WORLDSLOWTIME, 0.0001f);
        }
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    DisableThreadLibraryCalls(hModule);
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&thing, NULL, 0, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

