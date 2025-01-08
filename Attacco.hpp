#pragma once

#include <iostream>

class Attacco
{
private:
	int coordinata_x;
	char coordinata_y;
public:
	Attacco(int _coordinata_x, char _coordinata_y);
	int getCoordinataX();
	char getCoordinataY();
};