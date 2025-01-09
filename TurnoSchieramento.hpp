#pragma once

#include <iostream>
#include "Turno.hpp"
#include "Giocatore.hpp"

class TurnoSchieramento : public Turno
{
private:
	Giocatore giocatore;
public:
	TurnoSchieramento(Giocatore _giocatore) { giocatore = _giocatore; }
	~TurnoSchieramento() {};

	void CreateAttacco(int x, char y) const override 
	{
		std::cout << "TurnoSchieramento non gestisce attacchi." << std::endl;
	}

	Giocatore getGiocatore() const { return giocatore; }
};