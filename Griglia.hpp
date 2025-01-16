#pragma once

#ifndef GRIGLIA_HPP
#define GRIGLIA_HPP

#include <iostream>
#include <vector>

//#include "Giocatore.hpp"
#include "Casella.hpp"
#include "Attacco.hpp"

class Giocatore;

class Griglia
{
private:
	std::pair<int, int> dim;
	Giocatore *g;
	std::vector<std::vector<Casella*>> ListaCaselle;
	std::vector<Attacco> ListaAttacchi;
public:
	Griglia() { g = nullptr; };
	Griglia(std::pair<int, int> _dim, Giocatore* _g);
	std::vector<Casella*> ScegliPosizione(int x, char y, std::string direction, int dim);
	Casella* FindCasella(int x, char y);
	void AggiornaGriglia();
	Giocatore* getGiocatore();
	void CreateAttacco(int x, char y, bool esito);
	void StampaGriglia();
	bool isOver();
	void DrawAttackGrid();
	Attacco getAttacco(int x, char y);
};

#endif