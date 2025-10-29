#include "Red.h"
#include <iostream>
using namespace std;

int main() {
    Red red;
    int opcion;

    cout << "Bienvenido a la simulacion de red de routers." << endl;
    do {
        cout << "--- MENU DE RED ---" << endl;
        cout << "1. Agregar router" << endl;
        cout << "2. Eliminar router" << endl;
        cout << "3. Mostrar estado actual de la red" << endl;
        cout << "4. Mostrar tablas de enrutamiento" << endl;
        cout << "5. Conectar routers" << endl;
        cout << "6. Cuanto cuesta enviar un paquete" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nombre;
            cout << "Nombre del nuevo router: ";
            cin >> nombre;
            red.agregarRouter(nombre);
            break;
        }
        case 2: {
            string nombre;
            cout << "Nombre del router a eliminar: ";
            cin >> nombre;
            red.eliminarRouter(nombre);
            break;
        }
        case 3:
            red.mostrarEstadoRed();
            break;
        case 4:
            red.mostrarTablasEnrutamiento();
            break;
        case 5: {
            string r1, r2;
            int costo;
            cout << "Nombre del primer router: ";
            cin >> r1;
            cout << "Nombre del segundo router: ";
            cin >> r2;
            cout << "Costo del enlace: ";
            cin >> costo;
            red.conectarRouters(r1, r2, costo);
            break;
        }
        case 6: {
            string origen, destino;
            cout << "Router origen: ";
            cin >> origen;
            cout << "Router destino: ";
            cin >> destino;
            red.mostrarRutaMinima(origen, destino);
            break;
        }
        case 0:
            cout << "Gracias por usar la simulacion de red." << endl;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 0);

    return 0;
}
