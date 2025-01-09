#include "Griglia.hpp"

Griglia::Griglia(std::pair<int, int> _dim, Giocatore _g)
{
	dim = _dim;
	g = _g;
}

bool Griglia::ScegliPosizione(int x, char y, std::string direction, int dim)
{
	//controlla se la nave puo' essere piazzata
	//controlla se la nave non è adiacente ad altre navi
	std::vector<Casella*> caselleScelte;
	for (int i = 0; i < dim; i++)
	{

	}
	return true;
}
