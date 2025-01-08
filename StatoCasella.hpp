#pragma once

#include <iostream>

class StatoCasella
{
public:
	enum Stato { acqua, occupata };
private:
	Stato stato;
public:
	StatoCasella();
	~StatoCasella() {};
};