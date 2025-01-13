#include <iostream>
#include "Giocatore.hpp"

class GiocatoreUmano : public Giocatore
{
public:
	GiocatoreUmano(std::string _nickname) : Giocatore(_nickname) {};
	~GiocatoreUmano() {};

	std::string getNickname() const { return nickname; }
};