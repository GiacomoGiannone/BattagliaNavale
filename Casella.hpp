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

	void SetColor(int color);
public:
	Casella() : coordinata_x(0), coordinata_y('A'), stato(StatoCasella::acqua) {}
	Casella(int _coordinata_x, char _coordinata_y, StatoCasella _stato):coordinata_x(_coordinata_x), coordinata_y(_coordinata_y), stato(_stato){}
	void AggiornaGriglia() {};
	StatoCasella getStato() { return stato; }
	void setStato(StatoCasella nuovoStato) { stato = nuovoStato; }
	const int getCoordinataX() { return coordinata_x; }
	const char getCoordinataY() { return coordinata_y; }
	
	friend std::ostream& operator<<(std::ostream& os, const Casella& casella);
	friend bool operator==(const Casella& lhs, const Casella& rhs);
};

#endif