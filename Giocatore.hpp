#pragma once

#ifndef GIOCATORE_HPP
#define GIOCATORE_HPP

#include <iostream>
#include <vector>

#include "Turno.hpp"

class Giocatore 
{
private:
	std::string nickname;
	std::vector<Turno*> ListaTurni;
public:
	Giocatore() {};
	Giocatore(std::string _nickname) {};

	bool operator<(const Giocatore& other) const
	{
		return nickname < other.nickname; 
	}

	std::string getNickname() const { return nickname; }
};

#endif