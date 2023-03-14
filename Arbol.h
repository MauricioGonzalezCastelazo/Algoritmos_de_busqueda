#pragma once

#include <string>
#include <vector>
#include <stddef.h>
#include <iostream>

using namespace std;

struct tipo_nodo_informacion
{
	string nombre_del_nodo = "";
	float costo_acumulado = 0.0f;
	float costo_estimado = 0.0f;
};

struct tipo_nodo_del_arbol
{
	tipo_nodo_informacion contenido;
	int padre = -1;
	unsigned int profundidad = 0;
	vector<unsigned int> hijos;
};

class Arbol {
public:
	Arbol();
	~Arbol();
	void crea_arbol(tipo_nodo_informacion contenido);
	void agrega_hijo_a_un_nodo(int padre, tipo_nodo_informacion contenido);
	bool esta_un_nodo_en_ancestros(const int nodo_origen, string nombre_del_nodo) const;
	bool buscar_en_el_arbol(int posicion, tipo_nodo_del_arbol& nodo_encontrado)const;
	unsigned int tamaño_del_arbol()const; 
private:
	vector<tipo_nodo_del_arbol> arbol_de_busqueda;

};






