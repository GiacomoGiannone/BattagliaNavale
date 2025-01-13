#include <iostream>

#include "BattagliaNavale.hpp"
#include "GiocatoreUmano.hpp"


int main()
{
    BattagliaNavale gioco;
	
    std::cout << "Benvenuto in Battaglia Navale!" << std::endl;
    std::cout << "Inserisci il tuo nickname: ";
	std::string MainPlayerNickname;
	std::cin >> MainPlayerNickname;
	std::cout << "Benvenuto " << MainPlayerNickname << "!" << std::endl;
    
	Giocatore* mainPlayer = new GiocatoreUmano(MainPlayerNickname);

	gioco.IniziaNuovaPartita(mainPlayer);

	std::cout << "Inserisci il nickname del tuo avversario: ";
	std::string SecondPlayerNickname;
	std::cin >> SecondPlayerNickname;
	std::cout << "Benvenuto " << SecondPlayerNickname << "!" << std::endl;
	std::cout << "Il secondo giocatore è un bot? (Y/N): ";
	char isBot;
	std::cin >> isBot;

	std::cout << "Impostazioni di default: griglia 10x10, 5 navi" << std::endl;

	if (isBot == 'Y' || isBot == 'y')
	{
		gioco.Scegli_Impostazioni(true, std::make_pair(10, 10), 5, SecondPlayerNickname);
	}
	else
	{
		gioco.Scegli_Impostazioni(false, std::make_pair(10, 10), 5, SecondPlayerNickname);
	}

	gioco.ConfermaImpostazioni();

	Partita* partita = gioco.getPartitaCorrente();
	gioco.IniziaTurnoSchieramento(mainPlayer, partita);
	gioco.ScegliNave();
	if (gioco.ScegliPosizione(1, 'A', "H"))
	{
		std::cout << "Nave piazzata correttamente!" << std::endl;
	}

	partita->StampaGriglieG1();

    //gioco.ScegliNave();
    return 0;
}
