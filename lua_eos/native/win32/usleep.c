#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <limits.h>
#include <winnt.h>
//#include "usleep.h"

static unsigned long currentResolution = 0;

static unsigned long setHighestTimerResolution(unsigned long timer_res_us)
{
	unsigned long timer_current_res = ULONG_MAX;
	const HINSTANCE ntdll = LoadLibrary("NTDLL.dll");
	if (ntdll != NULL)
	{
		typedef long(NTAPI* pNtSetTimerResolution)(unsigned long RequestedResolution, BOOLEAN Set, unsigned long* ActualResolution);

		pNtSetTimerResolution NtSetTimerResolution = (pNtSetTimerResolution) GetProcAddress(ntdll, "NtSetTimerResolution");
		if (NtSetTimerResolution != NULL)
		{
			// bounds are validated and set to the highest allowed resolution
			NtSetTimerResolution(timer_res_us, TRUE, &timer_current_res);
		}
		// we can decrement the internal reference count by one
		// and NTDLL.DLL still remains loaded in the process
		FreeLibrary(ntdll);
	}

	return timer_current_res;
}

void usleep(__int64 usec)
{
	HANDLE timer;
	LARGE_INTEGER period;

	if (currentResolution == 0)
		currentResolution = setHighestTimerResolution(1);

	// negative values are for relative time
	period.QuadPart = -(10*usec);

	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &period, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}
