#ifndef TEST_MODE

#include <iostream>
#include <time.h>

#include <cstdlib> 
#include <thread>
#include <chrono>

#include <fstream>
#include <string>
#include <unordered_map>

#include "BattagliaNavale.hpp"
#include "GiocatoreUmano.hpp"

void ClearConsole()
{
#ifdef _WIN32
    system("cls"); //Windows
#else
    system("clear"); //Unix/Linux/macOS
#endif
}

bool VerificaCredenziali(const std::string& filename, const std::string& nickname, const std::string& password) {
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

bool NicknameEsiste(const std::string& filename, const std::string& nickname) {
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

void AggiornaClassifica(const std::string& classificaFile, const std::string& nickname) {
    std::ofstream file(classificaFile, std::ios::app);
    if (file.is_open()) {
        file << nickname << " 0\n";
    }
}

void RegistraNuovoUtente(const std::string& utentiFile, const std::string& classificaFile, const std::string& nickname, const std::string& password) {
    std::ofstream utenti(utentiFile, std::ios::app);
    if (utenti.is_open()) {
        utenti << nickname << " " << password << "\n";
    }
    AggiornaClassifica(classificaFile, nickname);
}

std::string GestisciAutenticazione(const std::string& utentiFile, const std::string& classificaFile) {
    std::string nickname, password;

    while (true) {
        std::cout << "Inserisci il tuo nickname: ";
        std::cin >> nickname;

        if (NicknameEsiste(utentiFile, nickname)) {
            std::cout << "Una vecchia conoscenza! Inserisci la password: ";
            std::cin >> password;
            ClearConsole();

            if (VerificaCredenziali(utentiFile, nickname, password)) {
                std::cout << "Accesso effettuato con successo!" << std::endl;
                return nickname;
            } else {
                std::cout << "Password errata. Riprova." << std::endl;
            }
        } else {
            std::cout << "Oh, un nuovo utente, piacere! Inserisci una password per registrarti: ";
            std::cin >> password;
            RegistraNuovoUtente(utentiFile, classificaFile, nickname, password);
            std::cout << "Registrazione completata con successo!" << std::endl;
            return nickname;
        }
    }
}

void AggiornaPunteggio(const std::string& classificaFile, const std::string& nickname, int incremento) {
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
    std::vector<std::pair<std::string, int>> classificaOrdinata;
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

void VisualizzaClassifica(const std::string& classificaFile) {
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


int main()
{
    srand(time(0));
    BattagliaNavale* gioco = BattagliaNavale::getInstance();
    const std::string utentiFile = "utenti.txt";
    const std::string classificaFile = "classifica.txt";

    
    std::cout << "Benvenuto in Battaglia Navale!" << std::endl;
    std::string MainPlayerNickname = GestisciAutenticazione(utentiFile, classificaFile);
    std::cout << "Benvenuto, " << MainPlayerNickname << "!" << std::endl;
   
    // Menu dopo il login
    bool userChoice = true;
    while (userChoice) {
        std::cout << "\nMENU:\n";
        std::cout << "1. Gioca\n";
        std::cout << "2. Visualizza classifica\n";
        std::cout << "3. Esci\n";
        std::cout << "Scegli cosa fare: ";
        int scelta;
        std::cin >> scelta;
        std::cout << "\n";

        switch (scelta) {
            case 1:
                {
                    bool gameIsRunning = true;
                    while (gameIsRunning)
                     {
                         // Codice per giocare
                         Giocatore* mainPlayer = new GiocatoreUmano(MainPlayerNickname);

                        gioco->IniziaNuovaPartita(mainPlayer);

                        std::this_thread::sleep_for(std::chrono::seconds(3));
                        ClearConsole();

                        std::cout << "Il secondo giocatore e' un bot? (Y/N): ";
                        char isBot;
                        std::cin >> isBot;
                        std::string SecondPlayerNickname;
                        if (isBot == 'Y' || isBot == 'y') {
                            std::cout << "Inserisci il nickname del bot avversario: ";
                            std::cin >> SecondPlayerNickname;
                        } else {
                            while (true) {
                                std::cout << "Inserisci il nickname del tuo avversario: ";
                                std::cin >> SecondPlayerNickname;
                                if (SecondPlayerNickname == MainPlayerNickname) {
                                    std::cout << "Il nickname del secondo giocatore non puo' essere uguale a quello del primo. Riprova." << std::endl;
                                    continue;
                                }
                                if (NicknameEsiste(utentiFile, SecondPlayerNickname)) {
                                    std::string password;
                                    std::cout << "Bentornato anche tu, " << SecondPlayerNickname << "! Inserisci la password: ";
                                    std::cin >> password;

                                    if (VerificaCredenziali(utentiFile, SecondPlayerNickname, password)) {
                                        std::cout << "Accesso effettuato con successo!" << std::endl;
                                        break;
                                    } else {
                                        std::cout << "Password errata. Riprova." << std::endl;
                                    }
                                } else {
                                    std::string password;
                                    std::cout << "Oh, un nuovo avversario! Inserisci una password per registrarti: ";
                                    std::cin >> password;
                                    RegistraNuovoUtente(utentiFile, classificaFile, SecondPlayerNickname, password);
                                    std::cout << "Registrazione completata con successo!" << std::endl;
                                    break;
                                }
                            }
                        }

                        std::this_thread::sleep_for(std::chrono::seconds(3));
                        ClearConsole();

                        std::cout << "Scelta delle impostazioni" << std::endl;
                        int numNavi;
                        int dimGriglia;
                        std::cout << "Inserisci con quante navi giocare: ";
                        std::cin >> numNavi;
                        std::cout << std::endl;
                        std::cout << "Inserire la dimensione della griglia (solo una dimensione): ";
                        std::cin >> dimGriglia;
                        std::cout << std::endl;

                        if (isBot == 'Y' || isBot == 'y')
                        {
                            gioco->Scegli_Impostazioni(false, std::make_pair(dimGriglia, dimGriglia), numNavi, SecondPlayerNickname);
                        }
                        else
                        {
                            gioco->Scegli_Impostazioni(true, std::make_pair(dimGriglia, dimGriglia), numNavi, SecondPlayerNickname);
                        }

                        gioco->ConfermaImpostazioni();

                        Partita* partita = gioco->getPartitaCorrente();
                        Giocatore* giocatore2 = partita->getGiocatore2();

                        int maxNumNavi = partita->GetNumeroNavi();
                        int currNumNavi = maxNumNavi;

                        std::vector<Giocatore*> giocatori;
                        giocatori.push_back(mainPlayer);
                        giocatori.push_back(giocatore2);

                        std::this_thread::sleep_for(std::chrono::seconds(3));
                        ClearConsole();

                        ////////////////////////////////// PARTE RELATIVA AL PIAZZAMENTO DELLE NAVI //////////////////////////////////
                        for (auto& giocatore : giocatori)
                        {
                            std::unordered_map<std::string, int> mappaNavi = gioco->CreaMappaNavi();
                            gioco->IniziaTurnoSchieramento(giocatore, partita);
                            while (currNumNavi > 0)
                            {
                                std::cout << "--------------------------------------------------------------" << std::endl;

                                partita->StampaGriglia(giocatore);

                                // Itera attraverso la mappa e stampa il nome della nave e il numero disponibile
                                std::cout << "Navi disponibili:" << std::endl;
                                for (const auto& pair : mappaNavi)
                                {
                                    const std::string& nome = pair.first;
                                    int numero = pair.second;
                                    std::cout << nome << ": " << numero << " disponibili" << std::endl;
                                }
                                std::cout << "Inserire id della nave che si vuole schierare: ";
                                std::cout << "Incrociatore(id 1), Corazzata(id 2), Portaerei(id 3), Sottomarino(id 4)" << std::endl;

                                int id;
                                //controlla se il turno e' del secondo giocatore ed e' un bot
                                if (partita->get_TurnoCorrente()->getNickGiocatore() == giocatore2->getNickname() && partita->isG2_Umano() == false)
                                {
                                    std::cout << "Il secondo giocatore e' un bot" << std::endl;
                                    id = rand() % 4 + 1;
                                }
                                else
                                {
                                    std::cin >> id;
                                }
                                if (!gioco->ScegliNave(id))
                                {
                                    std::cout << "Errore nella selezione della nave. Riprova!" << std::endl;
                                    continue;
                                }

                                // Chiedi all'utente la posizione e la direzione per piazzare la nave
                                // Se il secondoGiocatore e' un bot allora usa posizioni a caso

                                int posizioneX;
                                char posizioneY;
                                std::string direction;

                                if (partita->get_TurnoCorrente()->getNickGiocatore() == giocatore2->getNickname() && partita->isG2_Umano() == false)
                                {
                                    posizioneX = rand() % partita->getDimGriglia().first;
                                    posizioneY = 'A' + (rand() % partita->getDimGriglia().second);
                                    int temp = rand() % 2;
                                    direction = temp == 0 ? "H" : "V";
                                }
                                else
                                {
                                    std::cout << "Scegli la posizione X: ";
                                    std::cin >> posizioneX;

                                    std::cout << "Scegli la posizione Y: ";
                                    std::cin >> posizioneY;

                                    std::cout << "Scegli la direzione (H/V): ";
                                    std::cin >> direction;
                                }

                                Nave* naveSelezionata = gioco->getNave();
                                if (naveSelezionata)
                                {
                                    std::string nomeNave = naveSelezionata->getNome();
                                    if (mappaNavi[nomeNave] > 0 && gioco->ScegliPosizione(posizioneX, std::toupper(posizioneY), direction))
                                    {
                                        mappaNavi[nomeNave]--;
                                        currNumNavi--;
                                        std::cout << "Nave " << nomeNave << " piazzata correttamente!" << std::endl;
                                    }
                                    else
                                    {
                                        std::cout << "Errore: nessuna nave di tipo " << nomeNave << " disponibile per il piazzamento oppure posizione sbagliata!" << std::endl;
                                    }
                                }
                                else
                                {
                                    std::cout << "Errore: nessuna nave selezionata!" << std::endl;
                                }
                            }
                            partita->StampaGriglia(giocatore);
                            partita->ResetTurnoSchieramento();
                            currNumNavi = maxNumNavi;
                        }

                        std::cout << "I giocatori hanno piazzato tutte le navi" << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(5));
                        ClearConsole();
                        ////////////////////////////////// FINE DELLA PARTE RELATIVA AL PIAZZAMENTO DELLE NAVI //////////////////////////////////

                        ////////////////////////////////// PARTE RELATIVA ALL'ATTACCO //////////////////////////////////
                        std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
                        std::cout << "Inizia la fase di attacco!" << std::endl;

                        while (partita->isOver() == false)
                        {
                            Giocatore* giocatoreCorrente = nullptr;
                            Giocatore* giocatoreInAttesa = nullptr;

                            Turno* lastTurno = partita->getLastValidTurnoAttacco() == nullptr ? partita->getLastValidTurnoSchieramento() : partita->getLastValidTurnoAttacco();
                            if (lastTurno == nullptr)
                            {
                                return -1;
                            }
                            else
                            {
                                std::string lastPlayer = lastTurno->getNickGiocatore();
                                giocatoreCorrente = (lastPlayer == mainPlayer->getNickname()) ? giocatore2 : mainPlayer;
                                giocatoreInAttesa = (lastPlayer == mainPlayer->getNickname()) ? mainPlayer : giocatore2;
                                std::cout << "Turno del giocatore " << giocatoreCorrente->getNickname() << std::endl;
                                std::cout << "L'ultimo turno era del giocatore " << lastTurno->getNickGiocatore() << std::endl;
                            }
                            std::cout << "Questa e' la tua griglia delle posizioni: " << std::endl;
                            partita->getGriglia(giocatoreCorrente)->StampaGriglia();
                            std::cout << "--------------------------------------------------------------" << std::endl;
                            std::cout << "Questa e' la tua griglia degli attacchi: " << std::endl;
                            partita->getGriglia(giocatoreInAttesa)->DrawAttackGrid();

                            int posizioneX;
                            char posizioneY;
                            //controlla se il turno e' del bot
                            if (lastTurno->getNickGiocatore() == mainPlayer->getNickname() && partita->isG2_Umano() == false)
                            {
                                posizioneX = rand() % partita->getDimGriglia().first;
                                posizioneY = 'A' + (rand() % partita->getDimGriglia().second);
                                gioco->ScegliPosizioneAttacco(posizioneX, posizioneY);
                            }
                            else
                            {
                                std::cout << "Scegli posizione di attacco X: ";
                                std::cin >> posizioneX;

                                std::cout << "Scegli posizione di attacco Y: ";
                                std::cin >> posizioneY;
                                gioco->ScegliPosizioneAttacco(posizioneX, posizioneY);
                            }
                        }
                        ClearConsole();
                        std::cout << "Un giocatore ha perso tutte le navi! partita finita, controllo il vincitore..." << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(5));
                        ////////////////////////////////// FINE DELLA PARTE RELATIVA ALL' ATTACCO //////////////////////////////////


                        ////////////////////////////////// PARTE RELATIVA ALLA FINE DELLA PARTITA //////////////////////////////////
                        if (partita->isOver()) {
                            std::string vincitore = partita->getWinner()->getNickname();
                            std::cout << "Il vincitore e': " << vincitore << std::endl;
                            // Controllo se il vincitore è il giocatore 1 o 2
                            if (vincitore == mainPlayer->getNickname()) {
                                AggiornaPunteggio(classificaFile, vincitore, 1);
                            } else if (vincitore == giocatore2->getNickname() && partita->isG2_Umano()) {
                                AggiornaPunteggio(classificaFile, vincitore, 1);
                            }
                            gioco->GestisciFinePartita();
                        }

                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        std::cout << "Giocare un'altra partita? (Y/N): ";
                        char risposta;
                        std::cin >> risposta;

                        if (risposta == 'Y' || risposta == 'y')
                        {
                            gameIsRunning = true;
                        }
                        else
                        {
                            gameIsRunning = false;
                        }
                    }
                }
                break;
                case 2:
                {
                    // Visualizza la classifica
                    VisualizzaClassifica(classificaFile);
                    break;
                }
                case 3:
                {
                    // Esci dal gioco
                    std::cout << "Grazie per aver giocato! Arrivederci!" << std::endl;
                    userChoice = false; // Esci dal menu
                    break;
                }
                default:
                std::cout << "Scelta non valida, riprova." << std::endl;
                break;
        }
    //implementa il testing
    }    
    return 0;
}

#endif
