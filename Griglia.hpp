#include <iostream>
#include <vector>
#include "Giocatore.hpp"
#include "Casella.hpp"

class Griglia
{
private:
	std::pair<int, int> dim;
	Giocatore g;
	std::vector<std::vector<Casella>> ListaCaselle;
public:
	bool ScegliPosizione(int x, char y, std::string direction, int dim);
	Casella FindCasella(int x, char y);
	void AggiornaGriglia();
};