#include "Red.h"
#include <iostream>
using namespace std;

int main() {
    Red red;
    int opcion;

    cout << "Bienvenido a la simulacion de red de routers." << endl;
    do {
        cout << "--- MENU DE RED ---" << endl;
        cout << "1. Cargar red desde archivo" << endl;
        cout << "2. Guardar red en archivo" << endl;
        cout << "3. Generar topologia de malla aleatoria" << endl;
        cout << "4. Agregar router manualmente" << endl;
        cout << "5. Conectar routers manualmente" << endl;
        cout << "6. Mostrar estado de la red" << endl;
        cout << "7. Mostrar tablas de enrutamiento" << endl;
        cout << "8. Consultar ruta y costo entre routers" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nombreArchivo;
            cout << "\nNombre del archivo a cargar: ";
            cin >> nombreArchivo;
            red.cargarDesdeArchivo(nombreArchivo);
            break;
        }
        case 2: {
            string nombreArchivo;
            cout << "\nNombre del archivo para guardar: ";
            cin >> nombreArchivo;
            red.guardarEnArchivo(nombreArchivo);
            break;
        }
        case 3: {
            int numRouters;
            cout << "\nNumero de routers para la malla: ";
            cin >> numRouters;
            if (numRouters > 0) {
                red.generarTopologiaMalla(numRouters);
            } else {
                cout << "Numero invalido de routers." << endl;
            }
            break;
        }
        case 4: {
            string nombre;
            cout << "\nNombre del nuevo router: ";
            cin >> nombre;
            red.agregarRouter(nombre);
            break;
        }
        case 5: {
            string r1, r2;
            int costo;
            cout << "\nPrimer router: ";
            cin >> r1;
            cout << "Segundo router: ";
            cin >> r2;
            cout << "Costo del enlace: ";
            cin >> costo;
            red.conectarRouters(r1, r2, costo);
            break;
        }
        case 6:
            red.mostrarEstadoRed();
            break;
        case 7:
            red.mostrarTablasEnrutamiento();
            break;
        case 8: {
            string origen, destino;
            cout << "\nRouter origen: ";
            cin >> origen;
            cout << "Router destino: ";
            cin >> destino;
            red.mostrarRutaYCosto(origen, destino);
            break;
        }
        case 0:
            cout << "Gracias por usar el simulador." << endl;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 0);

    return 0;
}
