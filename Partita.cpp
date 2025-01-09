#include "Partita.hpp"

Giocatore Partita::getInstanceByNick(std::string nick)
{
	return (g1.getNickname() == nick) ? g1 : g2;
}

Partita::Partita(Giocatore _g1, Giocatore _g2, Griglia _griglia_attacchi_1, Griglia _griglia_attacchi_2, Griglia _griglia_posizioni_1, Griglia _griglia_posizioni_2)
{
	stato = attiva;

	griglia_attacchi_1 = _griglia_attacchi_1;
	griglia_attacchi_2 = _griglia_attacchi_2;
	griglia_posizioni_1 = _griglia_posizioni_1;
	griglia_posizioni_2 = _griglia_posizioni_2;
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
	
	Griglia grigliaCorrente = (griglia_posizioni_1.getGiocatore().getNickname() == giocatoreCorrente.getNickname()) ?  griglia_posizioni_1 : griglia_posizioni_2;
	/*if (!grigliaCorrente)
	{
		std::cerr << "Errore: nessuna griglia trovata per il giocatore corrente." << std::endl;
		return false;
	}*/

	bool esito = grigliaCorrente.ScegliPosizione(x, y, direction, dim);
	return true;
}