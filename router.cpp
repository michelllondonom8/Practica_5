#include "router.h"

Router::Router(const string& nombre_) : nombre(nombre_) {}

void Router::actualizarEntrada(const string& destino, int costo, const string& siguienteSalto) {
    tablaEnrutamiento[destino] = {costo, siguienteSalto};
}

void Router::mostrarTabla() const {
    cout << "Tabla de enrutamiento de " << nombre << ":" << endl;
    cout << "Destino\tCosto\tSiguiente Salto" << endl;
    for (const auto& entrada : tablaEnrutamiento) {
        cout << entrada.first << "\t" << entrada.second.first << "\t" << entrada.second.second << endl;
    }
}
