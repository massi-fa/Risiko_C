//
// Created by maxim on 06/03/2019.
//

#include "spostamento.h"
/**
 * Procedura che consente al giocatore di spostare armate in territori adiacenti
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param posizioneG intero contenente la posizione del giocatore nel vettore array
 */
void spostamentoStrategico(DatiG array[],Territorio terre[],int posizioneG){
    int idTerritorio,idTerritorioD;
    _Bool scelta;
    if(territoriGiocatoreAdiacenti(terre,array[posizioneG].id)){  //Controlla se i territori sono adiacenti
      stampaTerritoriAdiacenti(terre,array[posizioneG].id);       //Stampa i territori adiacenti
      printf("\nDesideri fare qualche spostamento?");
      scelta=SioNo();                                             //Assegno un valore di verita' a scelta
      if(scelta){
              printf("\nInserire id del territorio da cui si vogliono spostare le armate");
              idTerritorio=sceltaTerritorioSpostamenti(terre,array[posizioneG].id);
              printf("\nHai selezionato ");
              stampaFacolta(idTerritorio);
              if(terre[idTerritorio].nArmate>ARMATE_ATT) { //Controllo se nel territori il numero di armate consente lo spostamento
                  printf("\nScegli dove vorresti spostare le truppe e quante vorresti spostarne");
                  idTerritorioD=sceltaDestinazione(terre,idTerritorio);
                  ArmateSpostamenti(terre,idTerritorio,idTerritorioD);   //Sposto le armate
              }else{
                  printf("\nNon hai truppe sufficenti per effettuare spostamenti..");
              }
      }
    }

}
/**
 * Procedura che consente di trasferire un numero di armate scelto dall'utente
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idTerritorio intero contenente il terriotorio da cui si vogliono spostare le armate
 * @param idTerritorioD intero contenente il terriotorio in cui si vogliono spostare le armate
 */
void ArmateSpostamenti(Territorio terre[],int idTerritorio,int idTerritorioD){
    int counter,scelta;
    counter=terre[idTerritorio].nArmate-1;
    printf("\nPuoi trasferire %d",counter);
    printf("\nInserire il numero di armate che vuoi trasferire: (Da 0 a %d)",counter);
    scelta=sceltaNArmate(counter,NEGATIVO);  //Assegno a scelta il numero deciso dall'utente
    terre[idTerritorio].nArmate-=scelta;
    terre[idTerritorioD].nArmate+=scelta;
}
/**
 * Funzione che permette all'utente di selezionare l'id del territorio di destinazione che viene poi restituito
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idTerritorioP intero contenente l'id del territorio da cui si vogliono spostare le armate
 * @return idTerritorioD intero contenente l'id del territorio in cui si vogliono spostare le armate
 */
int sceltaDestinazione(Territorio terre[],int idTerritorioP){
    int idTerritorioD;
    printf("\nInserisci l'id del territorio in cui vuoi spostare le armate");
    do{
        printf("\n-->");
        scanf("%d",&idTerritorioD);
        getchar();
        /*Controlla se il territorio e' dell'utente e se i due territori sono adiacenti*/
    }while(terre[idTerritorioD].idProprietario!=terre[idTerritorioP].idProprietario||!isAdjacent(idTerritorioP,idTerritorioD));
    return idTerritorioD;
}
/**
 * Funzione che permette all''utente di selezionare il territorio da cui vuole spostare le armate
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocatore in turno
 * @return idterritorio intero contenente l'id del territorio da cui il giocatore intende partire
 */
int sceltaTerritorioSpostamenti(Territorio terre[],int idGiocatore){
    int idTerritorio;
    do {
        do {
            printf("\n-->");
            scanf("%d", &idTerritorio);
            getchar();
            if(!controlloTerritorioAttacco(terre,idGiocatore,idTerritorio)){//Controlla che il territorio abbia adiacenze
                printf("\nNon ci sono territori in cui spostare le armate..\nProva di nuovo");
            }
            if(terre[idTerritorio].nArmate<=ARMATE_ATT){//Controlla che il territorio scelto abbia piu' di un armata
                printf("\nIl territorio da te scelto non ha abbastanza armate per effettuare spostamenti..\nProva di nuovo");
            }
            /*Controllo che il territorio sia del giocatore in turno e che il territorio abbia un adiacenza*/
        } while (terre[idTerritorio].idProprietario != idGiocatore ||
                 !controlloAdiacenzeDiTerritorio(terre, idTerritorio));
    }while(terre[idTerritorio].nArmate<ARMATE_ATT); //Cicla fino a che il terriotiro scelto ha almeno un armata
    return idTerritorio;
}
/**
 * Procedura che stampa i territori in cui e' possibile eseguire uno spostamento
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocatore in turno
 */
void stampaTerritoriAdiacenti(Territorio terre[],int idGiocatore){
    int i,j;
    for(i=0;i<N_COUNTRY;i++){                         //Ciclo for usato per scorrere il vettore terre
        if(terre[i].idProprietario==idGiocatore){     //Controlla che il il territorio sia del giocatore in turno
            /*Controlla se ha adiacenze e se ha piu' di un armata*/
            if(controlloAdiacenzeDiTerritorio(terre,i)&&terre[i].nArmate>ARMATE_ATT){
                printf("\n");
                stampaFacolta(i);
                printf("(id=%d) con %d armate e\' adiacente a:",i,terre[i].nArmate);
                for(j=0;j<N_COUNTRY;j++){
                    /*Controlla se il territorio e' del giocatore e diverso dal precedente*/
                    if(terre[j].idProprietario==idGiocatore&&terre[j].idTerritori!=i){
                        if(isAdjacent(i,j)){          //Controlla se il territorio e' adiacente al territorio di partenza
                            stampaFacolta(j);
                            printf(" (id=%d) con %d armate| ",j,terre[j].nArmate);
                        }
                    }
                }
            }
        }
    }
}
/**
 * Funzione che restituisce un valore di verita in caso il territorio in input abbia un adiacenza
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idTerritorio intero contenente l'id del territorio di cui si vuole sapere se possiede adiacenze
 * @return _Bool valore di verita
 */
_Bool controlloAdiacenzeDiTerritorio(Territorio terre[],int idTerritorio) {
    int j;
    _Bool condizione = false;
    for (j = 0; j < N_COUNTRY; j++) {                                            //Ciclo usato per scorrere i territori
        if (terre[j].idProprietario == terre[idTerritorio].idProprietario) {    //Controlla se sono stesso proprietario
            if (isAdjacent(terre[j].idTerritori, terre[idTerritorio].idTerritori)) { //Controllase sono adiacenti
                return true;
            }
        }
    }
    return condizione;
}
/**
 * Funzione che restituisce un valore di verita in caso il giocatore possieda territori adiacenti
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocatore in turno
 * @return _Bool valore di verita
 */
_Bool territoriGiocatoreAdiacenti(Territorio terre[],int idGiocatore){
    int i,j;
    _Bool condizione=false;
    for(i=0;i<N_COUNTRY;i++){                                                 //Ciclo for usato per scorrere i territori
        /*Controlla se il territorio e' del giocatore e se il numero di armate e' maggiore di 1*/
        if(terre[i].idProprietario==idGiocatore&&terre[i].nArmate>ARMATE_ATT){
        for(j=0;j<N_COUNTRY;j++)                                              //Ciclo for usato per scorrere i territori
            /*COntrolla che i due territori siano diversi e che il territorio appartenga al giocatore*/
        if(terre[j].idTerritori!=terre[i].idTerritori&&terre[j].idProprietario==idGiocatore){
            if(isAdjacent(terre[i].idTerritori,terre[j].idTerritori)){        //Controlla che i due territori sono adiacenti
                condizione=true;
            }
        }
        }
    }
    return condizione;
}