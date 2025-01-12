#pragma once

#include <iostream>

class Impostazioni
{
private:
	int num_giocatori;
	std::pair<int, int> dim_griglia;
	int num_navi;
public:
	Impostazioni()
		: num_giocatori(0), dim_griglia({ 0, 0 }), num_navi(0)
	{
		// Inizializzazione di default
	}
	Impostazioni(int _num_giocatori, std::pair<int, int> _dim_griglia, int _num_navi) {};
};