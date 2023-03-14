#pragma once
#include <string>
#include <vector>
#include <stddef.h>
#include <iostream>
#include "Arbol.h"

struct tipo_enlace_de_grafo
{
	string nodo_1 = "";
	float costo_nodo_1 = 0.0f;
	string nodo_2 = "";
	float costo_nodo_2 = 0.0f;
	float costo_del_enlace = 0.0f;
	float posicion_x_nodo_1 = 0.0f;
	float posicion_y_nodo_1 = 0.0f;
	float posicion_x_nodo_2 = 0.0f;
	float posicion_y_nodo_2 = 0.0f;
};


class Grafo {
public:
	Grafo();
	~Grafo();
	void devuelve_vecinos_grafo_no_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const;
	bool devuelve_informacion_de_un_vertice_grafo_no_dirigido(string nodo, Arbol arbol_de_busqueda,
		int nodo_padre, tipo_nodo_informacion& informacion) const;
	bool lee_grafo(string archivo);
	void calcular_heuristica(tipo_nodo_informacion vecino, float& heuristica, string nodo_final);

private:
	vector<tipo_enlace_de_grafo> grafo;
};
