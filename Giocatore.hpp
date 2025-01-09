#pragma once

#include <iostream>
#include "Turno.hpp"
#include <vector>

class Giocatore 
{
private:
	std::string nickname;
	std::vector<Turno*> ListaTurni;
public:
	Giocatore() {};
	Giocatore(std::string _nickname) {};
};