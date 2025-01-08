#include <iostream>
#include "StatoCasella.hpp"

class Casella
{
private:
	int coordinata_x;
	char coordinata_y;
	StatoCasella stato;
public:
	Casella(int _coordinata_x, char _coordinata_y, StatoCasella _stato);
	void SetNave(NaveSchierata ns);
	void AggiornaGriglia();
	StatoCasella getStato();
};