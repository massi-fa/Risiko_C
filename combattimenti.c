//
// Created by maxim on 02/03/2019.
//
#include "combattimenti.h"
/**
 * Funzione che racchiude le funzioni necessarie allo scontro tra i giocatori
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param posizioneG intero contenente la posizione del giocatore nel vettore array
 * @param nGiocatori intero contenente il numero dei giocatori
 * @return nG intero contenente il numero dei giocatori, aggiornato se un giocatore viene eliminato
 */
int combattimenti(Territorio terre[],DatiG array[],int posizioneG,int nGiocatori){
    int scelta,idPartenza,idArrivo,nG;
    _Bool continua;
    nG=nGiocatori;
    printf("\n\n\n\n");
    printf("%s e\' il momento..\nVuoi attaccare?",array[posizioneG].nome);
    scelta=SioNo();
    if(scelta==AFFERMATIVO) {
        do {
            stampaTerritoriGiocatore(terre,array[posizioneG].id);                  //Stampa territori giocatore
            stampaTerritoriDaCuiPuoiAttaccare(terre, array, array[posizioneG].id); //Stampa territori da cui puo' attaccare
            idPartenza = territorioPartenza(terre, array[posizioneG].id);
            if(!controlloTerritorioAttacco(terre,array[posizioneG].id,idPartenza)){//Controlla se puo' attaccare
                printf("\nNon puoi attaccare da qua..\n");
            }else{                                                                 //Se la condizione non e' verificata
            stampaTerritoriChePuoiAttaccare(terre, array[posizioneG].id, idPartenza);//Stampa territori che puo' attaccare
            idArrivo = territorioArrivo(terre, idPartenza);
            /*Richiamo la funzione per i combattimenti*/
            nG=combattimentiDado(terre, array, array[posizioneG].id, terre[idArrivo].idProprietario, idPartenza, idArrivo,nG);

            }
            if(giocatorePuoAttaccare(terre,array[posizioneG].id)){ //Controlla se il giocatore puo' attaccare ancora
                printf("\nVuoi continuare ad attaccare?");
                continua=SioNo();
            }else{
                continua=false;
            }
        }while(continua); //Cicla fino a che il giocatore vuole e puo' attaccare
    }
    return nG;
}
/**
 * Procedura che consente di trasferire un numero di armate in un territorio appena conquistato
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idPartenza intero contenente il territorio da cuoi si stanno spostando le armate
 * @param idArrivo  intero contenente il territorio in cui si stanno spostando le armate
 */
void trasferimentoConquista(Territorio terre[],int idPartenza,int idArrivo){
    int armateTrasferibili,decisone,minimo=0;
    _Bool  condizone;
    armateTrasferibili=terre[idPartenza].nArmate-ARMATE_ATT;
    printf("\nSai gia di aver conquistato ");
    stampaFacolta(idArrivo);
    printf(",in cui hai ora %d armate",terre[idArrivo].nArmate);
    printf("\n\nPuoi spostare %d armate,vuoi trasferire qualcuna di queste armate?",armateTrasferibili);
    condizone=SioNo();
    if(condizone){
        printf("\nQuante armate vuoi trasferire? (0-%d)",armateTrasferibili);
        decisone=sceltaNArmate(armateTrasferibili,minimo);
        terre[idPartenza].nArmate-=decisone;
        terre[idArrivo].nArmate+=decisone;
    }


}
/**
 * Funzione che permette all'utente di inserire una risposta affermativa o negativa
 * @return scelta _Bool contenente un valore di verita
 */
_Bool SioNo(){
    int scelta;
    printf("\nInserire 1 per 'SI' e 0 per 'NO'..");
    do{
        printf("\n-->");
        scanf("%d",&scelta);
        getchar();
    }while(scelta!=AFFERMATIVO&&scelta!=NEGATIVO); //Controlla che il valore inserito dall'utente sia nel range
    if(scelta==AFFERMATIVO){
        return true;
    }else{
        return false;
    }
}
/**
 * Procedura che stampa i territori che il giocatore in turno puo' attaccare
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocatore in turno
 * @param terrPartenza intero contenente l'id del territorio da cui l'utente desidera attaccare
 */
void stampaTerritoriChePuoiAttaccare(Territorio terre[],int idGiocatore,int terrPartenza){
    int i;
    printf("\nPuoi attacare :\n|");
    for(i=0;i<N_COUNTRY;i++){                           //Ciclo for usato per scorrere i territori
        if(isAdjacent(terrPartenza,i)){                 //Controlla se i territori sono adiacenti
            if (terre[i].idProprietario!=idGiocatore){  //Controlla che il territorio non sia del giocatore in turno
                stampaFacolta(i);
                printf("=%d|",i);
            }
        }
    }

}
/**
 * Funzione che controlla si possa attaccare dal territorio di partenza
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocatore in turno
 * @param idPT intero contenente l'id del territorio di partenza
 * @return condizione _Bool contenente valore di verita'
 */
_Bool controlloTerritorioAttacco(Territorio terre[],int idGiocatore,int idPT) {
    int i;
    _Bool condizione = false;
    for (i = 0; i < N_COUNTRY; i++) {               //Ciclo usato per scorrere i territori
        if (terre[i].idProprietario !=idGiocatore) {//Controlla che il territorio non appartenga al giocatore in turno
            if (isAdjacent(idPT, i)) {              //Controlla che i due territori siano adiacenti
                condizione = true;
            }
        }
    }
    return condizione;
}
/**
 * Funzione che controlla se il giocatore in turno possiede almeno un territorio da cui attaccare
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocatore in turno
 * @return _Bool contenente valore di verita'
 */
_Bool giocatorePuoAttaccare(Territorio terre[],int idGiocatore){
    int i,c;
    for(i=0;i<N_COUNTRY;i++){                   //Ciclo for usato per scorrere i territori
        /*Controlla che il territorio non appartenga al giocatore in turno e che ci sia posizionata piu' di armata*/
        if(terre[i].idProprietario==idGiocatore&&terre[i].nArmate>ARMATE_ATT){
            for (c = 0; c < N_COUNTRY; c++) {   //Ciclo for usato per scorrere i territori
                /*Controlla che il territorio non appartenga al giocatore in turno*/
                if (terre[c].idProprietario!=idGiocatore) {
                    if (isAdjacent(i,c)) {      //Controlla che i territori siano adiacenti
                        return true;
                    }
                }
            }
        }
    }
    return  false;
}
/**
 * Funzione che controlla che l'insermento dell'attacco da parte dell'utente sia corretto
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idPartenza intero contenente l'id del territorio da cui si desidera far partire l'attacco
 * @param idArrivo intero contenente l'id del territotrio che si desidera attaccare
 * @return _Bool valore di verita'
 */
_Bool sceltaAttaccoCorretta(Territorio terre[],int idPartenza,int idArrivo){
    _Bool  condizione;
    condizione=isAdjacent(idPartenza,idArrivo);
    /*Controlla che i due territori abbiano proprietari diversi*/
    if(terre[idArrivo].idProprietario!=terre[idPartenza].idProprietario){
        if(condizione){
            printf("\nOttima scelta.. Riuscirai a conquistare ");
            stampaFacolta(idArrivo);
            printf(" ?");
            return false;
        }else{
            printf("\nMi dispiace ma questi territori non sono adiacenti");
            return true;
        }}else{
        printf("\nQuesto terriroio e\' tuo...\nDevi sceglierne un altro..");
        return true;
    }
}
/**
 * Funzione che permette all'utente di inserire il territorio che desidera attaccare
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idPartenza intero contenente l'id del territorio da cui si desidera far partire l'attacco
 * @return scelta intero contenente l'id del territorio scelto dall'utente
 */
int territorioArrivo(Territorio terre[],int idPartenza){
    int scelta;
    printf("\nScegli il territorio da attacare");
    do{
        printf("\n-->");
        scanf("%d",&scelta);
        getchar();
    }while(sceltaAttaccoCorretta(terre,idPartenza,scelta)); //Cicla fino a che la scelta dell'utente non e' corretta
    printf("\nHai scelto ");
    stampaFacolta(scelta);
    return scelta;

}
/**
 * Procedura che stampa i territori da cui il giocatore in turno puo' attaccare
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param posizioneG intrero contenente la posizione del giocatore nel vettore array
 */
void stampaTerritoriDaCuiPuoiAttaccare(Territorio terre[],DatiG array[],int posizioneG){
    int i;
    printf("\n\n\n%s puoi attaccare da:\n ",array[posizioneG].nome);
    for(i=0;i<N_COUNTRY;i++){                              //Ciclo for usato per scorrere i territori
        if(terre[i].idProprietario==array[posizioneG].id){ //Controlla che il territorio sia del giocatore in turno
            /*Controlla che ci sia piu' di un armata e che la scelta sia corretta*/
            if(terre[i].nArmate>ARMATE_ATT&&controlloTerritorioAttacco(terre,array[posizioneG].id,i)){
                stampaFacolta(terre[i].idTerritori);
                printf(" id=%d | ",terre[i].idTerritori);
            }
        }
    }
}
/**
 * Funzione che restituisce un valore di verita' in base alla correttezza della scelta del territorio
 * da cui fa partire l'attacco
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocatore in turno
 * @param scelta intero contenente l'id del territorio scelto dall'utente
 * @return _Bool valore di verita che dipende dalla correttezza della scelta
 */
_Bool sceltaPartenzaGiusta(Territorio terre[],int idGiocatore,int scelta){
    if(terre[scelta].idProprietario==idGiocatore){      //Controlla se il territorio appartiene al giocatore
        if(terre[scelta].nArmate>ARMATE_ATT){           //Controlla se nel territorio e' presente piu' di un armata
            return false;
        }
    }
        if(terre[scelta].idProprietario!=idGiocatore){  //Controlla se il territorio non appartiene al giocatore
            printf("\nNon possiedi questo territorio...");
        }
    if(terre[scelta].idProprietario==idGiocatore) {     //Controlla ce il territorio appartiene al giocatore
        if (terre[scelta].nArmate < ARMATE_ATT) {       //Controlla se il territorio ha meno di un armata
            printf("\nNon hai abbastanza armate per attaccare da questo territorio");
        }
    }
        return true;

}
/**
 * Funzione che permette all'utente di scegliere il territorio da cui far partire l'attacco
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocatore in turno
 * @return scelta intero contenente l'id del territorio scelto dall'utente
 */
int territorioPartenza(Territorio terre[],int idGiocatore){
    int scelta;
    printf("\nDa che terriotiro vuoi attaccare?");
    do{
        printf("\n--->");
        scanf("%d",&scelta);
        getchar();
    }while(sceltaPartenzaGiusta(terre,idGiocatore,scelta));  //Cicla fino a che l'inserimento non e' corretto
    printf("\nHai scelto ");
    stampaFacolta(scelta);
    return scelta;
}
/**
 * Funzione che racchiude le funzioni necessarie al combattimento fra giocatori, tra cui lo scontro con i dati.
 * Restituisci un numero di giocatori aggiornato nel caso in cui uno dei giocatori perda l'ultimo
 * territorio negli scontri
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param idAttacante intero contenente la poszione in array del giocatore in turno
 * @param idDifensore intero contenente la posizione sotto attacco
 * @param idTerrAttack intero contenente l'id del territorio da cui parte l'attacco
 * @param idTerrDif intero contenente l'id del territorio sotto attacco
 * @param nGiocatori intero contenente il numero dei giocatori in partita
 * @return nGiocatori intero contenente il numero di giocatori in partita
 */
int combattimentiDado(Territorio terre[],DatiG array[],int poszioneAttacante,int posizioneDifensore,int idTerrAttack,int idTerrDif,int nGiocatori){
    int difesa[MAX_DADI],attacco[MAX_DADI],attack,defense,i,ArmateAtt;
    _Bool  condizione;
    do{
            printf("\n%s ha iniziato l\'attacco vediamo come andra\' a finire..\n\n\n\n", array[poszioneAttacante].nome);
            attack = sceltaAttacco(array, terre, poszioneAttacante, idTerrAttack);  //Il giocatore sceglie i dadi per atttaccare
            printf("\n%s ha deciso di attaccare con %d truppe.", array[poszioneAttacante].nome, attack);
            defense = sceltaDifesa(array, terre, posizioneDifensore, idTerrDif);    //Il giocatore sceglie i dadi per difendere
            for (i = 0; i < defense; i++) {
                difesa[i] = generazioneDadi();       //Genera i dadi della difesa
            }
            for (i = 0; i < attack; i++) {
                attacco[i] = generazioneDadi();      //Genera i dadi dell'attacco
            }
            if (defense > MIN_DADIT) {                       //Controlla se la difesa ha lanciato piu' di un dado
                ordinaVett(difesa, defense);                 //Ordina il vettore dadi
            }
            if (attack > MIN_DADIT) {                        //Controlla se l'attacco ha lanciato piu' di un dado
                ordinaVett(attacco, attack);                 //Ordina il vettore dadi
            }
            printf("\n%s ha lanciato %d dadi: ", array[poszioneAttacante].nome, attack);
            for (i = 0; i < attack; i++) {
                printf("%d ", attacco[i]);
            }
            printf("\n%s ha lanciato %d dadi: ", array[posizioneDifensore].nome, defense);
            for (i = 0; i < defense; i++) {
                printf("%d ", difesa[i]);
            }
            ArmateAtt = scontroDadi(terre, idTerrAttack, idTerrDif, attacco, difesa, attack, defense);
            if (terre[idTerrDif].nArmate ==NIENTE) {        //Controlla se il giocatore ha finito le armate in un territorio
                terre[idTerrDif].idProprietario = array[poszioneAttacante].id;
                terre[idTerrDif].nArmate = ArmateAtt;
                terre[idTerrAttack].nArmate-=ArmateAtt;
                condizione = false;
                printf("\n\nComplimenti hai conquistato ");
                stampaFacolta(idTerrDif);
                /*Controlla se il giocatore ha ancora territori, se non ne ha elimina il giocatore*/
                nGiocatori=eliminaGiocatore(terre,array,posizioneDifensore,nGiocatori);
                if(nGiocatori>UNICO) { //Controlla che il numero di giocatori sia maggiore di uno
                    printf("\n\n\nOra i tui territori sono: ");
                    stampaTerritoriGiocatore(terre, array[poszioneAttacante].id);
                    if (terre[idTerrAttack].nArmate >
                        ARMATE_ATT) { //Controlla se l giocatore puo' trasferire armate nel nuovo territorio
                        trasferimentoConquista(terre, idTerrAttack, idTerrDif);
                    }
                }else{
                    printf("\n\n\nComplimenti %s, hai finalmente vinto la guerra..",array[PRIMA_POS].nome);
                    printf("\nPossiedi tutti i territori di Risika e ormai goversi tutti il planisfero..");
                    printf("\nChissa\' se qualcuno decidera' di riprendere la battaglia...");
                }
            }else if (terre[idTerrAttack].nArmate>ARMATE_ATT&&terre[idTerrDif].nArmate!=NEGATIVO) {
                printf("\nVuoi continuare l\'attacco verso questo territorio?");
                condizione = SioNo();
            }else{
                printf("\nNon puoi piu\' attacare da questo territorio..");
                condizione = false;
            }

    }while(condizione);
    return nGiocatori;
}
/**
 * Funzione che controlla se il giocatore ha ancora territorioì a disposizione, se non possiete alcun territorio,
 * sposta il giocatore alla fine del vettore array e decrementa il numero di giocatori in partita
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param posizioneG intero contenente la posizione del giocatore nel vettore array
 * @param nGiocatori intero contenente il numero dei giocatori in partita
 * @return numeroGAgg intero contenente il numero dei giocatori in partita
 */
int eliminaGiocatore(Territorio terre[],DatiG array[],int posizioneG,int nGiocatori){
    int i,numeroGAgg;
    _Bool condizione=false;
    numeroGAgg=nGiocatori;
    for(i=0;i<N_COUNTRY;i++){                              //Ciclo for usato per scorrere i territori
        if(terre[i].idProprietario==array[posizioneG].id){ //Controlla se il territorio appartine al giocatore
            condizione=true;
        }
    }
    if(!condizione){                                       //Controlla se la condizione e' falsa
        printf("\n\n\nIl giocatore %s non ha piu\' armate..\nE\' uscito dal gioco..",array[posizioneG].nome);
        numeroGAgg=ridimensionaArray(array,posizioneG,nGiocatori); //Funzione per eliminare il giocatore
    }
    return numeroGAgg;
}
/**
 * Funzione che sposta il giocatore da eliminare in ultima poszione e decrementa il numero di giocatori in partita
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param posizione intero contenente la posizione del giocatore da eliminare
 * @param nGiocatori intero contenente il numero di giocatori in partita
 * @return nGiocatori intero contenente il numero di giocatori in partita
 */
int ridimensionaArray(DatiG array[],int posizione,int nGiocatori){
    int i,j;
    if(posizione!=nGiocatori){   //Controlla se il giocatore da eliminare non si trova in ultima posizione in array
        i=posizione;
        j=posizione+1;
        do{
            scambiaElementi(array,i,j);
            i++;
            j++;
        }while(j<nGiocatori);
    }
    nGiocatori--;
    return nGiocatori;
}
/**
 * Procedura che serve a scambiare le informaazioni dei giocatori in array, usata per eliminare un giocatore
 * spostandolo in ultima posizione
 * @param array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param primo intero contenente la poszione del giocatore in array da scambiare
 * @param secondo intero contenente la poszione del giocatore in array da scambiare
 */
void scambiaElementi(DatiG array[],int primo,int secondo){
    DatiG save;
    save.cArmate=array[primo].cArmate;
    strcpy(save.nome, array[primo].nome);
    //printf("\nsave=%s,copia=%s",save.nome,array[primo].nome);
    save.id=array[primo].id;
    //printf("saveId=%d,copiaId=%d",save.id,array[primo].id);
    array[primo].cArmate=array[secondo].cArmate;
    array[primo].id=array[secondo].id;
    strcpy(array[primo].nome,array[secondo].nome);
    array[secondo].nArmate=save.nArmate;
    array[secondo].id=save.id;
    strcpy(array[secondo].nome,save.nome);
}
/**
 * Funzione che consente il combattimento dei dadi confrontando i dadi lanciati dai giocatori
 * e che restiruisce il numero di armate soppravvisute all'attacco
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param terrAtt intero contenente l'id del territorio da cui parte l'attacco
 * @param terrDif intero contenente l'id del territorio verso cui e' diretto l'attacco
 * @param attacco vettore coontenente i numeri dei dadi lanciati dall'attacco
 * @param difesa vettore coontenente i numeri dei dadi lanciati dalla difesa
 * @param dim1 intero contenente il numero di dadi lanciati dall'attacco
 * @param dim2 intero contenente il numero di dadi lanciati dalla difesa
 * @return nArmateatt intero contenente il numero di armate soppravvisute all'attacco
 */
int scontroDadi(Territorio terre[], int terrAtt,int terrDif,int attacco[],int difesa[],int dim1,int dim2){
    int i,c,nArmateatt;
    _Bool condizione;
    nArmateatt=dim1;
    dim1--;
    dim2--;
    if (dim1 == dim2) {                 //Controlla se difesa e attacco hanno lanciato lo stesso numero di dadi
        for (i =dim1; i>-1; i--) {      //Ciclo for usato per scorrere i dadi
            condizione=controlliDadi(attacco[i],difesa[i]); //Funzione che controlla il valore dei dadi
            if(condizione){                                 //Controlla se l'attacco ha perso lo scontro
                terre[terrAtt].nArmate--;
                nArmateatt--;
            }else{
                terre[terrDif].nArmate--;
            }
        }
    }
    if (dim1 > dim2) {                  //Controlla se l'attacco ha lanciato piu' dadi della difesa
        for (i = dim2, c =dim1; i>-1; i--, c--) {          //Ciclo for usato per scorrere i dadi
            condizione=controlliDadi(attacco[c],difesa[i]);//Funzione che controlla il valore dei dadi
            if(condizione){                                //Controlla se l'attacco ha perso lo scontro
                terre[terrAtt].nArmate--;
                nArmateatt--;
            }else{
                terre[terrDif].nArmate--;
            }
        }
    }

    if (dim1<dim2) {                    //Controlla se la difesa ha lanciato piu' dadi dell'attacco
        for (i = dim1, c = dim2 ; i>-1; i--, c--) {          //Ciclo for usato per scorrere i dadi
            condizione=controlliDadi(attacco[i],difesa[c]);  //Funzione che controlla il valore dei dadi
            if(condizione){                                  //Controlla se l'attacco ha perso lo scontro
                terre[terrAtt].nArmate--;
                nArmateatt--;
            }else{
                terre[terrDif].nArmate--;
            }
        }
    }
    return nArmateatt;
}
/**
 * Funzione che controlla il valore di due dadi e restituisce un valore di verita in caso di vittori o sconfitta
 * @param attacco intero contenente il valore del dado dell'attacco
 * @param difesa intero contenente il vslore del dado della difesa
 * @return _Bool valore di verita' indicante vittoria o sconfitta
 */
_Bool controlliDadi(int attacco,int difesa){
    if (attacco > difesa) {                      //Controlla se il valore dell'attacco e' maggiore della difesa
        printf("\nIl difensore perde un armata");
        return false;
    }

    if (attacco<difesa) {                        //Controlla se il valore dell'attacco e' minore della difesa
        printf("\nL'attaccante perde un armata");
        return true;
    }
    if (attacco == difesa) {                    //Controlla se il valore dell'attacco e' uguale della difesa
        printf("\nL'attaccante perde un armata");
        return true;
    }
}
/**
 * Procedura che ordina il vettore contenente il valore dei dadi generati, dal minore al maggiore
 * @param array vettore di interi contenente il valore dei dadi (InsertSort)
 * @param dim intero contenente la dimensione del vettore array
 */
void ordinaVett(int array[],int dim){
    int  c, d, position, swap;
    for (c = 0; c < (dim - 1); c++) {
        position = c;

        for (d = c + 1; d < dim; d++) {
            if (array[position] > array[d])
                position = d;
        }
        if (position != c) {
            swap = array[c];
            array[c] = array[position];
            array[position] = swap;
        }
    }
}
/**
 * Funzione che genra un numero casuale tra 1 e 6
 * @return nCasuale intero contenente il numero generato casualmente
 */
int generazioneDadi(void){
    int ncasuale;
    ncasuale=MIN_DADIT+rand()%DADI_MAX;
    return ncasuale;
}
/**
 * Funzione che permette al giocatore attaccante di scegliere il numero di armate con cui attaccare
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param posizioneG intero contenente la posizione del giocarore in turno in array
 * @param idTerritorio intero contenente l'id del territorio da cui il giocatore fa partire l'attacco
 * @return scelta intero contenente il numero di armate scelto dall'utente
 */
int sceltaAttacco(DatiG array[],Territorio terre[],int posizioneG,int idTerritorio){
    int scelta,possibilita,disponibili;
    printf("\n%s in ",array[posizioneG].nome);
    stampaFacolta(idTerritorio);
    printf(" ha %d",terre[idTerritorio].nArmate);
    disponibili=terre[idTerritorio].nArmate-ARMATE_ATT;
    if(disponibili==NIENTE){                           //Controlla che il numero di armate disponibili sia diverso da 0
        scelta=NIENTE;
        return scelta;
    }else{
        if(disponibili>AMATE_MAXT){                    //Controlla che il numero di armate sia aggiore di 1
            possibilita=AMATE_MAXT;
        }else{
            possibilita=disponibili;
        }
        printf("\nPuoi attaccare con %d.\nCon quante armate vuoi attaccare?",possibilita);
        scelta=sceltaNArmate(possibilita,NEGATIVO+1);
    }
    return scelta;
}
/**
 * Funzione che consente al giocatore sotto attacco di scegliere il numero di armate con cui diffendersi
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param posizioneG intero contenente la posizione del giocarore in turno in array
 * @param idTerritorio intero contenente l'id del territorio attaccato dal giocatore in turno
 * @return scelta intero contenente il numero di armate scelto dall'utente
 */
int sceltaDifesa(DatiG array[],Territorio terre[],int posizioneG,int idTerritorio) {
    int scelta, possibilita, disponibili;
    printf("\n\n%s e\' sotto attacco in ", array[posizioneG].nome);
    stampaFacolta(idTerritorio);
    printf(" dove ha %d armate", terre[idTerritorio].nArmate);
    disponibili = terre[idTerritorio].nArmate;
    if(disponibili==NIENTE){
        scelta=NIENTE;
        return scelta;
    }else {
        if (disponibili > AMATE_MAXT) {
            possibilita = AMATE_MAXT;
        } else {
            possibilita = disponibili;
        }
        printf("\nPuoi difendere con %d.\nCon quante armate vuoi difendere? ", possibilita);
        scelta = sceltaNArmate(possibilita,NEGATIVO+1);
    }
    return scelta;
}