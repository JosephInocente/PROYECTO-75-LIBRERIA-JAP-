#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib> // Para system("cls") en Windows o system("clear") en UNIX

using namespace std;

struct Libro {
    string Codigo_libro;
    string Titulo_libro;
    string Autor_libro;
    string Categoria_libro;
    int Cantidad_Mismo_libro;
    float Precio_libro;
};

// Prototipos de funciones
void imprimirLibro(const Libro& libro);
void agregarLibroAlmacen(vector<Libro>& libros);
void Imprimir_Listado_Libros(const vector<Libro>& libros);
void Modificar_Libro(vector<Libro>& libros, const string& codigo);
void eliminar_Libro_Por_Codigo_Autor_o_Categoria(vector<Libro>& libros, const string& valor, int condicion);
void Guardar_Galeria_TXT(const vector<Libro>& libros);
void Cargar_Galeria_TXT(vector<Libro>& libros);
int Menu();
int MenuEliminar_Segun();

int main() {
    vector<Libro> libros;
    Cargar_Galeria_TXT(libros);
    int opcion = 0;
    while (true) {
        system("cls"); // Limpia la pantalla en Windows, cambiar a "clear" en UNIX
        opcion = Menu();
        switch(opcion) {
            case 1:
                agregarLibroAlmacen(libros);
                break;
            case 2:
                Imprimir_Listado_Libros(libros);
                break;
            case 3: {
            	Imprimir_Listado_Libros(libros);
                string codigo;
                cout << "Ingrese el codigo del libro a modificar: ";
                cin >> codigo;
                Modificar_Libro(libros, codigo);
                break;
            }
            case 4: {
            	Imprimir_Listado_Libros(libros);
                int condicion = MenuEliminar_Segun();
                string valor;
                cout << "Ingrese el valor para eliminar: ";
                cin >> valor;
                eliminar_Libro_Por_Codigo_Autor_o_Categoria(libros, valor, condicion);
                break;
            }
            case 5:
                Guardar_Galeria_TXT(libros);
                cout << "Libreria guardada exitosamente." << endl;
                system("pause");
                return 0;
            default:
                cout << "Opcion no valida." << endl;
                break;
        }
        system("pause"); // Pausa después de cada operación
    }
}

void imprimirLibro(const Libro& libro) {
    cout << "Codigo: " << libro.Codigo_libro << "\n"
         << "Titulo: " << libro.Titulo_libro << "\n"
         << "Autor: " << libro.Autor_libro << "\n"
         << "Categoría: " << libro.Categoria_libro << "\n"
         << "Cantidad: " << libro.Cantidad_Mismo_libro << "\n"
         << "Precio: $" << libro.Precio_libro << endl;
}

void agregarLibroAlmacen(vector<Libro>& libros) {
    system("cls");
    Libro nuevoLibro;
    cout << "Agregar nuevo libro" << endl;
    cout << "Ingrese el codigo del libro: ";
    cin >> nuevoLibro.Codigo_libro;
    cin.ignore();
    cout << "Ingrese el titulo del libro: ";
    getline(cin, nuevoLibro.Titulo_libro);
    cout << "Ingrese el autor del libro: ";
    getline(cin, nuevoLibro.Autor_libro);
    cout << "Ingrese la categoria del libro: ";
    getline(cin, nuevoLibro.Categoria_libro);
    cout << "Ingrese la cantidad de libros: ";
    cin >> nuevoLibro.Cantidad_Mismo_libro;
    cout << "Ingrese el precio del libro: ";
    cin >> nuevoLibro.Precio_libro;
    libros.push_back(nuevoLibro);
    cout << "Libro agregado exitosamente." << endl;
}

void Imprimir_Listado_Libros(const vector<Libro>& libros) {
    system("cls");
    cout << "Listado de Libros:" << endl;
    for (const auto& libro : libros) {
        imprimirLibro(libro);
        cout << "----------------------------" << endl;
    }
}

void Modificar_Libro(vector<Libro>& libros, const string& codigo) {
    system("cls");
    for (auto& libro : libros) {
        if (libro.Codigo_libro == codigo) {
            cout << "Modificar libro con codigo: " << codigo << endl;
            cout << "Ingrese el nuevo titulo del libro: ";
            cin.ignore();
            getline(cin, libro.Titulo_libro);
            cout << "Ingrese el nuevo autor del libro: ";
            getline(cin, libro.Autor_libro);
            cout << "Ingrese la nueva categoria del libro: ";
            getline(cin, libro.Categoria_libro);
            cout << "Ingrese la nueva cantidad de libros: ";
            cin >> libro.Cantidad_Mismo_libro;
            cout << "Ingrese el nuevo precio del libro: ";
            cin >> libro.Precio_libro;
            cout << "Libro modificado exitosamente." << endl;
            return;
        }
    }
    cout << "Libro no encontrado." << endl;
}

void eliminar_Libro_Por_Codigo_Autor_o_Categoria(vector<Libro>& libros, const string& valor, int condicion) {
    system("cls");
    bool eliminado = false;
    auto it = libros.begin();
    while (it != libros.end()) {
        bool match = false;
        switch(condicion) {
            case 1: match = it->Codigo_libro == valor; break;
            case 2: match = it->Autor_libro == valor; break;
            case 3: match = it->Categoria_libro == valor; break;
        }
        if (match) {
            it = libros.erase(it);
            eliminado = true;
        } else {
            ++it;
        }
    }
    if (eliminado) {
        cout << "Libro(s) eliminado(s) exitosamente." << endl;
    } else {
        cout << "No se encontraron libros para eliminar." << endl;
    }
}

void Guardar_Galeria_TXT(const vector<Libro>& libros) {
    ofstream archivo("Libreria.txt");
    for (const auto& libro : libros) {
        archivo << libro.Codigo_libro << ","
                << libro.Titulo_libro << ","
                << libro.Autor_libro << ","
                << libro.Categoria_libro << ","
                << libro.Cantidad_Mismo_libro << ","
                << libro.Precio_libro << "\n";
    }
    archivo.close();
}

void Cargar_Galeria_TXT(vector<Libro>& libros) {
    ifstream archivo("Libreria.txt");
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Libro libro;
        getline(ss, libro.Codigo_libro, ',');
        getline(ss, libro.Titulo_libro, ',');
        getline(ss, libro.Autor_libro, ',');
        getline(ss, libro.Categoria_libro, ',');
        string cantidad, precio;
        getline(ss, cantidad, ',');
        getline(ss, precio);
        libro.Cantidad_Mismo_libro = stoi(cantidad);
        libro.Precio_libro = stof(precio);
        libros.push_back(libro);
    }
    archivo.close();
}

int Menu() {
    int opcion;
    cout << "Menu Principal:" << endl;
    cout << "1. Agregar libro" << endl;
    cout << "2. Listar libros" << endl;
    cout << "3. Modificar libro" << endl;
    cout << "4. Eliminar libro" << endl;
    cout << "5. Salir y guardar" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    return opcion;
}

int MenuEliminar_Segun() {
    system("cls");
    int opcion;
    cout << "Menu Eliminar Segun:" << endl;
    cout << "1. Por codigo" << endl;
    cout << "2. Por autor" << endl;
    cout << "3. Por categoria" << endl;
    cout << "Seleccione una opcion para eliminar: ";
    cin >> opcion;
    return opcion;
}
