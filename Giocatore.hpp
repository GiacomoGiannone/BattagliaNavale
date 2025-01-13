#pragma once

#ifndef GIOCATORE_HPP
#define GIOCATORE_HPP

#include <iostream>
#include <vector>

#include "Turno.hpp"

class Giocatore 
{
private:
	std::vector<Turno*> ListaTurni;
protected:
	std::string nickname;
public:
	Giocatore() {};
	Giocatore(std::string _nickname) : nickname(_nickname) {};
	Giocatore(const Giocatore& other) : nickname(other.nickname), ListaTurni(other.ListaTurni) {}
	virtual ~Giocatore() {}

	bool operator<(const Giocatore& other) const
	{
		return nickname < other.nickname; 
	}

	virtual std::string getNickname() const { return nickname; }
};

#endif