//
// Created by maxim on 24/02/2019.
//

#include "territori.h"
/**
 * Procedura che racchiude le funzioni necessarie a distribuire i territori iniziali ai giocatori e
 * ad occuparle con le prime armate a loro disponibili
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param order puntatore alla struttura di tipo Deck
 * @param nGiocatori intero contenente il numero dei giocatori
 */
void territori(Territorio terre[],DatiG array[],Deck order[],int nGiocatori){
    int i;
    distribuisci(terre,order,nGiocatori);                 //Si distribuiscono le terre ai giocatori
    for(i=0;i<nGiocatori;i++){                            //Ciclo for con iterazioni pari a nGiocatori
        stampaTerritoriGiocatore(terre,i);                //Si stampano i territori dei giocatori
    }
    occupazionePrimaDistribuzione(array,terre,nGiocatori);//SI occupano i territori con un armata
    for(i=0;i<nGiocatori;i++){                            //Ciclo for con numero di iterazioni pari a nGiocatori
        printf("\n\n%s ha %d armate ancora disponibili",array[i].nome,array[i].nArmate);
    }
    occupazioneSeconda(array,terre,nGiocatori);           //Si occupano i territori con tre armate per turno
}
/**
 * Procedura che distribuisce i territori ai giocatori inizializzando il vettore terre seguendo l'ordine di order
 * e inizializzando il parametro terre con l'id del giocatore a cui viene assegnato il territorio
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param order order puntatore alla struttura di tipo Deck
 * @param nGiocatori intero contenente il numero dei giocatori
 */
void distribuisci(Territorio terre[],Deck order[],int nGiocatori){
    int i,id;
    for(i=0,id=0;i<order->numeroCarte;i++){           //Ciclo for con un numero di iterazioni pari a numero carte
        distribuisciGiocatore(terre,order,id,i);      //Iinizializza il campo idProprietario in terre
        id++;
        if(id==nGiocatori){                           //Arrivati all'ultimo giocatore riparte dall'id 0
            id=0;
        }
    }

}
/**
 * Procedura che inizializza il capo idProprietario di terre con l'id del giocatore
 * a cui e' stato assegnato il territorio
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param order order puntatore alla struttura di tipo Deck
 * @param id intero contenente l'id del giocatore
 * @param count intero che indica la posizione del vettore deckOrder in cui ci troviano
 */
void distribuisciGiocatore(Territorio terre[],Deck order[],int id,int count){
    terre[order->deckOrder[count]].idProprietario=id;
}
/**
 * Procedura che stampa i territori che possiedono l'id di un determinato giocatore
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param id intero contenente l'id del giocatore
 */
void stampaTerritoriGiocatore(Territorio terre[],int idGiocatore){
    int i;
    for(i=0;i<N_COUNTRY;i++){             //Ciclo for con numero di iterazioni pari a N_COUNTRY
        if(terre[i].idProprietario==idGiocatore){  //Controlla che l'id del del proprietario  sia uguale all'id in input
        printf("|");
        stampaFacolta(terre[i].idTerritori);
        printf(" - numero armate= %d | (id=%d)\n",terre[i].nArmate,terre[i].idTerritori);
        }
    }

}
/**
 * Procedura che occupa i territori appena assegnati al giocatore con una armata
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param nGiocatori intero contenente il numero dei giocatori
 */
void occupazionePrimaDistribuzione(DatiG array[],Territorio terre[],int nGiocatori){
    int i,c;
    for(i=0;i<nGiocatori;i++){                //Ciclo for che scorre i giocatori
        for(c=0;c<N_COUNTRY;c++){             //Ciclo for che scorre i territori
            if(terre[c].idProprietario==i){   //Controlla se l'id del proprietario e' uguale all'id del giocatore
                terre[c].nArmate=1;
                array[i].nArmate--;
            }
        }
    }
}
/**
 * Procedura che posiziona le armate del giocaotore nel terriotorio scelto dallo stesso
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param nGiocatori intero contenente il numero dei giocatori
 */
void occupazioneSeconda(DatiG array[],Territorio terre[],int nGiocatori){
    int i=0,ultimo;
    _Bool condizione;
    ultimo=nGiocatori-1;
    printf("\n\nE\' arrivato il momento di rendervi partecipi..");
    printf("\nDovete posizionare le restanti armate nei vostri territori.\nPotete posizionarne massimo 3 per turno..");
    do{
        condizione=ciSonoArmate(array,i); //Controlla che siano presenti armate
        if(condizione) {                           //Se e' verificata la condizione posiziona le armate
            posizionaArmate(array, terre, i);
        }
        i++;
        if(i==nGiocatori){
            i=0;
        }
    }while(array[ultimo].nArmate!=NIENTE);      //Cicla fino a che l'ultimo giocatore ha un numero di armate diveso da 0

}
/**
 * Funzione che controlla se i giocatori possiedono armate
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param posizioneG intero contenente la posizione del giocatore in array
 * @return condizione _Bool che ci restituisce un valore di verita
 */
_Bool ciSonoArmate(DatiG array[],int posizioneG){
    _Bool condizione=false;
    if(array[posizioneG].nArmate>NIENTE){ //Controlla se il giocatore possiede armate
        condizione=true;
    }

    return condizione;
}
/**
 *
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocatore che intende posizionare le armate
 */
void posizionaArmate(DatiG array[],Territorio terre[],int posizioneG){
   printf("\n\n\n\n\n\n\n");
   int count=0,scelta,armate;
   printf("\n%s e\' il tuo turno.\nHai %d armate",array[posizioneG].nome,array[posizioneG].nArmate);
   printf("\n\n");
   if(array[posizioneG].nArmate==NIENTE){                     //Controlla se il giocatore ha finito le armate
       printf("\n%s ha terminato le armate",array[posizioneG].nome);
   }else if(array[posizioneG].nArmate>=AMATE_MAXT){            //Controlla se il giocatre ha piu di 3 armate
       count=AMATE_MAXT;
       array[posizioneG].nArmate-=AMATE_MAXT;
   }else if(array[posizioneG].nArmate<AMATE_MAXT&&array[posizioneG].nArmate>NIENTE){//Controlla se ha meno di 3 armate
       count=array[posizioneG].nArmate;
       array[posizioneG].nArmate=NIENTE;
   }
   do{
       printf("\n\nPuoi posizionare %d, seleziona il territorio in cui vuoi posizionare le armate.\n", count);
       stampaTerritoriGiocatore(terre,array[posizioneG].id);
       do {
           printf("\nInserisci id.\n--->");
           scanf("%d", &scelta);
           getchar();
       } while (giocatoreHaTerritorio(terre,array[posizioneG].id,scelta)); //Controlla se il giocatore possiede il territorio
       printf("\nHai selezionato ");
       stampaFacolta(scelta);
       printf("\nQuante armate ci vuoi posizionare?\nInserisci un numero compreso tra 0 e %d--->", count);
       armate=sceltaNArmate(count,NIENTE);
       terre[scelta].nArmate += armate;
       count-=armate;
       if(count>NIENTE){
           stampaTerritoriGiocatore(terre,array[posizioneG].id);          //Stampa i terrritori del giocatore
       }
   }while(count!=NIENTE);
   printf("\n\n\n\n");

}
/**
 * Funzione che restituisce un valore di verita' dopo aver controllato se un giocatore possiede o meno un territorio
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocatore
 * @param scelta intero contenente il territorio scelto dall'utente
 * @return _Bool valore di verita
 */
_Bool giocatoreHaTerritorio(Territorio terre[],int idGiocatore,int scelta){

    if (terre[scelta].idProprietario==idGiocatore){     //Controlla se il territorio e' di proprieta' del giocatore
        return false;
    }else{
        printf("\nIl giocatore non ha ");//Se la condizione non e' verificata esegue il blocco
        stampaFacolta(scelta);
        printf("\nProva con un altro corso.\n-->");
        return true;
    }
}

/**
 * Funzione che controlla l'inserimento delle armate rispetti un determinato range
 * @param nMassimo intero contenente l'estremo massimo del range
 * @param minimo intero contenente l'intero minimo del range
 * @return scelta intero contenente il numero inserito dell'utente
 */
int sceltaNArmate(int nMassimo,int minimo){
    int scelta;
    do{
        printf("\n-->");
        scanf("%d",&scelta);
        getchar();
    }while(scelta<minimo||scelta>nMassimo);  //Controlla che il numero rispetti il range
    return scelta;
}