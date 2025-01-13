#include <iostream>
#include "Giocatore.hpp"

class Bot: public Giocatore
{
public:
	Bot(std::string _nickname) : Giocatore(_nickname) {};
	~Bot() {};

	std::string getNickname() const { return nickname; }
};