//
// Created by maxim on 23/02/2019.
//

#include "login.h"
#include "game.h"

/**
 * Procedura che racchiude le funzioni necessarie per inizializzare il vettore di tipo DatiG, contenete le
 * informazioni dei giocatori
 * @param array vettore di tipo DatiG in cui verrano caricati i dati dei giocatori
 * @param nGiocatori intero contenente il numero dei giocatori
 */
void giocatori(DatiG array[],int nGiocatori) {
    printf("\nOra so che siete in %d, vediamo chi inizia..\nPremere invio per continuare..",nGiocatori);
    getchar();
    inizializzaDatiGiocatore(array, nGiocatori);                               //Inizializzo il vettore DatiG
    if (ordinaId(array, generazionecasuale(nGiocatori),nGiocatori)) {          //Controllo se il numero generato e' diverso da 0
        ordinaPerId(array,nGiocatori);                                         //Ordino il vettore DatiG in base all'id
    }
    printf("\n\nQuesti sono i giocatori e i loro dati..");
    stampaGiocatori(array, nGiocatori);                                        //Stampo i giocatori
}

/**
 * Procedura che inizializza il vettore dei giocatori di tipo DatiG tramite codice
 * (nome,colore,id,numero carte,numero armate)
 * @param array vettore di tipo DatiG in cui verranno caricati i dati dei giocatori
 * @param nGiocatori intero contenente il numero dei giocatori
 */
void inizializzaDatiGiocatore(DatiG array[],int nGiocatori){
    int c;
    char* nomi[]={"Giocatore 1","Giocatore 2","Giocatore 3","Giocatore 4","Giocatore 5","Giocatore 6"};

    for(c=0;c<nGiocatori;c++){ //Ciclo for necessario a inizializzare il vettore con numero di iterazioni e' pari a nGiocatori
        strcpy(array[c].nome,nomi[c]);
        array[c].cArmate=c;
        array[c].id=c;
        array[c].nCarte=0;
        array[c].nArmate=distribuzioneArmate(nGiocatori);
    }
}
/**
 * Funzione che restituisce un numero definito di armate in base al numero di giocatori presenti in partita
 * @param nGiocatori intero contenente il numero dei giocatori
 * @return nArmate intero contenente il numero di armate iniziali che verranno assegnate ai giocatori
 */
int distribuzioneArmate(int nGiocatori){
    int nArmate;
    switch (nGiocatori){ //Switch che in base al numero di giocatori in input assegna un numero definito a nArmate
        case 3:
            nArmate=35;
            break;
        case 4:
            nArmate=30;
            break;
        case 5:
            nArmate=25;
            break;
        case 6:
            nArmate=20;
            break;
    }
    return nArmate;
}
/**
 * Procedura che stampa i dati dei giocatori in partita
 * @param array vettore di tipo DatiG in cui verranno caricati i dati dei giocatori
 * @param nGiocatori intero contenente il numero dei giocatori
 */
void stampaGiocatori(DatiG array[],int nGiocatori){
    int i;
    for(i=0;i<nGiocatori;i++){   //Ciclo for per stampare i dati dei giocatori tramite la funzione stampaGiocatore
        stampaGiocatore(array,i);
    }
}
/**
 * Procedura che stampa i dati del giocatore in una definita posizione nel vettore
 * @param array vettore di tipo DatiG in cui verranno caricati i dati dei giocatori
 * @param posizione intero indicante la posizione del giocatore ricercato nel vettore array
 */
void stampaGiocatore(DatiG array[],int posizione){
    printf("\n\n\nID:%d",array[posizione].id);
    printf("\nNome:%s",array[posizione].nome);
    printf("\nColore armata:");
    stampaColore(array[posizione].cArmate);
}
/**
 * Procedura che stampa il colore delle armate scelte dal giocatore in base numero definito nell'enumerazione colore
 * @param colore intero indicante il colore delle armate del giocatore
 */
void stampaColore(int colore){
    switch (colore){       //Switch che stampa il colore in base all'intero inserito
        case ROSSO:
            printf("Rosso");
            break;
        case NERO:
            printf("Nero");
            break;
        case VIOLA:
            printf("Viola");
            break;
        case VERDE:
            printf("Verde");
            break;
        case GIALLO:
            printf("Giallo");
            break;
        case BLU:
            printf("Blu");
            break;
    }
}
/**
 * Funzione che ordina gli id dei giocatori in base al numero casuale passato in input
 * @param array vettore di tipo DatiG in cui verranno caricati i dati dei giocatori
 * @param nCasuale intero generato casualmente indicante la posizione del giocatore iniziale
 * @param nGiocatori intero contenente il numero dei giocatori
 * @return _Bool 0 in caso il numero casuale coincida con la prima posizione,1 se e' diverso e gli id sono stati cambiati
 */
_Bool ordinaId(DatiG array[],int nCasuale, int nGiocatori) {
    int i, id;
    if (nCasuale == PRIMA_POS) {  //Controlla se nCasuale coincide con la prima posizione( Corrispondente a 0)
        printf("\nIl caso ha voluto che inizasse %s.\nGli altri seguiranno..\n\n", array[PRIMA_POS].nome);
        return false;
    } else {                      //Se la condizione e' falsa assegna gli id a partire dal giocatore in posizione nCasuale
        for (i=nCasuale,id=PRIMA_POS;i<nGiocatori;i++,id++) { //Ciclo for per assegnare gli id
            array[i].id = id;
        }
        for (i = 0; i < nCasuale; i++, id++) {                //Ciclo for per assegnare gli id
            array[i].id = id;
        }
        return true;
    }
}/**
 * Funzione che genera un numero casuale compreso tra 0 e nGiocatori
 * @param nGiocatori intero contenente il numero dei giocatori
 * @return nCasuale intero contenente il numero generato casualmente
 */
int generazionecasuale(int nGiocatori){
    int nCasuale;
    nCasuale=rand()%(nGiocatori);
    return nCasuale;
}
/**
 * Procedura che ordina i dati dei giocatori inizializzati in InizializzaDatiGiocatore in base alla nuova assegnazione dell'id
 * @param array vettore di tipo DatiG in cui verranno caricati i dati dei giocatori
 * @param nGiocatori intero contenente il numero dei giocatori
 */
void ordinaPerId(DatiG array[],int nGiocatori){
    int i,j;
    DatiG save[nGiocatori];
    for (i=0;i<nGiocatori;i++) {           //Ciclo for che scorre il vettore save
        for (j = 0; j <nGiocatori; j++) {  //Ciclo for che cerca in array il giocaotre con l'id ricercato
            if (array[j].id == i) {
                save[i].cArmate=array[j].cArmate;
                strcpy(save[i].nome, array[j].nome);
                save[i].id = array[j].id;
            }
        }
    }
    for(i=0;i<nGiocatori;i++){            //Ciclo for che inizializza  array con i dati contenuti in save
        strcpy(array[i].nome,save[i].nome);
        array[i].cArmate=save[i].cArmate;
        array[i].id=save[i].id;
    }
}
/**
 * Procedura che inizializza la struttura info_game
 * @param info_game struttura di tipo Gioco_info contenente il numero di giocaotori e l'id del giocatore iniziale
 */
void settaInfoGame(Gioco_info *info_game){
    int nGiocatori;

    printf("\n\nRisika e\' un gioco che ammette un numero di giocatori compreso tra il 3 e il 6..\nVoi quanti siete?");

    do{                                                    //Do While usato per controllare l'inseriemento dei giocatori
        printf("\nInserire un numero comrpeso tra 3 e 6.\n-->");
        scanf("%d",&nGiocatori);
        getchar();
    }while(nGiocatori<MIN_G||nGiocatori>MAX_G);            //Controllo se nGiocatori ha un valore corretto

    info_game->nGiocatori=nGiocatori;
    info_game->GIniz=PRIMA_POS;
}