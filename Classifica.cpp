#include "Classifica.hpp"

#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <vector>

void Classifica::AggiornaClassifica(const std::string& classificaFile, const std::string& nickname)
{
    std::ofstream file(classificaFile, std::ios::app);
    if (file.is_open()) {
        file << nickname << " 0\n";
    }
}

void Classifica::AggiornaPunteggio(const std::string& classificaFile, const std::string& nickname, int incremento)
{
    std::ifstream file(classificaFile);
    std::ofstream tempFile("temp.txt");
    if (!file.is_open() || !tempFile.is_open()) {
        std::cerr << "Errore nell'aprire il file della classifica." << std::endl;
        return;
    }
    std::unordered_map<std::string, int> classifica;
    std::string storedNickname;
    int punteggio;
    // Leggi tutti i dati della classifica esistente
    while (file >> storedNickname >> punteggio) {
        classifica[storedNickname] = punteggio;
    }
    // Aggiungi o aggiorna il punteggio del nickname
    classifica[nickname] += incremento;
    // Crea un vettore di coppie (nickname, punteggio)
    std::vector<std::pair<std::string, int> > classificaOrdinata;
    for (const auto& entry : classifica) {
        classificaOrdinata.push_back(entry);
    }
    // Ordina il vettore in ordine decrescente di punteggio
    std::sort(classificaOrdinata.begin(), classificaOrdinata.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second; // Ordina per punteggio decrescente
        });
    // Riscrivi la classifica nel file in ordine decrescente
    for (const auto& entry : classificaOrdinata) {
        tempFile << entry.first << " " << entry.second << "\n";
    }
    file.close();
    tempFile.close();
    // Sostituisci il file della classifica con il file temporaneo
    std::remove(classificaFile.c_str());
    std::rename("temp.txt", classificaFile.c_str());
}

void Classifica::VisualizzaClassifica(const std::string& classificaFile)
{
    std::ifstream file(classificaFile);
    if (!file.is_open()) {
        std::cerr << "Errore nell'aprire il file della classifica." << std::endl;
        return;
    }

    std::cout << "Classifica:\n";
    std::string nickname;
    int punteggio;
    while (file >> nickname >> punteggio) {
        std::cout << nickname << ": " << punteggio << std::endl;
    }
}