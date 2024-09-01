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

// Clase Hash
class Hash {
private:
    int N;//tamaño de la lista
    vector<list<Contacto*>> table;

    // Función hash personalizada basada en el nombre
    int hashFunction(const string& key) {
        unsigned long hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % N;
    }

public:
    Hash(int s) : N(s), table(s, list<Contacto*>()) {}

    // Insertar contacto
    void insertar(const string& nombre, Contacto* contacto) {
        int index = hashFunction(nombre);
        // Verificar si el contacto ya existe
        for (auto& c : table[index]) {
            if (c->nombre == nombre) {
                cout << "El contacto con el nombre \"" << nombre << "\" ya existe.\n";
                return;
            }
        }
        table[index].push_back(contacto);
        cout << "Contacto agregado exitosamente.\n";
    }

    // Mostrar todos los contactos
    void mostrarContactos() {
        for (int i = 0; i < N; ++i) {
            if (!table[i].empty()) {
                cout << "Indice " << i << ":\n";
                for (auto& contacto : table[i]) {
                    cout << "  Nombre: " << contacto->nombre << "\n"
                         << "  Apellidos: " << contacto->apellidos << "\n"
                         << "  Correo: " << contacto->correo << "\n"
                         << "  Celular: " << contacto->celular << "\n"
                         << "  Fecha de Nacimiento: " << contacto->fechaNacimiento << "\n\n";
                }
            }
        }
    }

    // Buscar contacto
    Contacto* buscarContacto(const string& nombre) {
        int index = hashFunction(nombre);
        for (auto& contacto : table[index]) {
            if (contacto->nombre == nombre) {
                return contacto;
            }
        }
        return nullptr;
    }

    // Editar contacto
    void editarContacto(const string& nombre) {
        Contacto* contacto = buscarContacto(nombre);
        if (contacto == nullptr) {
            cout << "Contacto no encontrado.\n";
            return;
        }
        cout << "Editar datos del contacto \"" << nombre << "\":\n";
        cout << "Nuevo Apellidos (actual: " << contacto->apellidos << "): ";
        getline(cin, contacto->apellidos);
        cout << "Nuevo Correo (actual: " << contacto->correo << "): ";
        getline(cin, contacto->correo);
        cout << "Nuevo Celular (actual: " << contacto->celular << "): ";
        getline(cin, contacto->celular);
        cout << "Nueva Fecha de Nacimiento (actual: " << contacto->fechaNacimiento << "): ";
        getline(cin, contacto->fechaNacimiento);
        cout << "Contacto actualizado exitosamente.\n";
    }

    // Borrar contacto
    void borrarContacto(const string& nombre) {
        int index = hashFunction(nombre);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it)->nombre == nombre) {
                delete *it;
                table[index].erase(it);
                cout << "Contacto borrado exitosamente.\n";
                return;
            }
        }
        cout << "Contacto no encontrado.\n";
    }

    // Destructor para liberar memoria
    ~Hash() {
        for (int i = 0; i < N; ++i) {
            for (auto& contacto : table[i]) {
                delete contacto;
            }
        }
    }
};

// Funciones auxiliares para interactuar con el usuario
void agregarContacto(Hash& hashTable) {
    string nombre, apellidos, correo, celular, fechaNacimiento;
    cout << "Ingrese Nombre: ";
    getline(cin, nombre);
    cout << "Ingrese Apellidos: ";
    getline(cin, apellidos);
    cout << "Ingrese Correo: ";
    getline(cin, correo);
    cout << "Ingrese Celular: ";
    getline(cin, celular);
    cout << "Ingrese Fecha de Nacimiento: ";
    getline(cin, fechaNacimiento);

    Contacto* nuevoContacto = new Contacto(nombre, apellidos, correo, celular, fechaNacimiento);
    hashTable.insertar(nombre, nuevoContacto);
}

void buscarContacto(Hash& hashTable) {
    string nombre;
    cout << "Ingrese el Nombre del contacto a buscar: ";
    getline(cin, nombre);
    Contacto* contacto = hashTable.buscarContacto(nombre);
    if (contacto) {
        cout << "Contacto encontrado:\n"
             << "  Nombre: " << contacto->nombre << "\n"
             << "  Apellidos: " << contacto->apellidos << "\n"
             << "  Correo: " << contacto->correo << "\n"
             << "  Celular: " << contacto->celular << "\n"
             << "  Fecha de Nacimiento: " << contacto->fechaNacimiento << "\n";
    } else {
        cout << "Contacto no encontrado.\n";
    }
}

void editarContacto(Hash& hashTable) {
    string nombre;
    cout << "Ingrese el Nombre del contacto a editar: ";
    getline(cin, nombre);
    hashTable.editarContacto(nombre);
}

void borrarContacto(Hash& hashTable) {
    string nombre;
    cout << "Ingrese el Nombre del contacto a borrar: ";
    getline(cin, nombre);
    hashTable.borrarContacto(nombre);
}

int main() {
    int tamaño;
    cout << "Ingrese el tamaño de la tabla de hash: ";
    cin >> tamaño;
    cin.ignore(); // Limpiar el buffer

    Hash hashTable(tamaño);

    int opcion;
    do {
        cout << "\n--- Gestor de Contactos ---\n";
        cout << "1. Agregar Contacto\n";
        cout << "2. Mostrar Contactos\n";
        cout << "3. Buscar Contacto\n";
        cout << "4. Editar Contacto\n";
        cout << "5. Borrar Contacto\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer

        switch (opcion) {
            case 1:
                agregarContacto(hashTable);
                break;
            case 2:
                hashTable.mostrarContactos();
                break;
            case 3:
                buscarContacto(hashTable);
                break;
            case 4:
                editarContacto(hashTable);
                break;
            case 5:
                borrarContacto(hashTable);
                break;
            case 6:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 6);

    return 0;
}
