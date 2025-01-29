#include "BattagliaNavale.hpp"
#include "Incrociatore.hpp"
#include "Corazzata.hpp"
#include "Portaerei.hpp"
#include "Sottomarino.hpp"


/*BattagliaNavale::BattagliaNavale()
{
	ListaNavi.push_back(std::make_unique<Incrociatore>());
	ListaNavi.push_back(std::make_unique<Corazzata>());
	ListaNavi.push_back(std::make_unique<Portaerei>());
	ListaNavi.push_back(std::make_unique<Sottomarino>());

	naveSelezionata = nullptr;
}*/

/*BattagliaNavale::~BattagliaNavale()
{

}*/

void BattagliaNavale::IniziaTurnoSchieramento(Giocatore* g, Partita* p)
{
	std::cout << "Inizio turno schieramento di " << g->getNickname() << std::endl;
	p->creaTurno(g);
}

bool BattagliaNavale::ScegliNave(int id)
{
	Partita* partita = getPartitaCorrente();
	bool naveScelta = false;
	
	//while (!naveScelta)
	//{
		if (id < 1 || id > 4)
		{
			std::cout << "Nave non valida" << std::endl;
		}

		switch (id)
		{
		case(1):
			//std::cout << "Incrociatore selezionato" << std::endl;
			naveSelezionata = new Incrociatore();
			naveScelta = true;
			break;
		case(2):
			//std::cout << "Corazzata selezionata" << std::endl;
			naveSelezionata = new Corazzata();
			naveScelta = true;
			break;
		case(3):
			//std::cout << "Portaerei selezionata" << std::endl;
			naveSelezionata = new Portaerei();
			naveScelta = true;
			break;
		case(4):
			//std::cout << "Sottomarino selezionato" << std::endl;
			naveSelezionata = new Sottomarino();
			naveScelta = true;
			break;
		}
	//}
	if (naveScelta)
		return true;
	return false;
}

bool BattagliaNavale::ScegliPosizione(int x, char y, std::string direction)
{
	//std::cout << "Metodo scegli posizione BattagliaNavale" << std::endl;
	int dim = naveSelezionata->getDimensione();
	std::cout << "La nave selezionata e' " << naveSelezionata->getNome() << " di dimensione " << dim << std::endl;
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

			for (auto& casella : caselle)
			{
				casella->setStato(StatoCasella::occupata);
			}

			NaveSchierata* nave = new NaveSchierata(naveSelezionata, caselle);
			p->addNave(nave);
			p->StampaNavi();
			return true;
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

void BattagliaNavale::IniziaNuovaPartita(Giocatore* _g1)
{
	std::cout << "Inizia nuova partita" << std::endl;
	Partita* p = new Partita(_g1/*, _g2, _griglia_attacchi_1, _griglia_attacchi_2, _griglia_posizioni_1, _griglia_posizioni_2*/);
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

void BattagliaNavale::setNaveSelezionata(Nave* nave)
{
	naveSelezionata = nave;
}

std::unordered_map<std::string, int> BattagliaNavale::CreaMappaNavi()
{
	// Crea una mappa per associare ogni tipo di nave al numero di navi schierabili
	std::unordered_map<std::string, int> mappaNavi;

	// Itera su tutte le navi nella lista e aggiungi il nome con il numero massimo schierabile
	for (const auto& nave : ListaNavi)
	{
		std::string nomeNave = nave->getNome();
		Partita* partita = getPartitaCorrente();
		int maxNumNavi = partita->GetNumeroNavi();

		// Inserisci nella mappa
		if (nomeNave == "Sottomarino")
		{
			mappaNavi[nomeNave] = maxNumNavi-3;
		}
		else
		{
			mappaNavi[nomeNave] = 1;
		}
	}
	return mappaNavi;
}

Nave* BattagliaNavale::getNave()
{
	return naveSelezionata;
}

void BattagliaNavale::GestisciFinePartita()
{
	for (auto& p : ListaPartite)
	{
		if (p->getStato() == Partita::attiva)
		{
			p->setStato(Partita::finita);
		}
	}
}

BattagliaNavale* BattagliaNavale::instance = nullptr;