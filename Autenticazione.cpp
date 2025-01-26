#include "Autenticazione.hpp"
#include <fstream>

bool Autenticazione::VerificaCredenziali(const std::string& filename, const std::string& nickname, const std::string& password)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string storedNickname, storedPassword;
    while (file >> storedNickname >> storedPassword) {
        if (storedNickname == nickname && storedPassword == password) {
            return true;
        }
    }
    return false;
}

bool Autenticazione::NicknameEsiste(const std::string& filename, const std::string& nickname)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string storedNickname, storedPassword;
    while (file >> storedNickname >> storedPassword) {
        if (storedNickname == nickname) {
            return true;
        }
    }
    return false;
}

void Autenticazione::RegistraNuovoUtente(const std::string& utentiFile, const std::string& classificaFile, const std::string& nickname, const std::string& password)
{
    std::ofstream utenti(utentiFile, std::ios::app);
    if (utenti.is_open()) {
        utenti << nickname << " " << password << "\n";
    }
    classifica.AggiornaClassifica(classificaFile, nickname);
}

std::string Autenticazione::GestisciAutenticazione(const std::string& utentiFile, const std::string& classificaFile)
{
    std::string nickname, password;

    while (true) {
        std::cout << "Inserisci il tuo nickname: ";
        std::cin >> nickname;

        if (NicknameEsiste(utentiFile, nickname)) {
            std::cout << "Una vecchia conoscenza! Inserisci la password: ";
            std::cin >> password;
            //ClearConsole();

            if (VerificaCredenziali(utentiFile, nickname, password)) {
                std::cout << "Accesso effettuato con successo!" << std::endl;
                return nickname;
            }
            else {
                std::cout << "Password errata. Riprova." << std::endl;
            }
        }
        else {
            std::cout << "Oh, un nuovo utente, piacere! Inserisci una password per registrarti: ";
            std::cin >> password;
            RegistraNuovoUtente(utentiFile, classificaFile, nickname, password);
            std::cout << "Registrazione completata con successo!" << std::endl;
            return nickname;
        }
    }
}

Autenticazione* Autenticazione::instance = nullptr;