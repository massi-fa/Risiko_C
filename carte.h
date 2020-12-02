//
// Created by maxim on 23/02/2019.
//

#ifndef FP_BASE_CARTE_H
#define FP_BASE_CARTE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define N_CARTE 28    //Macro che indica il numero di carte
#define N_COUNTRY 26  //Macro che indica il numero dei territori
#define N_SHUFFLE 100 //Macro che indica il numero di iterazioni utili per mischiare il mazzo

typedef enum{BIRRA=1,VINO=2,CAFFE=3}Tipi;  //Enumerazione che contine il tipo d'arma della carta

typedef enum{PSICOLOGIA,FILOSOFIA,PEDAGOGIA,LETTERE,LINGUE,ECONOMIA,SCIENZEPOLITICHE,GIURISPRUDENZA,
             ODONTOIATRIA,INFERMIERISTICA,MEDICINA,SCIENZEMOTORIE,CTF,TOSSICOLOGIA,BIOLOGIA,
             SCIENZEDELLANATURA,FARMACIA,INGCHIMICA,INGMECCANICA,INGELETTRONICA,ARCHITETTURA,
             INGCIVILE,CHIMICA,FISICA,INFORMATICA,MATEMATICA}Carte; //Enumerazione che contine gli id dei territori

typedef struct {
    int facolta;
    int tipologia;
} Informazione; //Struttura contenente i dati della singola carta

typedef struct elemento {
    Informazione info; //Dato da salvare nella lista
    struct elemento *next; //Puntatore al prossimo nodo della lista
} Elemento;     //Struttura contenente i dati del nodo della lista

typedef struct {
    int contatore;
    Elemento* testa;
}Mazzo;         //Struttura contenente i dati necessari per la lista

typedef struct{
    int numeroCarte;
    int deckOrder[N_CARTE];
}Deck;          //Struttura contenente il vettore in cui viene conservato l'ordine delle carte e il numero di carte

typedef struct {
    int idTerritori;
    int idProprietario;
    int nArmate;
}Territorio;    //Struttura contenente i dati del singolo territorio

void inizializzaMazzo(Mazzo *carte);
void generaMazzo(Mazzo* carte);
Informazione settaValoreMazzo(int contatore);
Elemento* allocaNuovoNodo();
Elemento* inserisciInTesta(Mazzo* carte,Informazione info);
Elemento* inserisciInCoda(Mazzo* carte,Informazione info);
int territoriTipologia(int id);
void stampaTipologia(Elemento* nodo);
void stampaFacolta(int id);
int generazioneCasualePrima(void);
void mischiaMazzo(Mazzo* carte);
Elemento *cercaNodoPerID(Mazzo* carte,int id);
void stampaNodo(Elemento* nodo);
void stampaLista(Mazzo* carte);
void mazzoCarte(Mazzo* carte,Territorio terre[],Deck* order);
void numerocarte(Mazzo* carte,Deck* order);
void inserisciInOrdine(Mazzo* carte,Deck* order);
void settaArrayTerritori(Mazzo* carte,Territorio terre[]);

#endif //FP_BASE_CARTE_H
