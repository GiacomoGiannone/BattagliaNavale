#pragma once

#include <iostream>
#include <vector>

#include "Partita.hpp"
#include "Giocatore.hpp"
#include "Nave.hpp"

#include "Incrociatore.hpp"
#include "Corazzata.hpp"
#include "Portaerei.hpp"
#include "Sottomarino.hpp"
#include <unordered_map>


class BattagliaNavale
{
private:
	static BattagliaNavale* instance;
	std::vector<Partita*> ListaPartite;
	std::vector<Giocatore> ListaGiocatori;
	std::vector<std::unique_ptr<Nave> > ListaNavi;

	Nave* naveSelezionata;

	BattagliaNavale()
	{
		ListaNavi.push_back(std::make_unique<Incrociatore>());
		ListaNavi.push_back(std::make_unique<Corazzata>());
		ListaNavi.push_back(std::make_unique<Portaerei>());
		ListaNavi.push_back(std::make_unique<Sottomarino>());

		naveSelezionata = nullptr;
	}

	~BattagliaNavale() = default;
public:
	//BattagliaNavale();
	//~BattagliaNavale();
	BattagliaNavale(const BattagliaNavale&) = delete;
	BattagliaNavale& operator=(const BattagliaNavale&) = delete;
	static BattagliaNavale* getInstance()
	{
		if (!instance)
		{
			instance = new BattagliaNavale();
		}
		return instance;
	}
	void IniziaTurnoSchieramento(Giocatore* g, Partita* p);
	bool ScegliNave(int id);
	bool ScegliPosizione(int x, char y, std::string direction);
	//bool ScegliPosizione(int x, char y, std::string direction, int dim);
	bool ConfermaPiazzamentoNavi();
	void ScegliPosizioneAttacco(int x, char y);
	void AggiornaGriglia();
	void IniziaNuovaPartita(Giocatore* _g1 /*Giocatore* _g2, Griglia* _griglia_attacchi_1, Griglia* _griglia_attacchi_2, Griglia* _griglia_posizioni_1, Griglia* _griglia_posizioni_2*/);
	void Scegli_Impostazioni(bool giocatoreUmano, std::pair<int, int> dimGriglia, int numNavi, std::string nomeAvversario);
	void ConfermaImpostazioni();
	Partita* getPartitaCorrente();
	void setNaveSelezionata(Nave* nave);
	std::unordered_map<std::string, int> CreaMappaNavi();
	Nave* getNave();
	void GestisciFinePartita();
};