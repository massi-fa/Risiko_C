//
// Created by maxim on 14/03/2019.
//

#ifndef FP_BASE_RINFORZI_H
#define FP_BASE_RINFORZI_H


#include "combattimenti.h"


#define COST_ARMATEAGG 3  //Macro che indica la costante in base a cui vengono date le armate bonus
#define B_STUM 3          //Macro che indica le armate bonus per studi umanistici
#define B_SEG 2           //Macro che indica le armate bonus per studi economici e giuridici
#define B_MC 2            //Macro che indica le armate bonus per studi medicina e chirurgia
#define B_BF 4            //Macro che indica le armate bonus per biologia e farmacia
#define B_IA 4            //Macro che indica le armate bonus per ingegneria e architettura
#define B_S 2             //Macro che indica le armate bonus per scienze
#define MAX_ARMATETOT 100 //Macro che indica il numero di armate massimo


void primaFaseRinforzi(DatiG arrray[],Territorio terre[],int idGiocatore);
void secondaFaseRinforzi(DatiG array[],Territorio terre[],int idGiocatore);
int controlloFacolta(Territorio terre[],int idGiocatore);
void distribuzioneArmateRinforzi(DatiG array[],Territorio terre[],int posizioneG);


#endif //FP_BASE_RINFORZI_H