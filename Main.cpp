#include "Busqueda.h"
int main() {
	Busqueda p;

	int nodo_encontrado = -1, nodo_encontrado_1 = -1, nodo_encontrado_2 = -1, nodo_encontrado_3 = -1
		, nodo_encontrado_4 = -1, nodo_encontrado_4_final = -1, nodo_encontrado_5 = -1, nodo_encontrado_6 = -1, nodo_encontrado_7 = -1
		, nodo_encontrado_8 = -1, nodo_encontrado_9 = -1, nodo_encontrado_10 = -1
		, nodo_encontrado_11 = -1, nodo_encontrado_12 = -1;

	string camino = "", camino_1 = "", camino_2 = "", camino_3 = "", camino_4 = "", camino_5 = "", camino_6 = "", camino_7 = ""
		, camino_8 = "", camino_9 = "", camino_10 = "", camino_11 = "", camino_12 = "";

	Arbol arbol_de_busqueda, arbol_de_busqueda_1, arbol_de_busqueda_2, arbol_de_busqueda_3, 
		arbol_de_busqueda_4, arbol_de_busqueda_4_final, arbol_de_busqueda_5, arbol_de_busqueda_6, arbol_de_busqueda_7
		, arbol_de_busqueda_8, arbol_de_busqueda_9, arbol_de_busqueda_10, arbol_de_busqueda_11
		, arbol_de_busqueda_12;

	

	if (p.busqueda_a_lo_ancho("Mexico", "Guadalajara", nodo_encontrado, arbol_de_busqueda))
		camino = p.devuelve_la_ruta_encontrada(arbol_de_busqueda, nodo_encontrado);
	cout << "\n" << "Camino de busqueda a lo ancho: " << camino << "\n";

	if (p.busqueda_primero_en_profundidad("Mexico", "Guadalajara", nodo_encontrado_1, arbol_de_busqueda_1))
		camino_1 = p.devuelve_la_ruta_encontrada(arbol_de_busqueda_1, nodo_encontrado_1);
	cout << "\n" << "Camino de busqueda primero en profundidad: " << camino_1 << "\n";

	if (p.busqueda_profundidad_limitada("Mexico", "Guadalajara", 7, nodo_encontrado_2, arbol_de_busqueda_2))
		camino_2 = p.devuelve_la_ruta_encontrada(arbol_de_busqueda_2, nodo_encontrado_2);
	cout << "\n" << "Camino de busqueda primero en profundidad limitada con k = 7: " << camino_2 << "\n";

	if (p.busqueda_profundidad_iterativa("Mexico", "Guadalajara", 7, 1, nodo_encontrado_3, arbol_de_busqueda_3))
		camino_3 = p.devuelve_la_ruta_encontrada(arbol_de_busqueda_3, nodo_encontrado_3);
	cout << "\n" << "Camino de busqueda primero en profundidad iterativa: " << camino_3 << "\n";

	if (p.busqueda_bidireccional("Mexico", "Guadalajara", nodo_encontrado_4, nodo_encontrado_4_final, arbol_de_busqueda_4, arbol_de_busqueda_4_final))
		camino_4 = p.devuelve_la_ruta_encontrada_busqueda_bidireccional(nodo_encontrado_4, nodo_encontrado_4_final, arbol_de_busqueda_4, arbol_de_busqueda_4_final);
	cout << "\n" << "Camino de busqueda bidireccional: " << camino_4 << "\n";

	if (p.busqueda_ascenso_a_la_colina("Mexico", "Guadalajara", nodo_encontrado_5, arbol_de_busqueda_5))
		camino_5 = p.devuelve_la_ruta_encontrada(arbol_de_busqueda_5, nodo_encontrado_5);
	cout << "\n" << "Camino de busqueda ascenso a la colina: " << camino_5 << "\n";

	//Modificar
	if (p.busqueda_ascenso_a_la_colina_sin_ordenamiento("Mexico", "Guadalajara", nodo_encontrado_6, arbol_de_busqueda_6))
		camino_6 = p.devuelve_la_ruta_encontrada(arbol_de_busqueda_6, nodo_encontrado_6);
	cout << "\n" << "Camino de busqueda ascenso a la colina sin ordenamiento: " << camino_6 << "\n";

	if (p.busqueda_best_first("Mexico", "Guadalajara", nodo_encontrado_7, arbol_de_busqueda_7))
		camino_7 = p.devuelve_la_ruta_encontrada(arbol_de_busqueda_7, nodo_encontrado_7);
	cout << "\n" << "Camino de busqueda best first: " << camino_7 << "\n";

	if (p.busqueda_best_first_sin_ordenamiento("Mexico", "Guadalajara", nodo_encontrado_8, arbol_de_busqueda_8))
		camino_8 = p.devuelve_la_ruta_encontrada(arbol_de_busqueda_8, nodo_encontrado_8);
	cout << "\n" << "Camino de busqueda best first sin ordenamiento: " << camino_8 << "\n";

	if (p.busqueda_beam_search("Mexico", "Guadalajara", nodo_encontrado_9, arbol_de_busqueda_9, 2))
		camino_9 = p.devuelve_la_ruta_encontrada(arbol_de_busqueda_9, nodo_encontrado_9);
	cout << "\n" << "Camino de busqueda beam search: " << camino_9 << "\n";

	//Esta mal
	if (p.busqueda_beam_search_sin_ordenamiento("Mexico", "Guadalajara", nodo_encontrado_10, arbol_de_busqueda_10, 3))
		camino_10 = p.devuelve_la_ruta_encontrada(arbol_de_busqueda_10, nodo_encontrado_10);
	cout << "\n" << "Camino de busqueda beam search sin ordenamiento: " << camino_10 << "\n";

	if (p.busqueda_branch_and_bound("Mexico", "Guadalajara", nodo_encontrado_11, arbol_de_busqueda_11))
		camino_11 = p.devuelve_la_ruta_encontrada(arbol_de_busqueda_11, nodo_encontrado_11);
	cout << "\n" << "Camino de busqueda branch and bound: " << camino_11 << "\n";

	if (p.busqueda_A("Mexico", "Guadalajara", nodo_encontrado_12, arbol_de_busqueda_12))
		camino_12 = p.devuelve_la_ruta_encontrada(arbol_de_busqueda_12, nodo_encontrado_12);
	cout << "\n" << "Camino de busqueda A*: " << camino_12 << "\n";

	return 0;

	

}