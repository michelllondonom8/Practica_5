#ifndef RED_H
#define RED_H

#include "Router.h"
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Red {
private:
    map<string, Router> routers;
    map<string, map<string, int>> conexiones;

public:
    void mostrarRutaYCosto(const string& origen, const string& destino) const;
    void agregarRouter(const string& nombre);
    void conectarRouters(const string& r1, const string& r2, int costo);
    void mostrarEstadoRed() const;
    void mostrarTablasEnrutamiento() const;
    void actualizarTablasEnrutamiento();

    bool cargarDesdeArchivo(const string& nombreArchivo);
    bool guardarEnArchivo(const string& nombreArchivo) const;
    void generarTopologiaMalla(int numRouters);
    void limpiarRed();
};

#endif // RED_H
