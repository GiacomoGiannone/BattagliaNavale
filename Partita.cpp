#include "Partita.hpp"
#include "TurnoSchieramento.hpp"
#include "TurnoAttacco.hpp"
#include "GiocatoreUmano.hpp"
#include "Bot.hpp"

Giocatore* Partita::getInstanceByNick(std::string nick)
{
	return (g1->getNickname() == nick) ? g1 : g2;
}

Partita::Partita(Giocatore* _g1/* Giocatore* _g2, Griglia* _griglia_attacchi_1, Griglia* _griglia_attacchi_2, Griglia* _griglia_posizioni_1, Griglia* _griglia_posizioni_2*/)
{
	stato = attiva;

	/*griglia_attacchi_1 = _griglia_attacchi_1;
	griglia_attacchi_2 = _griglia_attacchi_2;
	griglia_posizioni_1 = _griglia_posizioni_1;
	griglia_posizioni_2 = _griglia_posizioni_2;*/

	g1 = _g1;
	//g2 = _g2;
}

bool Partita::creaTurno(Giocatore* g)
{
	if(!g)
	{
		std::cerr << "Errore: giocatore non inizializzato" << std::endl;
		return false;
	}
	std::string nickGiocatore = g->getNickname();
	std::cout << "Creo turno di schieramento del giocatore "<< nickGiocatore << std::endl;
	t = new TurnoSchieramento(nickGiocatore);
	//alla fine del turno di schieramento di g, fai delete t in modo da poter creare un nuovo turno per g2
	return true;
}

std::vector<Casella*> Partita::ScegliPosizione(int x, char y, std::string direction, int dim)
{
	std::cout << "Metodo scegli posizione di Partita" << std::endl;
	std::string nickGiocatore = t->getNickGiocatore();
	Giocatore *giocatoreCorrente = getInstanceByNick(nickGiocatore);
	
	Griglia* grigliaCorrente = (griglia_posizioni_1->getGiocatore()->getNickname() == giocatoreCorrente->getNickname()) ?  griglia_posizioni_1 : griglia_posizioni_2;
	/*if (!grigliaCorrente)
	{
		std::cerr << "Errore: nessuna griglia trovata per il giocatore corrente." << std::endl;
		return false;
	}*/

	return grigliaCorrente->ScegliPosizione(x, y, direction, dim);
}

void Partita::ToggleState()
{
	stato = (stato == attiva) ? finita : attiva;
}

void Partita::addNave(NaveSchierata* nave)
{
	navi.push_back(nave);
}

void Partita::ResetTurnoSchieramento()
{
	std::cout << "Resetto il turno di schieramento di" << t->getNickGiocatore() << std::endl;
	ListaTurni.push_back(t);
	delete t;
}

void Partita::FindCasella(int x, char y)
{
	//accedi all'ultimo turno per capire chi è il giocatore corrente
	std::string lastPlayer = ListaTurni.back()->getNickGiocatore();
	Giocatore* gTemp; //gTemp è il giocatore che deve attaccare
	if (g1->getNickname() == lastPlayer)
	{
		gTemp = new Giocatore(*g2);
	}
	else
	{
		gTemp = new Giocatore(*g1);
	}
	t = new TurnoAttacco(gTemp->getNickname());
	//accedi alla griglia di attacco del giocatore corrente
	Griglia* grigliaCorrente = (griglia_posizioni_1->getGiocatore()->getNickname() == gTemp->getNickname()) ? griglia_posizioni_1 : griglia_posizioni_2;
	//cerca la casella x,y
	Casella* casella = grigliaCorrente->FindCasella(x, y);

	if (casella)
	{
		// Ottieni lo stato della casella
		StatoCasella stato = casella->getStato();

		//std::cout << "Lo stato della casella (" << x << ", " << y << ") è: " << stato << std::endl;

		if (stato == StatoCasella::acqua)
		{
			std::cout << "Casella acqua!" << std::endl;
		}
		else if (stato == StatoCasella::occupata)
		{
			std::cout << "Casella occupata!" << std::endl;
		}
	}
	else
	{
		std::cout << "Casella non trovata!" << std::endl;
	}

	bool esito = GeneraEsito(casella->getStato());
	t->CreateAttacco(x, y, grigliaCorrente, esito);
	//conferma il turno di attacco e cancella il turno corrente
	ListaTurni.push_back(t);
	delete t;
}

bool Partita::GeneraEsito(StatoCasella stato)
{
	if (stato == StatoCasella::acqua)
	{
		std::cout << "Acqua!" << std::endl;
		return false;
	}
	else if (stato == StatoCasella::occupata)
	{
		std::cout << "Colpito!" << std::endl;
		return true;
	}
	else
	{
		std::cout << "Errore!" << std::endl;
		return false;
	}
}

Partita::Stato Partita::getStato()
{
	return stato;
}

void Partita::AggiornaGriglia()
{
	/*std::string lastPlayer = ListaTurni.back()->getNickGiocatore();
	Giocatore* gTemp; //gTemp è il giocatore che deve attaccare
	if (g1.getNickname() == lastPlayer)
	{
		gTemp = new Giocatore(g2);
	}
	else
	{
		gTemp = new Giocatore(g1);
	}
	Griglia grigliaCorrente = (griglia_posizioni_1.getGiocatore().getNickname() == gTemp->getNickname()) ? griglia_posizioni_1 : griglia_posizioni_2;
	grigliaCorrente.AggiornaGriglia();*/
}

void Partita::CreaImpostazioni(bool giocatoreUmano, std::pair<int, int> dimGriglia,int numNavi,  std::string nomeAvversario)
{
	i = new Impostazioni(giocatoreUmano, dimGriglia, numNavi);
	if (giocatoreUmano)
	{
		g2 = new GiocatoreUmano(nomeAvversario);
	}
	else
	{
		g2 = new Bot(nomeAvversario);
	}

	griglia_attacchi_1 = new Griglia(dimGriglia, g1);
	griglia_attacchi_2 = new Griglia(dimGriglia, g2);
	griglia_posizioni_1 = new Griglia(dimGriglia, g1);
	griglia_posizioni_2 = new Griglia(dimGriglia, g2);

	//griglia_posizioni_1->StampaGriglia();

	std::cout << "Impostazioni della partita completate. Griglie inizializzate." << std::endl;
}

void Partita::StampaGriglia(Giocatore* g)
{
	if (g->getNickname() == g1->getNickname())
	{
		griglia_posizioni_1->StampaGriglia();
	}
	else
	{
		griglia_posizioni_2->StampaGriglia();
	}
}

void Partita::StampaNavi()
{
	for (auto& naveSchierata : navi)
	{
		naveSchierata->PrintInfo();
	}
}

int Partita::GetNumeroNavi()
{
	return i->getNumNavi();
}

Giocatore* Partita::getGiocatore2()
{
	return g2;
}

bool Partita::isG2_Umano()
{
	return i->getGiocatoreUmano();
}

Turno* Partita::get_TurnoCorrente()
{
	return t;
}

std::pair<int, int> Partita::getDimGriglia()
{
	return i->getDimGriglia();
}