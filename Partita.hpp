#pragma once

#ifndef PARTITA_HPP
#define PARTITA_HPP

#include <iostream>
#include <map>

#include "Giocatore.hpp"
#include "Impostazioni.hpp"
#include "NaveSchierata.hpp"
#include "Casella.hpp"

class Partita
{
public :
	enum Stato { attiva, finita };
private:
	Giocatore *g1,*g2;
	Impostazioni *i;
	std::vector<std::shared_ptr<Turno>> ListaTurni;
	Turno* t;
	//std::map<Giocatore, Griglia*> mapGiocatoreGriglie;
	Griglia *griglia_attacchi_1, *griglia_attacchi_2;
	Griglia *griglia_posizioni_1, *griglia_posizioni_2;
	Stato stato;
	std::vector<NaveSchierata*> navi;

	Giocatore* getInstanceByNick(std::string nick);
	bool GeneraEsito(StatoCasella stato);

public:
	Partita() {};
	Partita(Giocatore* _g1/* Giocatore* _g2, Griglia* _griglia_attacchi_1, Griglia* _griglia_attacchi_2, Griglia* _griglia_posizioni_1, Griglia* _griglia_posizioni_2*/);
	bool creaTurno(Giocatore* g);
	std::vector<Casella*> ScegliPosizione(int x, char y, std::string direction, int dim);
	void AggiornaGriglia();
	void FindCasella(int x, char y);
	void CreaImpostazioni(bool giocatoreUmano, std::pair<int, int> dimGriglia, int numNavi, std::string nomeAvversario);
	Stato getStato();
	void ToggleState();
	void addNave(NaveSchierata* nave);
	void ResetTurnoSchieramento();
	void StampaGriglia(Giocatore* g);
	void StampaNavi();
	int GetNumeroNavi();
	Giocatore* getGiocatore2();
	bool isG2_Umano();
	Turno* get_TurnoCorrente();
	std::pair<int, int> getDimGriglia();
	bool isOver();
	Turno* getLastValidTurno();
	void setStato(Stato nuovoStato);
	Giocatore* getWinner();
};

#endif