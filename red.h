#ifndef RED_H
#define RED_H

#include "Router.h"
#include <map>
#include <queue>
#include <set>
#include <iostream>
using namespace std;

class Red {
private:
    map<string, Router> routers;
    map<string, map<string, int>> conexiones;

public:
    void mostrarRutaMinima(const string& origen, const string& destino) const;
    void agregarRouter(const string& nombre);
    void eliminarRouter(const string& nombre);
    void conectarRouters(const string& r1, const string& r2, int costo);
    void mostrarEstadoRed() const;
    void mostrarTablasEnrutamiento() const;
    void actualizarTablasEnrutamiento();
};

#endif // RED_H
