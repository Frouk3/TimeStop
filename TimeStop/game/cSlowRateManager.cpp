#include <Windows.h>
#include "cSlowRateManager.h"

static DWORD base = (DWORD)GetModuleHandleA(NULL);
cSlowRateManager &g_pcSlowRateManager = *(cSlowRateManager*)(base + 0x19D9160);
cSlowRateManager* m_cSlowRateManager = &g_pcSlowRateManager;

void cSlowRateManager::SetSlowRate(SlowRateType SlowType, float SlowTime) noexcept
{
	DWORD address = base + 0xA03A70;
	((void (__thiscall *)(cSlowRateManager*, SlowRateType, float))address)(this, SlowType, SlowTime);
}

cSlowRateManager* GetcSlowRateManager() noexcept
{
	DWORD address = base + 0xA03960;
	return ((cSlowRateManager* (__stdcall *)())address)();
}

void cSlowRateManager_SetSlowRate(SlowRateType SlowType, float SlowTime) noexcept
{
	DWORD address = base + 0x532020;
	((void(__cdecl*)(SlowRateType, float))address)(SlowType, SlowTime);
}

void cSlowRateManager_Reset() noexcept
{
	DWORD address = base + 0x11EDC20;
	((void(__cdecl*)())address)();
}

float cSlowRateManager::GetSlowRate(SlowRateType SlowType) noexcept
{
	return this->m_fSlowRate[0].m_fRate;
}