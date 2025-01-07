#include <iostream>

class BattagliaNavale
{
private:

public:
	BattagliaNavale();
	bool ScegliNave(int idNave);
	bool ScegliPosizione(int x, char y, std::string direction);
	bool ScegliPosizione(int x, char y, std::string direction, int dim);
	bool ConfermaPiazzamentoNavi();
	bool ScegliPosizioneAttacco(int x, char y);
	void AggiornaGriglia();
	void IniziaNuovaPartita();
	void Scegli_Impostazioni(bool giocatoreUmano, std::pair<int, int> dimGriglia, std::string nomeAvversario);
	void ConfermaImpostazioni();
};