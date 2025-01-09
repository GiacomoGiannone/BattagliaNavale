#include <iostream>
#include <vector>
#include "Turno.hpp"
#include "Attacco.hpp"

class TurnoAttacco : public Turno
{
private:
	std::vector<Attacco> Lista_Attacchi;
	Giocatore giocatore;
public:
	TurnoAttacco();
	~TurnoAttacco();

	void CreateAttacco(int x, char y) const
	{
		std::cout << "Creazione attacco alle coordinate: " << x << ", " << y << std::endl;
	}

	Giocatore getGiocatore() const { return giocatore; }
};