#pragma once

#ifndef CLASSIFICA_HPP
#define CLASSIFICA_HPP

#include <iostream>

class Classifica
{
private:
public:
	void AggiornaClassifica(const std::string& classificaFile, const std::string& nickname);
	void AggiornaPunteggio(const std::string& classificaFile, const std::string& nickname, int incremento);
	void VisualizzaClassifica(const std::string& classificaFile);
};

#endif