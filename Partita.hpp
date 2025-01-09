#include <iostream>
#include <map>

#include "Giocatore.hpp"
#include "Impostazioni.hpp"
#include "Casella.hpp"
#include "Turno.hpp"
#include "TurnoAttacco.hpp"
#include "Griglia.hpp"
#include "TurnoSchieramento.hpp"

class Partita
{
public :
	enum Stato { attiva, finita };
private:
	Giocatore g1,g2;
	Impostazioni *i;
	std::vector<Turno*> ListaTurni;
	Turno* t;
	std::map<Giocatore, Griglia*> mapGiocatoreGriglie;
	Stato stato;

	Giocatore getInstanceByNick(std::string nick);

public:
	Partita() {};
	Partita(Giocatore _g1, Giocatore _g2);
	bool creaTurno(Giocatore g);
	bool ScegliPosizione(int x, char y, std::string direction, int dim);
	void AggiornaGriglia() {};
	void FindCasella(int x, char y) {};
	bool GeneraEsito(StatoCasella stato);
	void CreaImpostazioni(bool giocatoreUmano, std::pair<int, int> dimGriglia, std::string nomeAvversario) {};
	Stato getStato() { return stato; }
	void ToggleState();
};