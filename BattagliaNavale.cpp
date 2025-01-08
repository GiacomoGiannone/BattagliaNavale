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
}

BattagliaNavale::~BattagliaNavale()
{

}

void BattagliaNavale::IniziaTurnoSchieramento(Giocatore g, Partita p)
{
	std::cout << "Inizio turno schieramento" << std::endl;
	p.creaTurno(g);
}

bool BattagliaNavale::ScegliNave(int idNave)
{
	std::cout << "Scegli nave" << std::endl;
	for (const auto& n : ListaNavi)
	{
		std::cout << n->getNome() << std::endl;
	}
	return true;
}
