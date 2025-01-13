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

void BattagliaNavale::IniziaTurnoSchieramento(Giocatore* g, Partita* p)
{
	std::cout << "Inizio turno schieramento" << std::endl;
	p->creaTurno(g);
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
			std::vector<Casella*> caselle = p->ScegliPosizione(x, y, direction, dim);
			if (caselle.empty())
			{
				std::cout << "Posizione non valida!" << std::endl;
				return false;
			}

			NaveSchierata* nave = new NaveSchierata(naveSelezionata, caselle);
			p->addNave(nave);
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
			//ListaPartite.push_back(p);
			p->ResetTurnoSchieramento();
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

void BattagliaNavale::IniziaNuovaPartita(Giocatore* _g1, Giocatore* _g2, Griglia *_griglia_attacchi_1, Griglia *_griglia_attacchi_2, Griglia *_griglia_posizioni_1, Griglia *_griglia_posizioni_2)
{
	std::cout << "Inizia nuova partita" << std::endl;
	Partita* p = new Partita(_g1, _g2, _griglia_attacchi_1, _griglia_attacchi_2, _griglia_posizioni_1, _griglia_posizioni_2);
	ListaPartite.push_back(p);
}

void BattagliaNavale::Scegli_Impostazioni(bool giocatoreUmano, std::pair<int, int> dimGriglia, int numNavi, std::string nomeAvversario)
{
	for (auto& p : ListaPartite)
	{
		if (p->getStato() == Partita::attiva)
		{
			p->CreaImpostazioni(giocatoreUmano, dimGriglia, numNavi, nomeAvversario);
		}
	}
}

void BattagliaNavale::ConfermaImpostazioni()
{
}

Partita* BattagliaNavale::getPartitaCorrente()
{
	for (auto& p : ListaPartite)
	{
		if (p->getStato() == Partita::attiva)
		{
			return p;
		}
	}
	return nullptr;
}