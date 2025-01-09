#include "BattagliaNavale.hpp"
#include "Incrociatore.hpp"
#include "Corazzata.hpp"
#include "Portaerei.hpp"
#include "Sottomarino.hpp"

BattagliaNavale::BattagliaNavale()
{
	ListaNavi.push_back(std::make_unique<Incrociatore>());
	ListaNavi.push_back(std::make_unique<Corazzata>());
	ListaNavi.push_back(std::make_unique<Portaerei>());
	ListaNavi.push_back(std::make_unique<Sottomarino>());

	naveSelezionata = nullptr;
}

BattagliaNavale::~BattagliaNavale()
{

}

void BattagliaNavale::IniziaTurnoSchieramento(Giocatore g, Partita p)
{
	std::cout << "Inizio turno schieramento" << std::endl;
	p.creaTurno(g);
}

bool BattagliaNavale::ScegliNave()
{
	std::cout << "Scegli quale nave piazzare:" << std::endl;
	int count = 1;
	int id = 1;
	for (const auto& n : ListaNavi)
	{
		std::cout << n->getNome() << " (" << count << ")" << std::endl;
		count++;
	}

	std::cin >> id;
	if (id < 1 || id > 4)
	{
		std::cout << "Nave non valida" << std::endl;
		return false;
	}

	switch (id)
	{
	case(1):
		std::cout << "Incrociatore selezionato" << std::endl;
		naveSelezionata = new Incrociatore();
		break;
	case(2):
		std::cout << "Corazzata selezionata" << std::endl;
		naveSelezionata = new Corazzata();
		break;
	case(3):
		std::cout << "Portaerei selezionata" << std::endl;
		naveSelezionata = new Portaerei();
		break;
	case(4):
		std::cout << "Sottomarino selezionato" << std::endl;
		naveSelezionata = new Sottomarino();
		break;
	}
	return true;
}

bool BattagliaNavale::ScegliPosizione(int x, char y, std::string direction)
{
	std::cout << "Scegli posizione" << std::endl;
	int dim = naveSelezionata->getDimensione();
	for (auto& p : ListaPartite)
	{
		if (p->getStato() == Partita::attiva)
		{
			return p->ScegliPosizione(x, y, direction, dim);
		}
	}
	return false;
}

bool BattagliaNavale::ConfermaPiazzamentoNavi()
{
	std::cout << "Conferma piazzamento navi" << std::endl;
	for (auto& p : ListaPartite)
	{
		if (p->getStato() == Partita::attiva)
		{
			ListaPartite.push_back(p);
			return true;
		}
	}
	return false;
}

void BattagliaNavale::ScegliPosizioneAttacco(int x, char y)
{
	for (auto& p : ListaPartite)
	{
		if (p->getStato() == Partita::attiva)
		{
			p->FindCasella(x, y);
		}
	}
}

void BattagliaNavale::AggiornaGriglia()
{
	for (auto& p : ListaPartite)
	{
		if (p->getStato() == Partita::attiva)
		{
			p->AggiornaGriglia();
		}
	}
}

void BattagliaNavale::IniziaNuovaPartita()
{
	std::cout << "Inizia nuova partita" << std::endl;
	Partita* p = new Partita();
	ListaPartite.push_back(p);
}

void BattagliaNavale::Scegli_Impostazioni(bool giocatoreUmano, std::pair<int, int> dimGriglia, std::string nomeAvversario)
{
	for (auto& p : ListaPartite)
	{
		if (p->getStato() == Partita::attiva)
		{
			p->CreaImpostazioni(giocatoreUmano, dimGriglia, nomeAvversario);
		}
	}
}

void BattagliaNavale::ConfermaImpostazioni()
{
}
