#include <Windows.h>

int Crash(HMODULE hModule, unsigned int method) {
	HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, false, GetCurrentProcessId());
	switch (method)
	{
	case 1:
		while (true) {}
		break;

	case 2:
		throw "gay";
		break;

	case 3:
		abort();
		break;

	case 4:
		TerminateProcess(proc, EXIT_FAILURE);
		break;

	case 5:
		CreateRemoteThread(proc, 0, 0, 0, 0, 0, 0);
		break;

	case 6:
		__asm int 3;
		break;

	case 7:
		*((unsigned int*)0) = 0xFF;
		break;

	case 8:
		free(Crash);
		break;

	case 9:
		LeaveCriticalSection(nullptr);
		break;

	case 10:
		CloseWindow(NULL);
		break;

	default:
		exit(EXIT_FAILURE);
		break;
	}
}

DWORD WINAPI entry(HMODULE hModule) {
	Crash(hModule, 10);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//Crash(hModule, 6);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)entry, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
