#include <iostream>
#include "Giocatore.hpp"

class Bot: public Giocatore
{
private:
	std::string nickname;
public:
	Bot(std::string _nickname) : nickname(_nickname) {};
	~Bot() {};
};