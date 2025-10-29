#include "red.h"
#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;
void Red::agregarRouter(const string& nombre) {
    if (routers.find(nombre) == routers.end()) {
        routers[nombre] = Router(nombre);
        conexiones[nombre] = {};
        cout << "Router " << nombre << " agregado."<<endl;
        actualizarTablasEnrutamiento();
    } else {
        cout << "El router ya existe."<<endl;
    }
}

void Red::eliminarRouter(const string& nombre) {
    if (routers.erase(nombre)) {
        conexiones.erase(nombre);
        for (auto& par : conexiones) {
            par.second.erase(nombre);
        }
        cout << "Router " << nombre << " eliminado.";
        actualizarTablasEnrutamiento();
    } else {
        cout << "El router no existe.\n";
    }
}

void Red::conectarRouters(const string& r1, const string& r2, int costo) {
    if (routers.find(r1) == routers.end() || routers.find(r2) == routers.end()) {
        cout << "Uno o ambos routers no existen."<<endl;
        return;
    }
    conexiones[r1][r2] = costo;
    conexiones[r2][r1] = costo;
    std::cout << "Routers conectados exitosamente."<<endl;
    actualizarTablasEnrutamiento();
}

void Red::mostrarEstadoRed() const {
    cout << "\n--- Estado de la red ---"<<endl;
    for (const auto& [origen, vecinos] : conexiones) {
        cout << origen << " conectado a: ";
        if (vecinos.empty()) {
            cout << "(sin conexiones)";
        } else {
            for (const auto& [destino, costo] : vecinos) {
                cout << destino << "(" << costo << ") ";
            }
        }
        cout << endl;
    }
}
void Red::mostrarRutaMinima(const string& origen, const string& destino) const {
    if (routers.find(origen) == routers.end() || routers.find(destino) == routers.end()) {
        cout << "Uno o ambos routers no existen.";
        return;
    }

    map<string, int> dist;
    map<string, string> prev;
    set<string> visitados;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

    for (const auto& [nombre, _] : routers) {
        dist[nombre] = numeric_limits<int>::max();
    }

    dist[origen] = 0;
    pq.push({0, origen});

    while (!pq.empty()) {
        auto [costo, actual] = pq.top(); pq.pop();
        if (visitados.count(actual)) continue;
        visitados.insert(actual);

        for (const auto& [vecino, peso] : conexiones.at(actual)) {
            if (dist[actual] + peso < dist[vecino]) {
                dist[vecino] = dist[actual] + peso;
                prev[vecino] = actual;
                pq.push({dist[vecino], vecino});
            }
        }
    }

    if (dist[destino] == numeric_limits<int>::max()) {
        cout << "No hay ruta desde " << origen << " hasta " << destino ;
        return;
    }


    vector<string> ruta;
    string actual = destino;
    while (actual != origen) {
        ruta.push_back(actual);
        actual = prev[actual];
    }
    ruta.push_back(origen);
    reverse(ruta.begin(), ruta.end());

    cout << "Costo minimo desde " << origen << " hasta " << destino << ": " << dist[destino] << endl;
    cout << "Ruta: ";
    for (size_t i = 0; i < ruta.size(); ++i) {
        cout << ruta[i];
        if (i < ruta.size() - 1) cout << " -> ";
    }
    cout << endl;
}

void Red::mostrarTablasEnrutamiento() const {
    for (const auto& [nombre, router] : routers) {
        router.mostrarTabla();
    }
}

void Red::actualizarTablasEnrutamiento() {
    for (auto& [origen, router] : routers) {
        map<string, int> dist;
        map<string, string> prev;
        set<string> visitados;
        priority_queue<pair<int, string>,
                       vector<pair<int, string>>, greater<>> pq;

        for (const auto& [nombre, _] : routers) {
            dist[nombre] = numeric_limits<int>::max();
        }
        dist[origen] = 0;
        pq.push({0, origen});

        while (!pq.empty()) {
            auto [costo, actual] = pq.top(); pq.pop();
            if (visitados.count(actual)) continue;
            visitados.insert(actual);

            for (const auto& [vecino, peso] : conexiones[actual]) {
                if (dist[actual] + peso < dist[vecino]) {
                    dist[vecino] = dist[actual] + peso;
                    prev[vecino] = actual;
                    pq.push({dist[vecino], vecino});
                }
            }
        }

        router.tablaEnrutamiento.clear();
        for (const auto& [destino, costo] : dist) {
            if (costo == std::numeric_limits<int>::max()) continue;
            string siguiente = destino;
            while (prev.count(siguiente) && prev[siguiente] != origen) {
                siguiente = prev[siguiente];
            }
            if (destino != origen) {
                router.actualizarEntrada(destino, costo, siguiente);
            } else {
                router.actualizarEntrada(destino, 0, origen);
            }
        }
    }
}
