//
// Created by maxim on 23/02/2019.
//

#ifndef FP_BASE_LOGIN_H
#define FP_BASE_LOGIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define VET_GIOCATORI 6 //Macro usata per inizializzare ilvettore dei giocatori
#define MIN_G 3         //Macro che indica il minimo numero dei giocatori di una partita
#define MAX_G 6         //Macro che indica il massimo numero dei giocatori di una partita
#define N_CARTE 28      //Macro che indica il numero di carte
#define DIM_NOME 23     //Macro che indica la dimensione della stringa nome
#define PRIMA_POS 0     //Macro che indica la prima posizione del vettore giocatori


typedef enum {ROSSO,NERO,VIOLA,VERDE,GIALLO,BLU} cArmate; //Enumerazione contenente il colore delle armate


typedef struct {
    char nome[DIM_NOME+1];
    int cArmate;
    int nCarte;
    int nArmate;
    int cartePossedute [N_CARTE];
    int id;

}DatiG;        //Struttura contenente i dati del giocatore

typedef struct {
    int nGiocatori;
    int GIniz;
}Gioco_info;  //Struttura che contiene il numero dei giocatori e il giocatore iniziale

void giocatori(DatiG array[],int nGiocatori);
void inizializzaDatiGiocatore(DatiG array[],int nGiocatori);
void stampaGiocatori(DatiG array[],int nGiocatori);
void stampaGiocatore(DatiG array[],int posizione);
void stampaColore(int colore);
_Bool ordinaId(DatiG array[],int nCasuale,int nGiocatori);
int generazionecasuale(int nGiocatori);
void ordinaPerId(DatiG array[],int nGiocatori);
int distribuzioneArmate(int nGiocatori);
void settaInfoGame(Gioco_info *info_game);


#endif //FP_BASE_LOGIN_H
