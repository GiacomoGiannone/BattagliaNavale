#pragma once

#include <iostream>
#include <vector>

#include "Nave.hpp"

class NaveSchierata
{
private:
	Nave *n;
	std::vector<Casella*> caselle;
public:
	NaveSchierata(Nave* _n, std::vector<Casella*> _caselle) : n(_n), caselle(_caselle) {}
	Nave* getNave() { return n; }
};