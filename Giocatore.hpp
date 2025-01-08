#include <iostream>
#include "Turno.hpp"

class Giocatore 
{
private:
	std::string nickname;
	std::vector<Turno> ListaTurni;
public:
	Giocatore(std::string _nickname);
};