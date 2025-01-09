#include <iostream>
#include "Giocatore.hpp"
#include "Impostazioni.hpp"
#include "Casella.hpp"
#include "Turno.hpp"
#include "TurnoAttacco.hpp"
#include "Griglia.hpp"

class Partita
{
public :
	enum Stato { attiva, finita };
private:
	Giocatore g1,g2;
	Impostazioni *i;
	std::vector<Turno*> ListaTurni;
	Turno* t;
	Griglia griglie[4];
	Stato stato;
public:
	Partita() { stato = attiva; };
	bool creaTurno(Giocatore g) { return true; }
	bool ScegliPosizione(int x, char y, std::string direction, int dim) {};
	void AggiornaGriglia() {};
	void FindCasella(int x, char y) {};
	bool GeneraEsito(StatoCasella stato);
	void CreaImpostazioni(bool giocatoreUmano, std::pair<int, int> dimGriglia, std::string nomeAvversario) {};
	Stato getStato() { return stato; }
	void ToggleState();
};