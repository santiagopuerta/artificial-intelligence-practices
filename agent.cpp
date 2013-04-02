/*
 * Santiago J. Puerta Correa
 */
#include "agent.h"
#include "environment.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <utility>


using namespace std;

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	ActionType accion;
	if(bump_){
		switch(orientacion){
			case 0:
				mapa[(x+9)%10][y] = -1;
				break;
			case 1:
				mapa[x][(y+1)%10] = -1;
				break;
			case 2:
				mapa[(x+1)%10][y] = -1;
				break;
			case 3:
				mapa[x][(y+9)%10] = -1;
				break;
		}
		//cout << "-- Pared --" << endl;
	}else if(ultima == actFORWARD){
		CambiaPos();
		mapa[x][y] += 1;
	}
	if(dirty_){
		accion = actSUCK;
	}else{
		accion = DondeGirar();
	}
	//PintaMatriz();
	//cout << "Posicion actual x: " << x << " y: " << y << endl;
	ultima = accion;
	return accion;
}

Agent::ActionType Agent::DondeGirar(){
	ActionType accion;
	int delante, detras, izquierda, derecha, valor;
	//cout << "Orientacion: " << orientacion << endl;
	switch(orientacion){
		case 0:
			delante = mapa[(x+9)%10][y];
			detras = mapa[(x+1)%10][y];
			izquierda = mapa[x][(y+9)%10];
			derecha = mapa[x][(y+1)%10];
			break;
		case 1:
			delante = mapa[x][(y+1)%10];
			detras = mapa[x][(y+9)%10];
			izquierda = mapa[(x+9)%10][y];
			derecha = mapa[(x+1)%10][y];
			break;
		case 2:
			delante = mapa[(x+1)%10][y];
			detras = mapa[(x+9)%10][y];
			izquierda = mapa[x][(y+1)%10];
			derecha = mapa[x][(y+9)%10];
			break;
		case 3:
			delante = mapa[x][(y+9)%10];
			detras = mapa[x][(y+1)%10];
			izquierda = mapa[(x+1)%10][y];
			derecha = mapa[(x+9)%10][y];
			break;
	}
	//cout << "delante: " << delante << endl;
	accion = actFORWARD;
	valor = delante;
	if(derecha != -1 && derecha < valor){
		accion = actTURN_R;
		orientacion = (orientacion + 1)%4;
		valor = derecha;
	}
	if(izquierda != -1 && izquierda < valor){
		accion = actTURN_L;
		orientacion = (orientacion + 3)%4;
		valor = izquierda;
	}
	if(valor == -1){
		accion = actTURN_R;
		orientacion = (orientacion + 1)%4;
	}
	//cout << "Orientacion despues de accion: " << orientacion << endl;
	return accion;
}

//Para pintar la matriz mapa.
void Agent::PintaMatriz(){
    for(int f=0; f<10; f++){
        for(int c=0; c<10; c++){
            cout << setw(2) << mapa[f][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Agent::CambiaPos(){
	// Si no choca
	switch(orientacion){
		case 0:
			x=(x+9)%10;
			break;
		case 1:
			y=(y+1)%10;
			break;
		case 2:
			x=(x+1)%10;
			break;
		case 3:
			y=(y+9)%10;
			break;
	}
}

// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	bump_ = env.isJustBump();
	dirty_ = env.isCurrentPosDirty();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
    switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actSUCK: return "SUCK";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}
