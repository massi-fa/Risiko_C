//
// Created by maxim on 24/02/2019.
//

#ifndef FP_BASE_TERRITORI_H
#define FP_BASE_TERRITORI_H

#include "carte.h"
#include "login.h"

#define NIENTE 0     //Macro che indica lo ZERO
#define AMATE_MAXT 3 //Macro che indica il numero di armate massimo posizionabile per turno


void distribuisci(Territorio terre[],Deck order[],int nGiocatori);
void territori(Territorio terre[],DatiG array[],Deck order[],int nGiocatori);
void distribuisciGiocatore(Territorio terre[],Deck order[],int id,int count);
void stampaTerritoriGiocatore(Territorio terre[],int idGiocatore);
void occupazionePrimaDistribuzione(DatiG array[],Territorio terre[],int nGiocatori);
void occupazioneSeconda(DatiG array[],Territorio terre[],int nGiocatori);
void posizionaArmate(DatiG array[],Territorio terre[],int idGiocatore);
_Bool ciSonoArmate(DatiG array[],int posizioneG);
_Bool giocatoreHaTerritorio(Territorio terre[],int idGiocatore,int scelta);
int sceltaNArmate(int nMassimo,int minimo);

//void stampaSituazioneGiocatore(DatiG array[],Territorio terre[],int id);

#endif //FP_BASE_TERRITORI_H
