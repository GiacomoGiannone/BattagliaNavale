#include "Partita.hpp"

Partita::Partita(Giocatore _g1, Giocatore _g2)
{
	stato = attiva;

	Griglia* griglia1 = new Griglia();
	Griglia* griglia2 = new Griglia();

	mapGiocatoreGriglie[g1] = griglia1;
	mapGiocatoreGriglie[g2] = griglia2;
}

bool Partita::creaTurno(Giocatore g)
{
	std::cout << "Creo turno" << std::endl;
	t = new TurnoSchieramento(g);
	return true;
}

bool Partita::ScegliPosizione(int x, char y, std::string direction, int dim)
{
	Giocatore giocatoreCorrente = t->getGiocatore();
	
	Griglia* grigliaCorrente = mapGiocatoreGriglie[giocatoreCorrente];
	if (!grigliaCorrente) 
	{
		std::cerr << "Errore: nessuna griglia trovata per il giocatore corrente." << std::endl;
		return false;
	}

	bool esito = grigliaCorrente->ScegliPosizione(x, y, direction, dim);
	return esito;
}