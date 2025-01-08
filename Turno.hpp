#pragma once

#include <iostream>

class Turno
{
private:
public:
	Turno();
	~Turno() {};
	virtual void CreateAttacco(int x, char y) const = 0;
};