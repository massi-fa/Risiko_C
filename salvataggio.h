//
// Created by maxim on 14/03/2019.
//

#ifndef FP_BASE_SALVATAGGIO_H
#define FP_BASE_SALVATAGGIO_H

#include "combattimenti.h"

#define MIN_GIOCATORI 2  //Macro che indica il minimo numero di giocatori che puo'avere un save
#define MAX_GIOCATORI 6  //Macro che indica il massimo numero di giocatori che puo'avere un save

void salvaPartita(Mazzo *carte,DatiG array[],Territorio terre[],Gioco_info *info_game);
void caricaPartita(DatiG array[],Territorio terre[],Mazzo *carte,Gioco_info *info_game);
void inizializzaG(DatiG array[],DatiG save,int posizione);
void inizializzaId(DatiG array[],Gioco_info *info_game);
int posizioneGiocatore(DatiG array[],int id,int nGiocatori);

#endif //FP_BASE_SALVATAGGIO_H
