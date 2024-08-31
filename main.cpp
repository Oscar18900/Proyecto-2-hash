#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

// Clase Contacto
class Contacto {
public:
    string nombre;
    string apellidos;
    string correo;
    string celular;
    string fechaNacimiento;

    Contacto(string n, string a, string c, string ce, string f) :
        nombre(n), apellidos(a), correo(c), celular(ce), fechaNacimiento(f) {}
};
