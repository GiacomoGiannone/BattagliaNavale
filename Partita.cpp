#include "Partita.hpp"

Giocatore Partita::getInstanceByNick(std::string nick)
{
	return (g1.getNickname() == nick) ? g1 : g2;
}

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
	std::cout << "Creo turno di schieramento del giocatore "<< g.getNickname() << std::endl;
	std::string nickGiocatore = g.getNickname();
	t = new TurnoSchieramento(nickGiocatore);
	//alla fine del turno di schieramento di g, fai delete t in modo da poter creare un nuovo turno per g2
	return true;
}

bool Partita::ScegliPosizione(int x, char y, std::string direction, int dim)
{
	std::string nickGiocatore = t->getNickGiocatore();
	Giocatore giocatoreCorrente = getInstanceByNick(nickGiocatore);
	
	Griglia* grigliaCorrente = mapGiocatoreGriglie[giocatoreCorrente];
	if (!grigliaCorrente) 
	{
		std::cerr << "Errore: nessuna griglia trovata per il giocatore corrente." << std::endl;
		return false;
	}

	bool esito = grigliaCorrente->ScegliPosizione(x, y, direction, dim);
	return true;
}