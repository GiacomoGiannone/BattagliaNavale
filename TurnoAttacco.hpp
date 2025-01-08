#include <iostream>
#include <vector>
#include "Turno.hpp"
#include "Attacco.hpp"

class TurnoAttacco : public Turno
{
private:
	std::vector<Attacco> Lista_Attacchi;
public:
	TurnoAttacco();
	~TurnoAttacco();

	void CreateAttacco(int x, char y);
};