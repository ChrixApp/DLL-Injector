#include <cstring>
using std::strcpy;

#include <iostream>
using std::cout;
using std::cin;

#include <string>
using std::string;

#include "Injector.h"

int main()
{
    string aux;

    // Pide la ruta de la DLL
    cout << "Path DLL: ";
    // Lee la ruta y la coloca en aux
    cin >> aux;

    // Convierte la variable aux a char*
    char *dll = new char[aux.length() + 1];
    strcpy(dll, aux.c_str());

    // Pide el título de la ventana
    cout << "Window Title: ";
    // Lee el título de la ventana y lo coloca en aux
    cin >> aux;

    // Convierte la variable aux a char*
    char *windowTitle = new char[aux.length() + 1];
    strcpy(windowTitle, aux.c_str());

    // Instancia un objeto de la clase Injetor
    Injector injector;
    // Llama al método inject
    injector.inject(dll, windowTitle);

    delete [] dll;
    delete [] windowTitle;

    return 0;
}
