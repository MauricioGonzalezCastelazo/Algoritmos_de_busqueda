#pragma once

#include <string>
#include <vector>
#include <stddef.h>
#include <iostream>
#include "Agenda.h"
#include"Arbol.h"
#include "Grafo.h"
using namespace std;

class Busqueda
{
public:
	Busqueda();
	~Busqueda();

	//Busqueda sin informacion 
	bool busqueda_a_lo_ancho(string nodo_inicio, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda);
	bool busqueda_primero_en_profundidad(string nodo_inicio, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda);
	bool busqueda_profundidad_limitada(string nodo_inicio, string nodo_final,
		unsigned int limite_de_profundidad, int& nodo_encontrado, Arbol& arbol_de_busqueda);
	bool busqueda_profundidad_iterativa(string nodo_inicio, string nodo_final,
		unsigned int limite_de_profundidad, unsigned int incremento_de_profundidad,
		int& nodo_encontrado, Arbol& arbol_de_busqueda);
	bool busqueda_bidireccional(string nodo_inicio, string nodo_final, int& nodo_encontrado_desde_el_inicio,
		int& nodo_encontrado_desde_el_final, Arbol& arbol_de_busqueda_desde_el_inicio, Arbol& arbol_de_busqueda_desde_el_final);

	//Busqueda con informacion

	bool busqueda_ascenso_a_la_colina(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda);
	bool busqueda_ascenso_a_la_colina_sin_ordenamiento(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda);
	bool busqueda_best_first(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda);
	bool busqueda_best_first_sin_ordenamiento(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda);
	bool busqueda_beam_search(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda,unsigned int num_alternativas);
	bool busqueda_beam_search_sin_ordenamiento(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda, unsigned int num_alternativas);
	bool busqueda_branch_and_bound(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda);
	bool busqueda_A(string nodo_inicial, string nodo_final, int& nodo_encontrado, Arbol& arbol_de_busqueda);

	string devuelve_la_ruta_encontrada(Arbol arbol_de_Busqueda, int nodo_encontrado) const;
	string devuelve_la_ruta_encontrada_busqueda_bidireccional(int nodo_encontrado_desde_el_inicio,
		int nodo_encontrado_desde_el_final, Arbol arbol_de_busqueda_desde_el_inicio, Arbol arbol_de_busqueda_desde_el_final) const;

private:
	void quicksort(vector<tipo_nodo_informacion>& arr, int left, int right);
	
};





