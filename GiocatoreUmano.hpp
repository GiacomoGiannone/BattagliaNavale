#include <iostream>
#include "Giocatore.hpp"

class GiocatoreUmano : public Giocatore
{
private:
	std::string nickname;
public:
	GiocatoreUmano(std::string _nickname) : nickname(_nickname) {};
	~GiocatoreUmano() {};
};