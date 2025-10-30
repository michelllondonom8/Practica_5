#include "red.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <sstream>
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
void Red::mostrarRutaYCosto(const string& origen, const string& destino) const {
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

    cout << "\n--- Informacion de ruta ---" << endl;
    cout << "Costo total: " << dist[destino] << endl;
    cout << "Camino: ";
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
bool Red::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return false;
    }

    limpiarRed();

    string linea;
    int numRouters = 0;

    // Leer número de routers
    if (getline(archivo, linea)) {
        stringstream ss(linea);
        ss >> numRouters;
    }

    // Leer nombres de routers
    vector<string> nombresRouters;
    for (int i = 0; i < numRouters; i++) {
        if (getline(archivo, linea)) {
            nombresRouters.push_back(linea);
            routers[linea] = Router(linea);
            conexiones[linea] = {};
        }
    }

    // Leer conexiones
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string r1, r2;
        int costo;
        if (ss >> r1 >> r2 >> costo) {
            if (routers.find(r1) != routers.end() && routers.find(r2) != routers.end()) {
                conexiones[r1][r2] = costo;
                conexiones[r2][r1] = costo;
            }
        }
    }

    archivo.close();
    actualizarTablasEnrutamiento();
    cout << "Red cargada exitosamente desde " << nombreArchivo << endl;
    cout << "Routers cargados: " << routers.size() << endl;
    return true;
}
bool Red::guardarEnArchivo(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo crear el archivo " << nombreArchivo << endl;
        return false;
    }

    // Escribir número de routers
    archivo << routers.size() << endl;

    // Escribir nombres de routers
    for (const auto& [nombre, _] : routers) {
        archivo << nombre << endl;
    }

    // Escribir conexiones (evitar duplicados)
    set<pair<string, string>> escritas;
    for (const auto& [origen, vecinos] : conexiones) {
        for (const auto& [destino, costo] : vecinos) {
            string r1 = origen < destino ? origen : destino;
            string r2 = origen < destino ? destino : origen;
            if (escritas.find({r1, r2}) == escritas.end()) {
                archivo << origen << " " << destino << " " << costo << endl;
                escritas.insert({r1, r2});
            }
        }
    }

    archivo.close();
    cout << "Red guardada exitosamente en " << nombreArchivo << endl;
    return true;
}

void Red::generarTopologiaMalla(int numRouters) {
    limpiarRed();
    srand(time(nullptr));

    cout << "\nGenerando topologia de malla..." << endl;

    // Crear routers
    for (int i = 0; i < numRouters; i++) {
        string nombre = "R" + to_string(i);
        routers[nombre] = Router(nombre);
        conexiones[nombre] = {};
    }

    // Conectar todos con todos (malla completa)
    vector<string> nombres;
    for (const auto& [nombre, _] : routers) {
        nombres.push_back(nombre);
    }

    for (size_t i = 0; i < nombres.size(); i++) {
        for (size_t j = i + 1; j < nombres.size(); j++) {
            int costo = rand() % 10 + 1;
            conexiones[nombres[i]][nombres[j]] = costo;
            conexiones[nombres[j]][nombres[i]] = costo;
        }
    }

    actualizarTablasEnrutamiento();

    // Guardar automáticamente con timestamp
    string nombreArchivo = "topologia_malla_" + to_string(time(nullptr)) + ".txt";
    guardarEnArchivo(nombreArchivo);
    cout << "Topologia de malla generada con " << numRouters << " routers." << endl;
    cout << "Tipo: Todos los routers conectados entre si." << endl;
}

void Red::limpiarRed() {
    routers.clear();
    conexiones.clear();
}
