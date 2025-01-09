#include <iostream>
#include <vector>
#include "Partita.hpp"
#include "Giocatore.hpp"
#include "Nave.hpp"

class BattagliaNavale
{
private:
	std::vector<Partita*> ListaPartite;
	std::vector<Giocatore> ListaGiocatori;
	std::vector<std::unique_ptr<Nave>> ListaNavi;

	Nave* naveSelezionata;
public:
	BattagliaNavale();
	~BattagliaNavale();
	void IniziaTurnoSchieramento(Giocatore g, Partita p);
	bool ScegliNave();
	bool ScegliPosizione(int x, char y, std::string direction);
	//bool ScegliPosizione(int x, char y, std::string direction, int dim);
	bool ConfermaPiazzamentoNavi();
	void ScegliPosizioneAttacco(int x, char y);
	void AggiornaGriglia();
	void IniziaNuovaPartita();
	void Scegli_Impostazioni(bool giocatoreUmano, std::pair<int, int> dimGriglia, std::string nomeAvversario);
	void ConfermaImpostazioni();
};