#pragma once

#include <iostream>

class Attacco
{
private:
	int coordinata_x;
	char coordinata_y;
	bool esito;
public:
	Attacco(int _coordinata_x, char _coordinata_y, bool _esito) :coordinata_x(_coordinata_x), coordinata_y(_coordinata_y),esito(_esito)  {}
	int getCoordinataX();
	char getCoordinataY();
};