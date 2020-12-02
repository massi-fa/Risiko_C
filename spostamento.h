//
// Created by maxim on 06/03/2019.
//

#ifndef FP_BASE_SPOSTAMENTO_H
#define FP_BASE_SPOSTAMENTO_H

#include "combattimenti.h"


_Bool territoriGiocatoreAdiacenti(Territorio terre[],int id);
void stampaTerritoriAdiacenti(Territorio terre[],int idGiocatore);
_Bool controlloAdiacenzeDiTerritorio(Territorio terre[],int idTerritorio);
int sceltaTerritorioSpostamenti(Territorio terre[],int idGiocatore);
int sceltaDestinazione(Territorio terre[],int idTerritorioP);
void ArmateSpostamenti(Territorio terre[],int idTerritorio,int idTerritorioD);
void spostamentoStrategico(DatiG array[],Territorio terre[],int posizioneG);

#endif //FP_BASE_SPOSTAMENTO_H
