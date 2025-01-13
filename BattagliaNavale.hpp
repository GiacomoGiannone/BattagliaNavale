#pragma once

#include <iostream>
#include <vector>

#include "Partita.hpp"
#include "Giocatore.hpp"
#include "Nave.hpp"

class BattagliaNavale
{
private:
	std::vector<Partita*> ListaPartite;
	std::vector<Giocatore> ListaGiocatori;
	std::vector<std::unique_ptr<Nave>> ListaNavi;

	Nave* naveSelezionata;
public:
	BattagliaNavale();
	~BattagliaNavale();
	void IniziaTurnoSchieramento(Giocatore* g, Partita* p);
	bool ScegliNave();
	bool ScegliPosizione(int x, char y, std::string direction);
	//bool ScegliPosizione(int x, char y, std::string direction, int dim);
	bool ConfermaPiazzamentoNavi();
	void ScegliPosizioneAttacco(int x, char y);
	void AggiornaGriglia();
	void IniziaNuovaPartita(Giocatore* _g1, Giocatore* _g2, Griglia _griglia_attacchi_1, Griglia _griglia_attacchi_2, Griglia _griglia_posizioni_1, Griglia _griglia_posizioni_2);
	void Scegli_Impostazioni(bool giocatoreUmano, std::pair<int, int> dimGriglia, int numNavi, std::string nomeAvversario);
	void ConfermaImpostazioni();
	Partita* getPartitaCorrente();
};