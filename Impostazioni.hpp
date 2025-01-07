#include <iostream>

class Impostazioni
{
private:
	int num_giocatori;
	std::pair<int, int> dim_griglia;
	int num_navi;
public:
	Impostazioni(int _num_giocatori, std::pair<int, int> _dim_griglia, int _num_navi);
};