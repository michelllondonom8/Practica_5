#ifndef ROUTER_H
#define ROUTER_H

#include <iostream>
#include <map>
#include <string>
using namespace std;

class Router {
public:
    string nombre;
    map<string, pair<int, string>> tablaEnrutamiento;

    Router() = default;
    Router(const string& nombre_);

    void actualizarEntrada(const string& destino, int costo, const string& siguienteSalto);
    void mostrarTabla() const;
};

#endif // ROUTER_H
