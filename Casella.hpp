#pragma once

#ifndef CASELLA_HPP
#define CASELLA_HPP

#include <iostream>
#include "StatoCasella.hpp"

class Casella
{
private:
	int coordinata_x;
	char coordinata_y;
	StatoCasella stato;
public:
	Casella(int _coordinata_x, char _coordinata_y, StatoCasella _stato):coordinata_x(_coordinata_x), coordinata_y(_coordinata_y), stato(_stato){}
	//void SetNave(NaveSchierata ns);
	void AggiornaGriglia() {};
	StatoCasella getStato() { return stato; }
	const int getCoordinataX() { return coordinata_x; }
	const char getCoordinataY() { return coordinata_y; }
};

#endif