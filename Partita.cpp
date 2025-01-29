#include "Partita.hpp"
#include "TurnoSchieramento.hpp"
#include "TurnoAttacco.hpp"
#include "GiocatoreUmano.hpp"
#include "Bot.hpp"

Giocatore* Partita::getInstanceByNick(std::string nick)
{
	return (g1->getNickname() == nick) ? g1 : g2;
}

Partita::Partita(Giocatore* _g1)
{
	stato = attiva;
	g1 = _g1;
}

bool Partita::creaTurno(Giocatore* g)
{
	if(!g)
	{
		std::cerr << "Errore: giocatore non inizializzato" << std::endl;
		return false;
	}
	std::string nickGiocatore = g->getNickname();
	//std::cout << "Creo turno di schieramento del giocatore "<< nickGiocatore << std::endl;
	t = new TurnoSchieramento(nickGiocatore);
	//alla fine del turno di schieramento di g, fai delete t in modo da poter creare un nuovo turno per g2
	return true;
}

std::vector<Casella*> Partita::ScegliPosizione(int x, char y, std::string direction, int dim)
{
	//std::cout << "Metodo scegli posizione di Partita" << std::endl;
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
	if (t) // Assicurati che t non sia nullptr
	{
		//std::cout << "Resetto il turno di schieramento di " << t->getNickGiocatore() << std::endl;

		// Aggiungi il turno a ListaTurni come std::shared_ptr
		ListaTurniSchieramento.push_back(std::shared_ptr<Turno>(t));

		// Imposta t a nullptr per evitare dangling pointer
		t = nullptr;
	}
	else
	{
		std::cout << "Errore: il turno corrente � gi� nullo!" << std::endl;
	}
}

void Partita::FindCasella(int x, char y)
{
	std::string lastPlayer;
	if (ListaTurniAttacco.empty())
	{
		lastPlayer = ListaTurniSchieramento.back()->getNickGiocatore();
	}
	else
	{
		lastPlayer = ListaTurniAttacco.back()->getNickGiocatore();
	}
	Giocatore* gTemp = (g1->getNickname() == lastPlayer) ? g2 : g1;

	TurnoAttacco turnoAttacco(gTemp->getNickname());
	//std::cout << "Turno di attacco del giocatore " << turnoAttacco.getNickGiocatore() << std::endl;

	//grigliaCorrente e' la griglia che viene attaccata
	Griglia* grigliaCorrente = (griglia_posizioni_1->getGiocatore()->getNickname() == gTemp->getNickname())? griglia_posizioni_2: griglia_posizioni_1;

	if (!grigliaCorrente)
	{
		std::cerr << "La griglia corrente non � valida" << std::endl;
		return;
	}

	Casella* casella = grigliaCorrente->FindCasella(x, y);

	if (!casella)
	{
		std::cout << "Casella non trovata!" << std::endl;
		return;
	}

	StatoCasella stato = casella->getStato();

	bool esito = GeneraEsito(stato);

	if (stato == StatoCasella::acqua)
	{
		std::cout << "Acqua!" << std::endl;
	}
	else if (stato == StatoCasella::occupata)
	{
		std::cout << "Colpito!" << std::endl;
		casella->setStato(StatoCasella::colpita);
	}
	else if (stato == StatoCasella::colpita)
	{
		std::cout << "Hai gi� colpito questa casella!" << std::endl;
	}

	turnoAttacco.CreateAttacco(x, y, grigliaCorrente, esito);

	ListaTurniAttacco.push_back(std::make_shared<TurnoAttacco>(turnoAttacco));
}

bool Partita::GeneraEsito(StatoCasella stato)
{
	if (stato == StatoCasella::acqua)
	{
		return false;
	}
	else if (stato == StatoCasella::occupata)
	{
		return true;
	}
	
	return false;
}

Partita::Stato Partita::getStato()
{
	return stato;
}

void Partita::AggiornaGriglia()
{
	/*std::string lastPlayer = ListaTurni.back()->getNickGiocatore();
	Giocatore* gTemp; //gTemp � il giocatore che deve attaccare
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
	this->giocatoreUmano = giocatoreUmano;
	this->dimGriglia = dimGriglia;
	this->numNavi = numNavi;
	this->nomeAvversario = nomeAvversario;

	//i = new Impostazioni(giocatoreUmano, dimGriglia, numNavi);
	if (giocatoreUmano)
	{
		g2 = new GiocatoreUmano(nomeAvversario);
	}
	else
	{
		g2 = new Bot(nomeAvversario);
	}

	/*griglia_attacchi_1 = new Griglia(dimGriglia, g1);
	griglia_attacchi_2 = new Griglia(dimGriglia, g2);*/
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
	return this->numNavi;
}

Giocatore* Partita::getGiocatore2()
{
	return g2;
}

bool Partita::isG2_Umano()
{
	return this->giocatoreUmano;
}

Turno* Partita::get_TurnoCorrente()
{
	return t;
}

std::pair<int, int> Partita::getDimGriglia()
{
	return this->dimGriglia;
}

bool Partita::isOver()
{
	return griglia_posizioni_1->isOver() || griglia_posizioni_2->isOver();
}

Turno* Partita::getLastValidTurnoSchieramento()
{
	if (ListaTurniSchieramento.empty())
	{
		//std::cerr << "Nessun turno schieramento trovato. Restituisco nullptr." << std::endl;
		return nullptr;
	}
	return ListaTurniSchieramento.back().get();
}

Turno* Partita::getLastValidTurnoAttacco()
{
	if (ListaTurniAttacco.empty())
	{
		//std::cerr << "Nessun turno attacco trovato. Restituisco nullptr." << std::endl;
		return nullptr;
	}
	return ListaTurniAttacco.back().get();
}

void Partita::setStato(Stato nuovoStato)
{
	this->stato = nuovoStato;
}

Giocatore* Partita::getWinner()
{
	if (griglia_posizioni_1->isOver())
	{
		return g2;
	}
	
	return g1;
}

Griglia* Partita::getGriglia(Giocatore* g)
{
	return griglia_posizioni_1->getGiocatore()->getNickname() == g->getNickname() ? griglia_posizioni_1 : griglia_posizioni_2;
}