#pragma once

#include <iostream>

class Impostazioni
{
private:
	bool giocatoreUmano;
	std::pair<int, int> dim_griglia;
	int num_navi;
public:
	/*Impostazioni() : num_giocatori(0), dim_griglia({0, 0}), num_navi(0)
	{
		// Inizializzazione di default
	}*/
	Impostazioni(bool _giocatoreUmano, std::pair<int, int> _dim_griglia, int _num_navi) 
	{
		giocatoreUmano = _giocatoreUmano;
		dim_griglia = _dim_griglia;
		num_navi = _num_navi;
	};

	int getNumNavi() { return num_navi; }
	bool getGiocatoreUmano() { return giocatoreUmano; }
	std::pair<int, int> getDimGriglia() { return dim_griglia; }
};