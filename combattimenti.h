//
// Created by maxim on 02/03/2019.
//

#ifndef FP_BASE_COMBATTIMENTI_H
#define FP_BASE_COMBATTIMENTI_H

#include "territori.h"
#include "docente.h"

#define AFFERMATIVO 1 //Macro che indica una risposta affermativa
#define NEGATIVO 0    //Macro che indica un valore negativo
#define MAX_DADI 3    //Macro che indica il massimo numero di dadi per giocatore
#define DADI_MAX 6    //Macro che indica il valore massimo del dado
#define ARMATE_ATT 1  //Macro che indica il minimo numero di armate che devono presidiare un territorio
#define MIN_DADIT 1   //Macro ceh indica il minimo numero di dadi che si devono lanciare
#define UNICO 1       //Macro che indica il minimo numero di giocatori in partita

int combattimenti(Territorio terre[],DatiG array[],int id,int nGiocatori);
void stampaTerritoriDaCuiPuoiAttaccare(Territorio terre[],DatiG array[],int id);
_Bool sceltaAttaccoCorretta(Territorio terre[],int idPartenza,int idArrivo);
int combattimentiDado(Territorio terre[],DatiG array[],int idAttacante,int idDifensore,int idTerrAttack,int idTerrDif,int nGiocatori);
void ordinaVett(int array[],int dim);
int generazioneDadi(void);
int sceltaAttacco(DatiG array[],Territorio terre[],int posizioneG,int idTerritorio);
int sceltaDifesa(DatiG array[],Territorio terre[],int posizioneG,int idTerritorio);
_Bool controlliDadi(int attacco,int difesa);
int scontroDadi(Territorio terre[], int terrAtt,int terrDif,int attacco[],int difesa[],int dim1,int dim2);
void stampaTerritoriChePuoiAttaccare(Territorio terre[],int idGiocatore,int terrPartenza);
_Bool SioNo();
_Bool sceltaPartenzaGiusta(Territorio terre[],int id,int scelta);
int territorioPartenza(Territorio terre[],int idGiocatore);
int territorioArrivo(Territorio terre[],int idPartenza);
void trasferimentoConquista(Territorio terre[],int idPartenza,int idArrivo);
_Bool controlloTerritorioAttacco(Territorio terre[],int idGiocatore,int idPT);
int ridimensionaArray(DatiG array[],int posizione,int nGiocatori);
void scambiaElementi(DatiG array[],int primo,int secondo);
int eliminaGiocatore(Territorio terre[],DatiG array[],int posizoneG,int nGiocatori);
_Bool giocatorePuoAttaccare(Territorio terre[],int idGiocatore);


#endif //FP_BASE_COMBATTIMENTI_H
