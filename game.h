//
// Created by maxim on 08/03/2019.
//

#ifndef FP_BASE_GAME_H
#define FP_BASE_GAME_H

#include "rinforzi.h"
#include "spostamento.h"
#include "combattimenti.h"
#include "salvataggio.h"

#define MAX_ARMATEG 100  //Macro che indica il numero di armate max per giocatore
#define SOLO 1           //Macro che indica il valore che ha nGiocatori se e' presente solo un giocatore

void turni(DatiG array[],Territorio terre[],int posizioneG,Gioco_info *info_game);
_Bool  contaArmateGiocatore(Territorio terre[],int idGiocatore);
_Bool giocatorePuoSpostare(Territorio terre[],int id);
void game(Mazzo *carte,Territorio terre[],DatiG array[],Gioco_info *info_game);
void Risika();


#endif //FP_BASE_GAME_H
