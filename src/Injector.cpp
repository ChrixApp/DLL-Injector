#include <windows.h>

#include "Injector.h"

// Función que lleva acabo la inyección
void Injector::inject(char *dll, char *windowTitle)
{
    HWND window;
    DWORD pid;
    HANDLE process;
    LPVOID memory;
    SIZE_T write = 0;

    // Buscamos la ventana del proceso a inyectar
    window = FindWindowEx(0, 0, 0, windowTitle);

    // Buscamos el proceso a inyectar
    GetWindowThreadProcessId(window, &pid);

    // Abrimos el proceso
    process = OpenProcess(PROCESS_ALL_ACCESS, false, pid);

    // Reservamos memoria en el proceso para la DLL
    memory = VirtualAllocEx(process, 0, strlen(dll),
        MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    // Escribimos en el proceso
    WriteProcessMemory(process, memory, (LPVOID)dll, strlen(dll), &write);

    // Obtenemos el modulo de la DLL Kernel32
    HMODULE hModule = LoadLibrary("Kernel32.dll");
    // Obtenemos la dirección en memoria en la que se encuentra la
    // función LoadLibrary
    FARPROC tsr = GetProcAddress(hModule, "LoadLibraryA");

    // Creamos un hilo en el proceso
    CreateRemoteThread(process, 0, 0, (LPTHREAD_START_ROUTINE)tsr, memory, 0, 0);
}
