#pragma once

#ifndef AUTENTICAZIONE_HPP
#define AUTENTICAZIONE_HPP

#include <iostream>
#include "Classifica.hpp"

class Autenticazione
{
private:
	Classifica classifica;
	static Autenticazione* instance;
	Autenticazione()
	{

	}

	~Autenticazione() = default;
public:
	Autenticazione(const Autenticazione&) = delete;
	Autenticazione& operator=(const Autenticazione&) = delete;

	static Autenticazione* getInstance()
	{
		if (!instance)
		{
			instance = new Autenticazione();
		}
		return instance;
	}

	bool VerificaCredenziali(const std::string& filename, const std::string& nickname, const std::string& password);
	bool NicknameEsiste(const std::string& filename, const std::string& nickname);
	void RegistraNuovoUtente(const std::string& utentiFile, const std::string& classificaFile, const std::string& nickname, const std::string& password);
	std::string GestisciAutenticazione(const std::string& utentiFile, const std::string& classificaFile);
};

#endif