#pragma once

#include <string>
#include <vector>
#include <stddef.h>
#include <iostream>
#include "Arbol.h"


using namespace std;
class Agenda {
public:
	Agenda();
	~Agenda();
	bool existe_un_nodo_comun_en_las_agendas(
		int& nodo_comun_inicio, int& nodo_comun_final, Arbol arbol_desde_inicio, Arbol arbol_desde_final) const;
	bool agenda_esta_vacia()const;
	void posicion(int localidad, int& valor_devuelto)const;
	bool elimiar_elemento(int posicion);
	void insertar_elemento(unsigned int posicion, int informacion);
	unsigned int tamaño_agenda()const;
private:
	vector<unsigned int> agenda;

};




