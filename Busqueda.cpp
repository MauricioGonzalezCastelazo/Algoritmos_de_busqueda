#include "Busqueda.h"
#include "Agenda.h"
#include "Arbol.h"
#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include <stddef.h>
//Buscar algoritmo libreria

using namespace std;

#pragma warning(disable : 6011)
Arbol::Arbol(){
    
}

Arbol::~Arbol() {
    

}

void Arbol::crea_arbol(tipo_nodo_informacion contenido)
{
    tipo_nodo_del_arbol temporal;
    temporal.padre = -1;
    temporal.profundidad = 0;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol_de_busqueda.push_back(temporal);
}

void Arbol::agrega_hijo_a_un_nodo(int padre, tipo_nodo_informacion contenido)
{
    tipo_nodo_del_arbol temporal;
    temporal.padre = padre;
    temporal.profundidad = arbol_de_busqueda[padre].profundidad + 1;
    temporal.contenido = contenido;
    temporal.hijos.clear();
    arbol_de_busqueda.push_back(temporal);
    arbol_de_busqueda[padre].hijos.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
}

bool Arbol::esta_un_nodo_en_ancestros(const int nodo_origen, string nombre_del_nodo) const
{
    int temporal = arbol_de_busqueda[nodo_origen].padre;
    while (temporal != -1)
    {
        if (arbol_de_busqueda[temporal].contenido.nombre_del_nodo == nombre_del_nodo)
            return true;
        temporal = arbol_de_busqueda[temporal].padre;
    }
    return false;
}

bool Arbol::buscar_en_el_arbol(int posicion, tipo_nodo_del_arbol& nodo_encontrado)const
{
    if (!arbol_de_busqueda.empty()) {
        nodo_encontrado = arbol_de_busqueda.at(posicion);
        return true;
    }
    return false; 
}

unsigned int Arbol::tamaño_del_arbol()const {
    return arbol_de_busqueda.size();
}

Agenda::Agenda() {
    agenda.clear();
}

Agenda::~Agenda() {
   
}

bool Agenda::existe_un_nodo_comun_en_las_agendas(
    int& nodo_comun_inicio, int& nodo_comun_final, Arbol arbol_desde_inicio, Arbol arbol_desde_final) const {
    tipo_nodo_del_arbol temporal_inicio;
    tipo_nodo_del_arbol temporal_final;
    unsigned int tamaño_del_arbol = arbol_desde_inicio.tamaño_del_arbol(); 
    unsigned int tamaño_del_arbol_final = arbol_desde_final.tamaño_del_arbol(); 
    
    
    for (unsigned int i = 0; i < tamaño_del_arbol; i++)
    {
        arbol_desde_inicio.buscar_en_el_arbol(i, temporal_inicio);
        for (unsigned int j = 0; j < tamaño_del_arbol_final; j++)
        {
            arbol_desde_final.buscar_en_el_arbol(j, temporal_final);
            if (temporal_inicio.contenido.nombre_del_nodo == temporal_final.contenido.nombre_del_nodo)
            {
                nodo_comun_inicio = i; 
                nodo_comun_final = j; 
                return true; 
            }
        }
    }
    
    return false; 

}

bool Agenda::agenda_esta_vacia()const {
    if (agenda.empty())
    {
        return true; 
    }
    else {
        return false; 
    }
}

void Agenda::posicion(int localidad, int& valor_devuelto)const {
    if (!agenda.empty() && localidad >= 0)
    {
        if (agenda.at(localidad) != NULL) {
            valor_devuelto = agenda.at(localidad);
        }
    }
}

bool Agenda::elimiar_elemento(int posicion)
{
    if (!agenda.empty())
    {
        agenda.erase(agenda.begin() + posicion);
        return true; 
    }
    return false; 
}

void Agenda::insertar_elemento(unsigned int posicion, int informacion)
{
    if (agenda.empty())
    {
        agenda.push_back(informacion);
    }
    else if (agenda.size() >= posicion)
    {
        agenda.push_back(informacion);
    }
    else if (agenda.size() > posicion)
    {
        agenda.insert(agenda.begin() + posicion, informacion);
    }
}

unsigned int Agenda::tamaño_agenda()const {
    return agenda.size();
}

Busqueda::Busqueda()
{
   
    
}

Busqueda::~Busqueda()
{

}

Grafo::Grafo() {
    grafo.clear();
}

Grafo::~Grafo(){

}

bool Grafo::lee_grafo(string archivo)
{
    string leida;
    tipo_enlace_de_grafo enlace;
    fstream newfile;
    vector<string> vector_de_cadenas;
    grafo.clear();
    newfile.open(archivo, ios::in);
    if (newfile.is_open())
    {
        getline(newfile, leida);
        while (getline(newfile, leida))
        {
            vector_de_cadenas.clear();
            stringstream cadena(leida);
            string temporal;
            while (getline(cadena, temporal, ','))
                vector_de_cadenas.push_back(temporal);
            enlace.nodo_1 = vector_de_cadenas[0];
            enlace.costo_nodo_1 = (float)atof(vector_de_cadenas[1].c_str());
            enlace.posicion_x_nodo_1 = (float)atof(vector_de_cadenas[2].c_str());
            enlace.posicion_y_nodo_1 = (float)atof(vector_de_cadenas[3].c_str());
            enlace.nodo_2 = vector_de_cadenas[4];
            enlace.costo_nodo_2 = (float)atof(vector_de_cadenas[5].c_str());
            enlace.posicion_x_nodo_2 = (float)atof(vector_de_cadenas[6].c_str());
            enlace.posicion_y_nodo_2 = (float)atof(vector_de_cadenas[7].c_str());
            enlace.costo_del_enlace = (float)atof(vector_de_cadenas[8].c_str());
            grafo.push_back(enlace);
        }
        newfile.close();
        return true;
    }
    else
        return false;
}

void Grafo::devuelve_vecinos_grafo_no_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const
{
    vecinos.clear();
    tipo_enlace_de_grafo temporal;
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo_1 == nodo)
            vecinos.push_back(grafo[i]);
        else if (grafo[i].nodo_2 == nodo)
        {
            temporal.nodo_1 = grafo[i].nodo_2;
            temporal.costo_nodo_1 = grafo[i].costo_nodo_2;
            temporal.posicion_x_nodo_1 = grafo[i].posicion_x_nodo_2;
            temporal.posicion_y_nodo_1 = grafo[i].posicion_y_nodo_2;
            temporal.nodo_2 = grafo[i].nodo_1;
            temporal.costo_nodo_2 = grafo[i].costo_nodo_1;
            temporal.posicion_x_nodo_2 = grafo[i].posicion_x_nodo_1;
            temporal.posicion_y_nodo_2 = grafo[i].posicion_y_nodo_1;
            temporal.costo_del_enlace = grafo[i].costo_del_enlace;
            vecinos.push_back(temporal);
        }

}

bool Grafo::devuelve_informacion_de_un_vertice_grafo_no_dirigido(string nodo, Arbol arbol_de_busqueda,
    int nodo_padre, tipo_nodo_informacion& informacion) const
{
    float costo_acumulado_del_padre = 0.0f;
    string nombre_del_nodo_padre = "";
    if (nodo_padre != -1)
    {
        tipo_nodo_del_arbol temporal;
        if (arbol_de_busqueda.buscar_en_el_arbol(nodo_padre, temporal)) {
            costo_acumulado_del_padre = temporal.contenido.costo_acumulado;
            nombre_del_nodo_padre = temporal.contenido.nombre_del_nodo;
            for (unsigned int i = 0; i < grafo.size(); i++)
                if (grafo[i].nodo_1 == nodo &&
                    grafo[i].nodo_2 == nombre_del_nodo_padre)
                {
                    informacion.nombre_del_nodo = grafo[i].nodo_1;
                    informacion.costo_acumulado = grafo[i].costo_nodo_1 +
                        costo_acumulado_del_padre +
                        grafo[i].costo_del_enlace;
                    return true;
                }
            for (unsigned int i = 0; i < grafo.size(); i++)
                if (grafo[i].nodo_2 == nodo &&
                    grafo[i].nodo_1 == nombre_del_nodo_padre)
                {
                    informacion.nombre_del_nodo = grafo[i].nodo_2;
                    informacion.costo_acumulado = grafo[i].costo_nodo_2 +
                        costo_acumulado_del_padre +
                        grafo[i].costo_del_enlace;
                    return true;
                }
        }
        return false;
    }
    else
    {
        for (unsigned int i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_1 == nodo)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_1;
                informacion.costo_acumulado = grafo[i].costo_nodo_1;
                return true;
            }
        for (unsigned int i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_2 == nodo)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_2;
                informacion.costo_acumulado = grafo[i].costo_nodo_2;
                return true;
            }
        return false;
    }
}

bool Busqueda::busqueda_primero_en_profundidad(string nodo_inicio, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda)
{
    Grafo grafo;
    grafo.lee_grafo("Ciudades_de_Mexico.csv");
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    unsigned int tamaño_agenda = 0;
    unsigned int tamaño_arbol = 0;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda, -1, informacion_del_nodo_inicio))
        return false;
    arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);
    Agenda agenda;
    agenda.insertar_elemento(0, 0);
    while (!agenda.agenda_esta_vacia())
    {
        agenda.posicion(0, nodo_actual);
        tipo_nodo_del_arbol nodo_a_buscar;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, nodo_a_buscar);
        if (nodo_a_buscar.contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        agenda.elimiar_elemento(0);
        tipo_nodo_del_arbol temporal;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal);
        grafo.devuelve_vecinos_grafo_no_dirigido(temporal.contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                arbol_de_busqueda, nodo_actual,
                informacion_del_hijo_a_adicionar);
            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                informacion_del_hijo_a_adicionar);
            tamaño_agenda = agenda.tamaño_agenda();
            tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
            agenda.insertar_elemento(0, tamaño_arbol - 1);
        }
    }
    return false;
}

bool Busqueda::busqueda_a_lo_ancho(string nodo_inicio, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda)
{
    Grafo grafo; 
    grafo.lee_grafo("Ciudades_de_Mexico.csv");
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    unsigned int tamaño_agenda = 0; 
    unsigned int tamaño_arbol = 0; 
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda, -1, informacion_del_nodo_inicio))
        return false;
    arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);
    Agenda agenda;
    agenda.insertar_elemento(0,0);
    while (!agenda.agenda_esta_vacia())
    {
        agenda.posicion(0, nodo_actual);
        tipo_nodo_del_arbol nodo_a_buscar;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, nodo_a_buscar);
        if (nodo_a_buscar.contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        agenda.elimiar_elemento(0);
        tipo_nodo_del_arbol temporal;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal);
        grafo.devuelve_vecinos_grafo_no_dirigido(temporal.contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                arbol_de_busqueda, nodo_actual,
                informacion_del_hijo_a_adicionar);
            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                informacion_del_hijo_a_adicionar);
            tamaño_agenda = agenda.tamaño_agenda();
            tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
            agenda.insertar_elemento(tamaño_agenda, tamaño_arbol-1);
        }
    }
    return false;
}

bool Busqueda::busqueda_profundidad_limitada(string nodo_inicio, string nodo_final,
    unsigned int limite_de_profundidad, int& nodo_encontrado, Arbol& arbol_de_busqueda)
{
    Grafo grafo;
    grafo.lee_grafo("Ciudades_de_Mexico.csv");
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    unsigned int tamaño_arbol = 0; 
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda, -1, informacion_del_nodo_inicio))
        return false;
    arbol_de_busqueda.crea_arbol(informacion_del_nodo_inicio);
    Agenda agenda;
    agenda.insertar_elemento(0,0);
    while (!agenda.agenda_esta_vacia())
    {
        agenda.posicion(0, nodo_actual);
        tipo_nodo_del_arbol nodo_a_buscar;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, nodo_a_buscar);
        if (nodo_a_buscar.contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        agenda.elimiar_elemento(0);
        tipo_nodo_del_arbol temporal;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal);
        if (temporal.profundidad < limite_de_profundidad)
        {
            grafo.devuelve_vecinos_grafo_no_dirigido(temporal.contenido.nombre_del_nodo, vecinos);
            for (unsigned int i = 0; i < vecinos.size(); i++)
                if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
                {
                    vecinos.erase(vecinos.begin() + i);
                    i--;
                }
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                    arbol_de_busqueda, nodo_actual,
                    informacion_del_hijo_a_adicionar);
                arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                    informacion_del_hijo_a_adicionar);
                tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
                agenda.insertar_elemento(0, tamaño_arbol-1);
            }
        }
    }
    return false;
}

bool Busqueda::busqueda_profundidad_iterativa(string nodo_inicio, string nodo_final,
    unsigned int limite_de_profundidad, unsigned int incremento_de_profundidad,
    int& nodo_encontrado, Arbol& arbol_de_busqueda)
{
    Grafo grafo;
    grafo.lee_grafo("Ciudades_de_Mexico.csv");
    unsigned int profundidad_actual = limite_de_profundidad;
    do
    {
        if (busqueda_profundidad_limitada(nodo_inicio, nodo_final,
            profundidad_actual, nodo_encontrado, arbol_de_busqueda))
            return true;
        if(profundidad_actual < profundidad_actual+incremento_de_profundidad)
            profundidad_actual += incremento_de_profundidad;
    } while (true);
    return false;
}

string Busqueda::devuelve_la_ruta_encontrada(Arbol arbol_de_Busqueda, int nodo_encontrado) const
{
    vector<unsigned int> vector_temporal;
    string camino = "";
    vector_temporal.clear();
    tipo_nodo_del_arbol temporal; 
    while (nodo_encontrado != -1)
    {
        vector_temporal.insert(vector_temporal.begin(), nodo_encontrado);
        arbol_de_Busqueda.buscar_en_el_arbol(nodo_encontrado, temporal);
        nodo_encontrado = temporal.padre;
    }
    for (unsigned int i = 0; i < vector_temporal.size(); i++) {
        arbol_de_Busqueda.buscar_en_el_arbol(vector_temporal.at(i), temporal);
        camino = camino + " " + temporal.contenido.nombre_del_nodo;
    }
    camino += " Costo acumulado: " + to_string(temporal.contenido.costo_acumulado);
    return camino;
}

bool Busqueda::busqueda_bidireccional(string nodo_inicio, string nodo_final, int& nodo_encontrado_desde_el_inicio,
    int& nodo_encontrado_desde_el_final, Arbol& arbol_de_busqueda_desde_el_inicio, Arbol& arbol_de_busqueda_desde_el_final)
{
    Grafo grafo;
    grafo.lee_grafo("Ciudades_de_Mexico.csv");
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_nodo_final;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    int nodo_actual_desde_el_inicio = 0;
    int nodo_actual_desde_el_final = 0;
    vector<tipo_enlace_de_grafo> vecinos_desde_el_inicio;
    vector<tipo_enlace_de_grafo> vecinos_desde_el_final;
    Agenda agenda_desde_el_inicio;
    Agenda agenda_desde_el_final; 
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicio, arbol_de_busqueda_desde_el_inicio,
        -1, informacion_del_nodo_inicio))
        return false;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_final, arbol_de_busqueda_desde_el_final,
        -1, informacion_del_nodo_final))
        return false;
    arbol_de_busqueda_desde_el_inicio.crea_arbol(informacion_del_nodo_inicio);
    arbol_de_busqueda_desde_el_final.crea_arbol(informacion_del_nodo_final);
    agenda_desde_el_inicio.insertar_elemento(0,0);
    agenda_desde_el_final.insertar_elemento(0,0);
    while (true)
    {
        if (agenda_desde_el_inicio.agenda_esta_vacia() &&  agenda_desde_el_final.agenda_esta_vacia())
            return false;
        if (!agenda_desde_el_inicio.agenda_esta_vacia())
        {
            agenda_desde_el_inicio.posicion(0, nodo_actual_desde_el_inicio);
            tipo_nodo_del_arbol Temporal_desde_inicio; 
            arbol_de_busqueda_desde_el_inicio.buscar_en_el_arbol(nodo_actual_desde_el_inicio, Temporal_desde_inicio);
            if (Temporal_desde_inicio.contenido.nombre_del_nodo == nodo_final)
            {
                nodo_encontrado_desde_el_inicio = nodo_actual_desde_el_inicio;
                nodo_encontrado_desde_el_final = -1;
                return true;
            }
            agenda_desde_el_inicio.elimiar_elemento(0);
            arbol_de_busqueda_desde_el_inicio.buscar_en_el_arbol(nodo_actual_desde_el_inicio, Temporal_desde_inicio);
            grafo.devuelve_vecinos_grafo_no_dirigido(Temporal_desde_inicio.contenido.nombre_del_nodo,
                vecinos_desde_el_inicio);
            for (unsigned int i = 0; i < vecinos_desde_el_inicio.size(); i++)
                if (arbol_de_busqueda_desde_el_inicio.esta_un_nodo_en_ancestros(
                    nodo_actual_desde_el_inicio,
                    vecinos_desde_el_inicio[i].nodo_2))
                {
                    vecinos_desde_el_inicio.erase(vecinos_desde_el_inicio.begin() + i);
                    i--;
                }
            for (unsigned int i = 0; i < vecinos_desde_el_inicio.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos_desde_el_inicio[i].nodo_2,
                    arbol_de_busqueda_desde_el_inicio,
                    nodo_actual_desde_el_inicio,
                    informacion_del_hijo_a_adicionar);
                arbol_de_busqueda_desde_el_inicio.agrega_hijo_a_un_nodo(
                    nodo_actual_desde_el_inicio,
                    informacion_del_hijo_a_adicionar);
                unsigned int Tamaño_agenda_desde_inicio = agenda_desde_el_inicio.tamaño_agenda();
                unsigned int Tamaño_arbol_desde_inicio = arbol_de_busqueda_desde_el_inicio.tamaño_del_arbol();
                agenda_desde_el_inicio.insertar_elemento(Tamaño_agenda_desde_inicio, Tamaño_arbol_desde_inicio - 1);
            }
        }
        if (!agenda_desde_el_final.agenda_esta_vacia())
        {
            agenda_desde_el_final.posicion(0, nodo_actual_desde_el_final);
            tipo_nodo_del_arbol Temporal_final; 
            arbol_de_busqueda_desde_el_final.buscar_en_el_arbol(nodo_actual_desde_el_final, Temporal_final);
            if (Temporal_final.contenido.nombre_del_nodo == nodo_inicio)
            {
                nodo_encontrado_desde_el_inicio = -1;
                nodo_encontrado_desde_el_final = nodo_actual_desde_el_final;
                return true;
            }
            agenda_desde_el_final.elimiar_elemento(0);
            arbol_de_busqueda_desde_el_final.buscar_en_el_arbol(nodo_actual_desde_el_final, Temporal_final);
            grafo.devuelve_vecinos_grafo_no_dirigido(Temporal_final.contenido.nombre_del_nodo,
                vecinos_desde_el_final);
            for (unsigned int i = 0; i < vecinos_desde_el_final.size(); i++)
                if (arbol_de_busqueda_desde_el_final.esta_un_nodo_en_ancestros(
                    nodo_actual_desde_el_final,
                    vecinos_desde_el_final[i].nodo_2))
                {
                    vecinos_desde_el_final.erase(vecinos_desde_el_final.begin() + i);
                    i--;
                }
            for (unsigned int i = 0; i < vecinos_desde_el_final.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos_desde_el_final[i].nodo_2,
                    arbol_de_busqueda_desde_el_final,
                    nodo_actual_desde_el_final,
                    informacion_del_hijo_a_adicionar);
                arbol_de_busqueda_desde_el_final.agrega_hijo_a_un_nodo(
                    nodo_actual_desde_el_final,
                    informacion_del_hijo_a_adicionar);
                unsigned tamaño_arbol_desde_final = arbol_de_busqueda_desde_el_final.tamaño_del_arbol();
                agenda_desde_el_final.insertar_elemento(0, tamaño_arbol_desde_final - 1);
            }
        }
        if (agenda_desde_el_inicio.existe_un_nodo_comun_en_las_agendas(
            nodo_encontrado_desde_el_inicio, nodo_encontrado_desde_el_final, arbol_de_busqueda_desde_el_inicio, arbol_de_busqueda_desde_el_final))
            return true;
    }
    return false;
}


//Basicamente, guarda solo de manera local el camino más corto aparente. no analiza más allá. Solo se guarda el camino más corto, por lo que la agenda solo tiene un elemento
//Quitar el ordenamiento
bool Busqueda::busqueda_ascenso_a_la_colina(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda)
{
    Grafo grafo;
    grafo.lee_grafo("Ciudades_de_Mexico.csv");
    tipo_nodo_informacion nodo_de_inicio;
    tipo_nodo_informacion hijo_a_adicionar;
    int nodo_actual = 0;
    unsigned int tamaño_agenda = 0;
    unsigned int tamaño_arbol = 0;
    unsigned int contador = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicial, arbol_de_busqueda, -1, nodo_de_inicio))
        return false;
    arbol_de_busqueda.crea_arbol(nodo_de_inicio);
    Agenda agenda;
    agenda.insertar_elemento(0, 0);
    while (!agenda.agenda_esta_vacia())
    {
        agenda.posicion(0, nodo_actual);
        tipo_nodo_del_arbol temporal;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal);
        if (temporal.contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        agenda.elimiar_elemento(0);
        tipo_nodo_del_arbol temporal_1;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal_1);
        grafo.devuelve_vecinos_grafo_no_dirigido(temporal_1.contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        vector<tipo_nodo_informacion>ordenar;
        ordenar.clear();
        if (!vecinos.empty()) {
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                    arbol_de_busqueda, nodo_actual,
                    hijo_a_adicionar);
                ordenar.push_back(hijo_a_adicionar);
            }
            quicksort(ordenar,0,ordenar.size()-1);
            //countingSort(ordenar);
            

           arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                    ordenar.at(0));
           tamaño_agenda = agenda.tamaño_agenda();
           tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
           agenda.insertar_elemento(tamaño_agenda, tamaño_arbol - 1);
            
        }
        else {
            contador += 1;
            if (contador == 2) {
                nodo_actual -= 2;
                contador = 0;
            }
            nodo_actual -= 1;
            arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal_1);
            grafo.devuelve_vecinos_grafo_no_dirigido(temporal_1.contenido.nombre_del_nodo, vecinos);
            for (unsigned int i = 0; i < vecinos.size(); i++)
                if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
                {
                    vecinos.erase(vecinos.begin() + i);
                    i--;
                }
            ordenar.clear();
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                    arbol_de_busqueda, nodo_actual,
                    hijo_a_adicionar);
                ordenar.push_back(hijo_a_adicionar);
            }
            //countingSort(ordenar);
            quicksort(ordenar, 0, ordenar.size()-1);
            if (ordenar.size() > 1)
                ordenar.erase(ordenar.begin());
          
            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                    ordenar.at(0));
            tamaño_agenda = agenda.tamaño_agenda();
            tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
            agenda.insertar_elemento(tamaño_agenda, tamaño_arbol - 1);
            
        }
    }

    return false;
}
bool Busqueda::busqueda_ascenso_a_la_colina_sin_ordenamiento(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda)
{
    Grafo grafo;
    grafo.lee_grafo("Ciudades_de_Mexico.csv");
    tipo_nodo_informacion nodo_de_inicio;
    tipo_nodo_informacion hijo_a_adicionar;
    int nodo_actual = 0;
    unsigned int tamaño_agenda = 0;
    unsigned int tamaño_arbol = 0;
    unsigned int contador = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicial, arbol_de_busqueda, -1, nodo_de_inicio))
        return false;
    arbol_de_busqueda.crea_arbol(nodo_de_inicio);
    Agenda agenda;
    agenda.insertar_elemento(0, 0);
    while (!agenda.agenda_esta_vacia())
    {
        agenda.posicion(0, nodo_actual);
        tipo_nodo_del_arbol temporal;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal);
        if (temporal.contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        agenda.elimiar_elemento(0);
        tipo_nodo_del_arbol temporal_1;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal_1);
        grafo.devuelve_vecinos_grafo_no_dirigido(temporal_1.contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        vector<tipo_nodo_informacion>ordenar;
        if (!vecinos.empty()) {
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                    arbol_de_busqueda, nodo_actual,
                    hijo_a_adicionar);
                ordenar.push_back(hijo_a_adicionar);
            }
            if (ordenar.size() > 0) {
                tipo_nodo_informacion ayuda_para_ordenar = ordenar.at(0);
                for (unsigned int i = 0; i < ordenar.size(); i++)
                {
                    if (ayuda_para_ordenar.costo_acumulado > ordenar.at(i).costo_acumulado)
                        ayuda_para_ordenar = ordenar.at(i);
                }


                arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                    ayuda_para_ordenar);
                tamaño_agenda = agenda.tamaño_agenda();
                tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
                agenda.insertar_elemento(tamaño_agenda, tamaño_arbol - 1);

            }
        }
        else {
            contador += 1;
            if (contador == 2) {
                nodo_actual -= 2;
                contador = 0;
            }
            nodo_actual -= 1;

        }
    }
    return false;
}


//Examina todos los vecinos, en lugar de solo la opcion más corta, sin embargo los vecinos se ordenan de menor a mayor
//por lo que se guardan así en la agenda, y se atienden primero los que tengan la ruta con menos costo. 
bool Busqueda::busqueda_best_first(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda)
{
    Grafo grafo;
    grafo.lee_grafo("Ciudades_de_Mexico.csv");
    tipo_nodo_informacion nodo_de_inicio;
    tipo_nodo_informacion hijo_a_adicionar;
    int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicial, arbol_de_busqueda, -1, nodo_de_inicio))
        return false;
    arbol_de_busqueda.crea_arbol(nodo_de_inicio);
    Agenda agenda;
    agenda.insertar_elemento(0, 0);
    while (true)
    {
        agenda.posicion(0, nodo_actual);
        tipo_nodo_del_arbol temporal;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal);
        if (temporal.contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        agenda.elimiar_elemento(0);
        tipo_nodo_del_arbol temporal_1;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal_1);
        grafo.devuelve_vecinos_grafo_no_dirigido(temporal_1.contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }

        if (!vecinos.empty()) {
            vector<tipo_nodo_informacion>ordenar;
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                    arbol_de_busqueda, nodo_actual,
                    hijo_a_adicionar);
                ordenar.push_back(hijo_a_adicionar);
            }
            quicksort(ordenar, 0, ordenar.size() - 1);
            //countingSort(ordenar);
            for (unsigned int i = 0; i < ordenar.size(); i++)
            {
                arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                    ordenar.at(i));
                unsigned int tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
                unsigned int tamaño_agenda = agenda.tamaño_agenda();
                agenda.insertar_elemento(tamaño_agenda, tamaño_arbol - 1);
            }
        }
    }
    return false; 

}
bool Busqueda::busqueda_best_first_sin_ordenamiento(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda){
    Grafo grafo;
    grafo.lee_grafo("Ciudades_de_Mexico.csv");
    tipo_nodo_informacion nodo_de_inicio;
    tipo_nodo_informacion hijo_a_adicionar;
    int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicial, arbol_de_busqueda, -1, nodo_de_inicio))
        return false;
    arbol_de_busqueda.crea_arbol(nodo_de_inicio);
    Agenda agenda;
    agenda.insertar_elemento(0, 0);
    while (true)
    {
        agenda.posicion(0, nodo_actual);
        tipo_nodo_del_arbol temporal;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal);
        if (temporal.contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        agenda.elimiar_elemento(0);
        tipo_nodo_del_arbol temporal_1;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal_1);
        grafo.devuelve_vecinos_grafo_no_dirigido(temporal_1.contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }

        if (!vecinos.empty()) {
            vector<tipo_nodo_informacion>ordenar;
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {

                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                    arbol_de_busqueda, nodo_actual,
                    hijo_a_adicionar);
                ordenar.push_back(hijo_a_adicionar);
            } 
            tipo_nodo_informacion vecino_con_menor_costo = ordenar.at(0);
            unsigned int vecino_a_borrar = 0;
            while (!ordenar.empty())
            {
                for (unsigned int i = 0; i < ordenar.size(); i++)
                {
                    if (ordenar.at(i).costo_acumulado < vecino_con_menor_costo.costo_acumulado) {
                        vecino_con_menor_costo = ordenar.at(i);
                        vecino_a_borrar = i;
                    }
                }
                arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                    vecino_con_menor_costo);
                unsigned int tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
                unsigned int tamaño_agenda = agenda.tamaño_agenda();
                agenda.insertar_elemento(tamaño_agenda, tamaño_arbol - 1);
                ordenar.erase(ordenar.begin() + vecino_a_borrar);
                if (ordenar.size() != 0) {
                    vecino_con_menor_costo = ordenar.at(0);
                }
                vecino_a_borrar = 0;
            }
        }
    }
    return false;
}
//Examina un numero limitado de vecinos, los cuales se orden con costo de menor a mayor. 
//Por lo que si solo se quiere examinar un vecino, sería igual a ascenso a la colina
//Si se analizan todos los vecinos es igual a best first
//Tu limitas el tamaño de la agenda, la cual siempre se queda con las mejores opciones, las dos, tres, cuatro mejores opciones
//dependiendo del usuario
bool Busqueda::busqueda_beam_search(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda, unsigned int num_alternativas)
{
    Grafo grafo;
    grafo.lee_grafo("Ciudades_de_Mexico.csv");
    tipo_nodo_informacion nodo_de_inicio;
    tipo_nodo_informacion hijo_a_adicionar;
    int nodo_actual = 0;
    unsigned int tamaño_agenda = 0;
    unsigned int tamaño_arbol = 0;
    unsigned int contador = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicial, arbol_de_busqueda, -1, nodo_de_inicio))
        return false;
    arbol_de_busqueda.crea_arbol(nodo_de_inicio);
    Agenda agenda;
    agenda.insertar_elemento(0, 0);
    while (!agenda.agenda_esta_vacia())
    {
        agenda.posicion(0, nodo_actual);
        tipo_nodo_del_arbol temporal;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal);
        if (temporal.contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        agenda.elimiar_elemento(0);
        tipo_nodo_del_arbol temporal_1;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal_1);
        grafo.devuelve_vecinos_grafo_no_dirigido(temporal_1.contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        vector<tipo_nodo_informacion>ordenar;
        if (!vecinos.empty()) {
            ordenar.clear();
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                    arbol_de_busqueda, nodo_actual,
                    hijo_a_adicionar);
                ordenar.push_back(hijo_a_adicionar);
            }
            quicksort(ordenar, 0, ordenar.size() - 1);
            //countingSort(ordenar);
            if(ordenar.size()>num_alternativas)
                while (ordenar.size() != num_alternativas)
                {
                    ordenar.erase(ordenar.begin() + 1);
                }
            for (unsigned int i = 0; i < ordenar.size(); i++) {
                arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                    ordenar.at(i));
                tamaño_agenda = agenda.tamaño_agenda();
                tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
                agenda.insertar_elemento(tamaño_agenda, tamaño_arbol - 1);
            }
        }
        else {
            contador += 1;
            if (contador == 2) {
                nodo_actual -= 2;
                contador = 0;
            }
            nodo_actual -= 1;
            arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal_1);
            grafo.devuelve_vecinos_grafo_no_dirigido(temporal_1.contenido.nombre_del_nodo, vecinos);
            for (unsigned int i = 0; i < vecinos.size(); i++)
                if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
                {
                    vecinos.erase(vecinos.begin() + i);
                    i--;
                }
            ordenar.clear();
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                    arbol_de_busqueda, nodo_actual,
                    hijo_a_adicionar);
                ordenar.push_back(hijo_a_adicionar);
            }
            //countingSort(ordenar);
            quicksort(ordenar, 0, ordenar.size() - 1);
            if (ordenar.size() > 1)
                ordenar.erase(ordenar.begin() + 0);
            
            if (ordenar.size() > num_alternativas)
                while (ordenar.size() != num_alternativas)
                {
                    ordenar.erase(ordenar.begin() + 1);
                }
            for (unsigned int i = 0; i < ordenar.size(); i++) {
                arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                    ordenar.at(i));
                tamaño_agenda = agenda.tamaño_agenda();
                tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
                agenda.insertar_elemento(tamaño_agenda, tamaño_arbol - 1);
            }
        }
    }

    return false;
}
bool Busqueda::busqueda_beam_search_sin_ordenamiento(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda, unsigned int num_alternativas)
{
    Grafo grafo;
    grafo.lee_grafo("Ciudades_de_Mexico.csv");
    tipo_nodo_informacion nodo_de_inicio;
    tipo_nodo_informacion hijo_a_adicionar;
    int nodo_actual = 0;
    unsigned int contador = 0; 
    vector<tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicial, arbol_de_busqueda, -1, nodo_de_inicio))
        return false;
    arbol_de_busqueda.crea_arbol(nodo_de_inicio);
    Agenda agenda;
    agenda.insertar_elemento(0, 0);
    while (true)
    {
        agenda.posicion(0, nodo_actual);
        tipo_nodo_del_arbol temporal;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal);
        if (temporal.contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        agenda.elimiar_elemento(0);
        tipo_nodo_del_arbol temporal_1;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal_1);
        grafo.devuelve_vecinos_grafo_no_dirigido(temporal_1.contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        vector<tipo_nodo_informacion>ordenar;
        if (!vecinos.empty()) {
            ordenar.clear();
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {

                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                    arbol_de_busqueda, nodo_actual,
                    hijo_a_adicionar);
                ordenar.push_back(hijo_a_adicionar);
            }
            tipo_nodo_informacion vecino_con_menor_costo = ordenar.at(0);
            if (ordenar.size() > num_alternativas) {
                unsigned int vecino_a_borrar = 0;
                unsigned int size_vector_ordenado = ordenar.size();
                unsigned int size_agenda_ordenada = ordenar.size() - num_alternativas;
                while (size_vector_ordenado != size_agenda_ordenada)
                {
                    for (unsigned int i = 0; i < ordenar.size(); i++)
                    {
                        if (ordenar.at(i).costo_acumulado < vecino_con_menor_costo.costo_acumulado) {
                            vecino_con_menor_costo = ordenar.at(i);
                            vecino_a_borrar = i;
                        }
                    }
                    arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                        vecino_con_menor_costo);
                    unsigned int tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
                    unsigned int tamaño_agenda = agenda.tamaño_agenda();
                    agenda.insertar_elemento(tamaño_agenda, tamaño_arbol - 1);
                    ordenar.erase(ordenar.begin() + vecino_a_borrar);
                    if (ordenar.size() != 0) {
                        vecino_con_menor_costo = ordenar.at(0);
                    }
                    vecino_a_borrar = 0;
                    size_vector_ordenado -= 1;
                }
            }
            else {
                while (!ordenar.empty())
                {
                    unsigned int vecino_a_borrar = 0;
                    for (unsigned int i = 0; i < ordenar.size(); i++)
                    {
                        if (ordenar.at(i).costo_acumulado < vecino_con_menor_costo.costo_acumulado) {
                            vecino_con_menor_costo = ordenar.at(i);
                            vecino_a_borrar = i;
                        }
                    }
                    arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                        vecino_con_menor_costo);
                    unsigned int tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
                    unsigned int tamaño_agenda = agenda.tamaño_agenda();
                    agenda.insertar_elemento(tamaño_agenda, tamaño_arbol - 1);
                    ordenar.erase(ordenar.begin() + vecino_a_borrar);
                    if (ordenar.size() != 0) {
                        vecino_con_menor_costo = ordenar.at(0);
                    }
                    vecino_a_borrar = 0;
                }
            }
        }
        else {
            contador += 1;
            if (contador == 2) {
                nodo_actual -= 2;
                contador = 0;
            }
            nodo_actual -= 1;

        }
    }
    return false;
};

//Basicamente primero tiene que llegar a la meta y guardarse el valor de su costo acumulado
//El algoritmo limita las ramas si es que su costo acumulado ya se pasó del costo acumulado de la meta
//En caso de que la rama que se está generado se pasó de la meta, directamente no se crea, sin añadirla a la agenda
//En caso de que si sea menor el costo de la rama, si se añade a la agenda
//Esto limita a la agenda, ya que solo se añaden los nodos que su costo acumulado sea menor al de la meta
//En caso de encontrar otra meta, se compara si su costo acumulado es menor al costo acumulado de la meta anterior
//En caso de que sea menor, el valor de nodo encontrado cambia, en caso que no, no cambia. 
//El algoritmo se ejecuta hasta tener la agenda vacia, esta se sabe que se vacia ya que esta limitada a solo tener valores pequeños
bool Busqueda::busqueda_A(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda)
{
    Grafo grafo;
    grafo.lee_grafo("Ciudades_de_Mexico.csv");
    tipo_nodo_informacion nodo_de_inicio;
    tipo_nodo_informacion hijo_a_adicionar;
    int nodo_actual = 0;
    float heuristica = 0; 
    vector<tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicial, arbol_de_busqueda, -1, nodo_de_inicio))
        return false;
    grafo.calcular_heuristica(nodo_de_inicio, heuristica, nodo_final);
    nodo_de_inicio.costo_estimado = heuristica;
    arbol_de_busqueda.crea_arbol(nodo_de_inicio);
    Agenda agenda;
    agenda.insertar_elemento(0, 0);
    while (!agenda.agenda_esta_vacia())
    {
        agenda.posicion(0, nodo_actual);
        tipo_nodo_del_arbol temporal;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal);
        if (temporal.contenido.nombre_del_nodo == nodo_final)
        {
            if(nodo_encontrado != -1){
                tipo_nodo_del_arbol help_1, help_2;
                arbol_de_busqueda.buscar_en_el_arbol(nodo_encontrado, help_1);
                arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, help_2);
                if (help_1.contenido.costo_acumulado > help_2.contenido.costo_acumulado)
                    nodo_encontrado = nodo_actual;
            }
            else
                nodo_encontrado = nodo_actual;

            unsigned int size_agenda = agenda.tamaño_agenda();
            tipo_nodo_del_arbol nodo_temporal, nodo_temporal_1;
            int posicion_actual = 0; 
            for (unsigned int i = 0; i < (unsigned int)(size_agenda); i++) {
                agenda.posicion(i, posicion_actual);
                arbol_de_busqueda.buscar_en_el_arbol(posicion_actual, nodo_temporal);
                arbol_de_busqueda.buscar_en_el_arbol(posicion_actual, nodo_temporal_1);
                if (nodo_temporal.contenido.costo_acumulado > nodo_temporal_1.contenido.costo_acumulado){
                    agenda.elimiar_elemento(i);
                    i--;
                }
            }
            size_agenda = agenda.tamaño_agenda();
            if (size_agenda == 0) {
                nodo_encontrado = nodo_actual;
                return true;
            }
        }
        agenda.elimiar_elemento(0);
        tipo_nodo_del_arbol temporal_1;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal_1);
        grafo.devuelve_vecinos_grafo_no_dirigido(temporal_1.contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }

        if (!vecinos.empty()) {
            vector<tipo_nodo_informacion>ordenar;
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                    arbol_de_busqueda, nodo_actual,
                    hijo_a_adicionar);
                ordenar.push_back(hijo_a_adicionar);
            }
            if (nodo_encontrado != -1) {
                for (unsigned int i = 0; i < ordenar.size(); i++)
                {

                    if (nodo_encontrado != -1) {
                        tipo_nodo_del_arbol ayuda;
                        arbol_de_busqueda.buscar_en_el_arbol(nodo_encontrado, ayuda);
                        grafo.calcular_heuristica(ordenar.at(i), heuristica, nodo_final);
                        ordenar.at(i).costo_estimado = heuristica;
                        if (ordenar.at(i).costo_acumulado + ordenar.at(i).costo_estimado < ayuda.contenido.costo_acumulado + ayuda.contenido.costo_estimado) {
                            arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                                ordenar.at(i));
                            unsigned int tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
                            agenda.insertar_elemento(0, tamaño_arbol - 1);
                        }
                    }

                }
            }
            else {
                vector<float>mejores_heuristicas;
                while (!ordenar.empty()) {
                    if (mejores_heuristicas.empty())
                        for (unsigned int i = 0; i < ordenar.size(); i++) {
                            grafo.calcular_heuristica(ordenar.at(i), heuristica, nodo_final);
                            ordenar.at(i).costo_estimado = heuristica;
                            mejores_heuristicas.push_back(ordenar.at(i).costo_acumulado + ordenar.at(i).costo_estimado);
                        }
                    int localidad = 0;
                    float heuristica_actual = mejores_heuristicas.at(0);
                    for (unsigned int i = 0; i < mejores_heuristicas.size(); i++)
                    {
                        if (heuristica_actual > mejores_heuristicas.at(i)) {
                            heuristica_actual = mejores_heuristicas.at(i);
                            localidad = i;
                        }
                    }
                    arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                        ordenar.at(localidad));
                    unsigned int tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
                    unsigned int tamaño_agenda = agenda.tamaño_agenda();
                    agenda.insertar_elemento(tamaño_agenda, tamaño_arbol - 1);
                    ordenar.erase(ordenar.begin() + localidad);
                    mejores_heuristicas.erase(mejores_heuristicas.begin() + localidad);
                    if (ordenar.size() != 0) {
                        heuristica_actual = mejores_heuristicas.at(0);
                    }
                    localidad = 0;
                }
            }
        }

    }

    if(nodo_encontrado != -1)
        return true;
    return false; 
    
}

void Grafo::calcular_heuristica(tipo_nodo_informacion vecino, float& heuristica, string nodo_final) {
    float coordenada_x_nodo_actual = 0.0f, coordenada_y_nodo_actual = 0.0f, coordenada_x_nodo_final = 0.0f, coordenada_y_nodo_final = 0.0f;
    for (unsigned int i = 0; i < grafo.size(); i++)
    {
        if (vecino.nombre_del_nodo == grafo.at(i).nodo_1) {
            coordenada_x_nodo_actual = grafo.at(i).posicion_x_nodo_1;
            coordenada_y_nodo_actual = grafo.at(i).posicion_y_nodo_1;
        }
        if (vecino.nombre_del_nodo == grafo.at(i).nodo_2) {
            coordenada_x_nodo_actual = grafo.at(i).posicion_x_nodo_2;
            coordenada_y_nodo_actual = grafo.at(i).posicion_y_nodo_2;
        }
        if (nodo_final == grafo.at(i).nodo_1) {
            coordenada_x_nodo_final = grafo.at(i).posicion_x_nodo_1;
            coordenada_y_nodo_final = grafo.at(i).posicion_y_nodo_1;
        }
        if (nodo_final == grafo.at(i).nodo_2) {
            coordenada_x_nodo_final = grafo.at(i).posicion_x_nodo_2;
            coordenada_y_nodo_final = grafo.at(i).posicion_y_nodo_2;
        }
    }
    (heuristica) = (float)(pow((coordenada_x_nodo_final - coordenada_x_nodo_actual), 2) + pow((coordenada_y_nodo_final - coordenada_y_nodo_actual), 2));
}

bool Busqueda::busqueda_branch_and_bound(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda)
{
    Grafo grafo;
    grafo.lee_grafo("Ciudades_de_Mexico.csv");
    tipo_nodo_informacion nodo_de_inicio;
    tipo_nodo_informacion hijo_a_adicionar;
    int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(nodo_inicial, arbol_de_busqueda, -1, nodo_de_inicio))
        return false;
    arbol_de_busqueda.crea_arbol(nodo_de_inicio);
    Agenda agenda;
    agenda.insertar_elemento(0, 0);
    while (!agenda.agenda_esta_vacia())
    {
        agenda.posicion(0, nodo_actual);
        tipo_nodo_del_arbol temporal;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal);
        if (temporal.contenido.nombre_del_nodo == nodo_final)
        {
            if (nodo_encontrado != -1) {
                tipo_nodo_del_arbol help_1, help_2;
                arbol_de_busqueda.buscar_en_el_arbol(nodo_encontrado, help_1);
                arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, help_2);
                if (help_1.contenido.costo_acumulado > help_2.contenido.costo_acumulado)
                    nodo_encontrado = nodo_actual;
            }
            else
                nodo_encontrado = nodo_actual;
            unsigned int size_agenda = agenda.tamaño_agenda();
            tipo_nodo_del_arbol nodo_temporal, nodo_temporal_1;
            int posicion_actual = 0;
            for (unsigned int i = 0; i < size_agenda; i++) {
                agenda.posicion(i, posicion_actual);
                arbol_de_busqueda.buscar_en_el_arbol(posicion_actual, nodo_temporal);
                arbol_de_busqueda.buscar_en_el_arbol(posicion_actual, nodo_temporal_1);
                if (nodo_temporal.contenido.costo_acumulado > nodo_temporal_1.contenido.costo_acumulado) {
                    agenda.elimiar_elemento(i);
                    i--;
                }
            }
            size_agenda = agenda.tamaño_agenda();
            if (size_agenda == 0) {
                nodo_encontrado = nodo_actual;
                return true;
            }
        }
        agenda.elimiar_elemento(0);
        tipo_nodo_del_arbol temporal_1;
        arbol_de_busqueda.buscar_en_el_arbol(nodo_actual, temporal_1);
        grafo.devuelve_vecinos_grafo_no_dirigido(temporal_1.contenido.nombre_del_nodo, vecinos);
        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (arbol_de_busqueda.esta_un_nodo_en_ancestros(nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }

        if (!vecinos.empty()) {
            vector<tipo_nodo_informacion>ordenar;
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {
                grafo.devuelve_informacion_de_un_vertice_grafo_no_dirigido(vecinos[i].nodo_2,
                    arbol_de_busqueda, nodo_actual,
                    hijo_a_adicionar);
                ordenar.push_back(hijo_a_adicionar);
            }
            for (unsigned int i = 0; i < ordenar.size(); i++)
            {

                if (nodo_encontrado != -1) {
                    tipo_nodo_del_arbol ayuda;
                    arbol_de_busqueda.buscar_en_el_arbol(nodo_encontrado, ayuda);
                    if (ordenar.at(i).costo_acumulado < ayuda.contenido.costo_acumulado) {
                        arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                            ordenar.at(i));
                        unsigned int tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
                        agenda.insertar_elemento(0, tamaño_arbol - 1);
                    }
                }
                else {
                    arbol_de_busqueda.agrega_hijo_a_un_nodo(nodo_actual,
                        ordenar.at(i));
                    unsigned int tamaño_arbol = arbol_de_busqueda.tamaño_del_arbol();
                    agenda.insertar_elemento(0, tamaño_arbol - 1);
                }
            }
        }

    }
    if (nodo_encontrado != -1)
        return true;
    return false;
    
}

void Busqueda::quicksort(vector<tipo_nodo_informacion>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    float pivot = arr[(left + right) / 2].costo_acumulado;
    int i = left;
    int j = right;

    while (i <= j) {
        while (arr[i].costo_acumulado < pivot) {
            i++;
        }

        while (arr[j].costo_acumulado > pivot) {
            j--;
        }

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    quicksort(arr, left, j);
    quicksort(arr, i, right);
}

string Busqueda::devuelve_la_ruta_encontrada_busqueda_bidireccional(int nodo_encontrado_desde_el_inicio,
    int nodo_encontrado_desde_el_final, Arbol arbol_de_busqueda_desde_el_inicio, Arbol arbol_de_busqueda_desde_el_final) const
{
    vector<unsigned int> temporal;
    string camino_desde_el_inicio = "";
    string camino_desde_el_final = "";
    tipo_nodo_del_arbol temporal_inicio;
    tipo_nodo_del_arbol temporal_final;
    if (nodo_encontrado_desde_el_inicio != -1)
    {
        temporal.clear();
        while (nodo_encontrado_desde_el_inicio != -1)
        {
            arbol_de_busqueda_desde_el_inicio.buscar_en_el_arbol(nodo_encontrado_desde_el_inicio, temporal_inicio);
            temporal.push_back(nodo_encontrado_desde_el_inicio);
            nodo_encontrado_desde_el_inicio = temporal_inicio.padre;
        }
        for (int i = (int)(temporal.size() - 1); i >= 0; i--) {
            arbol_de_busqueda_desde_el_inicio.buscar_en_el_arbol(temporal[i], temporal_inicio);
            camino_desde_el_inicio = camino_desde_el_inicio + " " +
             temporal_inicio.contenido.nombre_del_nodo;
        }
    }
    if (nodo_encontrado_desde_el_final != -1)
    {
        temporal.clear();
        arbol_de_busqueda_desde_el_final.buscar_en_el_arbol(nodo_encontrado_desde_el_final, temporal_final);
        nodo_encontrado_desde_el_final = temporal_final.padre;
        while (nodo_encontrado_desde_el_final != -1)
        {
            arbol_de_busqueda_desde_el_final.buscar_en_el_arbol(nodo_encontrado_desde_el_final, temporal_final);
            temporal.push_back(nodo_encontrado_desde_el_final);
            nodo_encontrado_desde_el_final = temporal_final.padre;
        }
        for (int i = (int)(temporal.size() - 1); i >= 0; i--) {
            arbol_de_busqueda_desde_el_final.buscar_en_el_arbol(temporal[i], temporal_final);
            camino_desde_el_final = temporal_final.contenido.nombre_del_nodo + " " + camino_desde_el_final;
        }
    }
    return camino_desde_el_inicio + " " + camino_desde_el_final;
}




