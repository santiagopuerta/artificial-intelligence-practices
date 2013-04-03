/*
 * Santiago J. Puerta Correa
 */
#ifndef AGENT__
#define AGENT__

#include <string>
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent():bump_(false), dirty_(false){
	    x = 0;
	    y = 0;
	    orientacion = 0;
	    ultima = actFORWARD;
        for(int f=0; f<10; f++){
            for(int c=0; c<10; c++){
                        mapa[f][c] = 0;
            }
        }
	}
	
	enum ActionType
	{
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
	    actSUCK,
	    actIDLE
	};
	
	void Perceive(const Environment &env);
	ActionType Think();
	void PintaMatriz();
	void CambiaPos();
	ActionType DondeGirar();
	void ActualizaMapa();
private:
	bool bump_, dirty_;
    int mapa[10][10];
    int x,y; // Posiciones actuales.
    int orientacion;
    ActionType ultima;

};

string ActionStr(Agent::ActionType);

#endif
