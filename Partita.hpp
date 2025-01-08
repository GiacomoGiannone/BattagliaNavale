#include <iostream>
#include "Giocatore.hpp"
#include "Impostazioni.hpp"
#include "Casella.hpp"
#include "Turno.hpp"
#include "TurnoAttacco.hpp"
#include "Griglia.hpp"

class Partita
{
private:
	Giocatore g1, g2;
	Impostazioni i;
	std::vector<Turno> ListaTurni;
	Turno* t;
	Griglia griglie[4];
public:
	Partita();
	bool creaTurno(Giocatore g) { return true; }
	bool ScegliPosizione(int x, char y, std::string direction, int dim);
	void AggiornaGriglia();
	Casella FindCasella(int x, char y);
	bool GeneraEsito(StatoCasella stato);
	void CreaImpostazioni(bool giocatoreUmano, std::pair<int, int> dimGriglia, std::string nomeAvversario);
};