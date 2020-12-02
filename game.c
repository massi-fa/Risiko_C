//
// Created by maxim on 08/03/2019.
//

#include "game.h"
/**
 * PRocedura che racchiude l'intero gioco di risika
 */
void Risika(){
    DatiG players[VET_GIOCATORI];
    Mazzo carte;
    Deck order;
    Territorio terre[N_COUNTRY];
    Gioco_info info_game;
    printf("\nBenvenuti in RISIKA...\nState per iniziare a giocare..");
    printf("\n\nDesiderate caricare una partita?");
    if(SioNo()){
        generaMazzo(&carte);
        settaArrayTerritori(&carte,terre);
        caricaPartita(players,terre,&carte,&info_game);
    }else{
        int i;
        settaInfoGame(&info_game);
        inizializzaDatiGiocatore(players,info_game.nGiocatori);
        giocatori(players, info_game.nGiocatori);
        mazzoCarte(&carte, terre, &order);
        {
            for (i = 0; i < N_COUNTRY; i++) {
                printf(" %d ", order.deckOrder[i]);
            }
            territori(terre, players, &order,info_game.nGiocatori);
        }
    }
    game(&carte,terre, players,&info_game);
}
/**
 * Procedura che permette lo svolgimento del Gioco
 * @param carte puntatore alla strutturaa di tipo Mazzo
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param info_game struttura di tipo Gioco_info
 */
void game(Mazzo *carte,Territorio terre[],DatiG array[],Gioco_info *info_game){
    int i,c=0;
    do {
        if(c!=0){ //Controlla che non sia la prima volta che si svolge un ciclo di turni
            printf("\n\n\n\nVuoi salvare la partita?");
            if(SioNo()){
                salvaPartita(carte,array,terre,info_game);
            }}
        for (i = 0; i <info_game->nGiocatori; i++){ //Ciclo for usato per lo svolgimento dei turni
            turni(array, terre, i, info_game);
        }
        c++;
    }while(info_game->nGiocatori!=SOLO);  //Cicla fino a che il numero gi giocatori e'diverso da 1

}
/**
 * Procedura che racchiude le funzioni necessarie a
 * @param array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param posizioneG intero contenente la posizione del giocatore in array
 * @param info_game struttura di tipo Gioco_info
 */
void turni(DatiG array[],Territorio terre[],int posizioneG,Gioco_info *info_game){
    int numeroG;
    printf("\n\n%s e\' il tuo turno..",array[posizioneG].nome);
    numeroG=info_game->nGiocatori;
    if(contaArmateGiocatore(terre,array[posizioneG].id)){    //Controlla che il giocatore non abbia piu' di 100 armate
        distribuzioneArmateRinforzi(array,terre,posizioneG); //Permette al giocatore di distribuire le armate bonus
    }else{
        printf("\nNon hai armate aggiuntive per rinforzare i territori");
    }
    if(giocatorePuoAttaccare(terre,array[posizioneG].id)) {  //Controlla se il giocatore puo'attaccare
        numeroG = combattimenti(terre, array,posizioneG, numeroG); //Permette lo svolgersi dei combattimenti
    }else{
        printf("\nNon puoi attaccare..");
    }
    if(numeroG>UNICO){ //Controlla che non sia rimasto un unico giocatore
        if(giocatorePuoSpostare(terre,array[posizioneG].id)) {   //Controlla se il giocatore puo' effettuare spostamenti
            spostamentoStrategico(array,terre,posizioneG);       //Permette uno spostamento strategico
        }else{
            printf("\nNon puoi fare spostamenti strategici..");
        }
    }
    info_game->nGiocatori=numeroG;

}
/**
 * Funzione che restituisce un valore di verita' se il giocatore puo' effettuare spostamenti
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocatore in turno
 * @return _Bool valore di verita',se puo' o meno effettuare spostamenti
 */
_Bool giocatorePuoSpostare(Territorio terre[],int idGiocatore){
    int i,c;
    for(i=0;i<N_COUNTRY;i++){         //Ciclo for che serve a scorrere i territori
        /*Controlla se il territorio e' del giocatore in turno e se possiede piu' di un armata*/
        if(terre[i].idProprietario==idGiocatore&&terre[i].nArmate>ARMATE_ATT){
            for(c=0;c<N_COUNTRY;c++){ //Ciclo for che serve a scorrere i territori
                /*Controlla se il territorio e' diverso da quello preso in considerazione e se i due territori sono adiacenti*/
                if(terre[c].idTerritori!=terre[i].idProprietario&&isAdjacent(i,c)){
                    return true;
                }
            }
        }
    }
    return false;
}
/**
 * Funzione che restituisce un valore di verita' se il giocatore possiede piu di 100 armate
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocatore in turno
 * @return _Bool valore di verita'
 */
_Bool  contaArmateGiocatore(Territorio terre[],int idGiocatore){
    int i,armateTot=0;
    for(i=0;i<N_COUNTRY;i++){ //Ciclo for usato per scorrere i territori
        if(terre[i].idProprietario==idGiocatore){ //Controlla se il proprietario e' del giocatore in turno
            armateTot+=terre[i].nArmate;
        }
    }
    printf("\n\n-----%d armate totali nei territori----\n",armateTot);
    if(armateTot<MAX_ARMATEG){                    //Controlla se il numero di armate e' maggiore di 100
        return true;
    }else{
        return false;
    }
}

