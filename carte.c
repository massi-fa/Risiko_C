//
// Created by maxim on 23/02/2019.
//

#include "carte.h"
/**
 * Procedura che raggruppa le funzioni necessarie a generare e mischiare il numero delle carte,
 * e a settare il vettore dei territori
 * @param carte puntatore alla struttura di tipo Mazzo
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param order puntatore alla struttura di tipo Deck
 */
void mazzoCarte(Mazzo* carte,Territorio terre[],Deck* order){
    generaMazzo(carte);                //Genera la lista carte
    settaArrayTerritori(carte,terre);  //Inizializza il vettore contenente i dati dei territori
    mischiaMazzo(carte);               //Mischia la lista carte
    inserisciInOrdine(carte,order);    //Salva lordine degli id delle carte in order
    numerocarte(carte,order);          //Salva il numero di carte
    stampaLista(carte);                //Stampa la lista
}
/**
 * Procedura che inizializza il vettore dei territori tramite le informazioni contenuta nella lista carte
 * @param carte puntatore alla struttura di tipo Mazzo
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 */
void settaArrayTerritori(Mazzo* carte,Territorio terre[]){
    int i=0;
    Elemento *it=NULL;
    it=carte->testa;
    while(it!=NULL){                         //While che scorre la lista fino a che il nodo e' diverso da NULL
        /*Si inizializza il vettore terre con i dati della lista carte*/
        terre[i].idTerritori=it->info.facolta;
        terre[i].nArmate=0;
        it=it->next;
        i++;
    }
}
/**
 * Procedura che inizializza contatore e testa della lista carte
 * @param carte puntatore alla struttura di tipo Mazzo
 */
void inizializzaMazzo(Mazzo *carte){
    carte->contatore=0;  //Inizializza contatore a 0
    carte->testa=NULL;   //Inizializza la testa a NULL in quanto la lista e' ancora vuota
}
/**
 * Procedura che crea e inizializza la lista carte tramite la procedura inserisciInCoda e settaValoreMazzo
 * @param carte puntatore alla struttura di tipo Mazzo
 */
void generaMazzo(Mazzo* carte){
    inizializzaMazzo(carte);
    int i;
    for (i=0;i<N_COUNTRY;i++) { //Ciclo for con numero di iterazioni pari al numero delle carte
        inserisciInCoda(carte,settaValoreMazzo(carte->contatore)); //Inserisce un nuvo elemento nella lista
    }

}
/**
 * Funzione che inizializza un nodo aiuto di tipo Informazione in base all'intero passato
 * @param contatore intero indicante il numero del nodo che si vaa inizializzare
 * @return aiuto elemento di tipo Informazione contentente i dati da inserire nel nodo della lista
 */
Informazione settaValoreMazzo(int contatore){
    Informazione aiuto;
    aiuto.facolta=contatore;
    aiuto.tipologia=territoriTipologia(contatore);
    return aiuto;
}
/**
 * Funzione che alloca in memoria lo spazione per un nuovo elemento della lista
 * @return nuovoElemento puntatore contenente l'indirizzo di memoria del nuovo nodo
 */
Elemento* allocaNuovoNodo() {
    Elemento *nuovoElemento = (Elemento*) malloc(sizeof(Elemento));
    return nuovoElemento;
}
/**
 * Funzione che inserisce un nuovo nodo in testa alla lista
 * @param carte puntatore alla struttura di tipo Mazzo
 * @param info  struttura di tipo Informazione contenente i dati per inizializzare il nodo della lista
 * @return nuovoElemento puntatore contenente l'indirizzo di memoria del nuovo nodo
 */
Elemento* inserisciInTesta(Mazzo* carte,Informazione info) {
    Elemento *nuovoElemento = allocaNuovoNodo();
    nuovoElemento->info =info;
    nuovoElemento->next = carte->testa;
    carte->testa = nuovoElemento;
    carte->contatore++;
    return nuovoElemento;
}
/**
 * Funzione che inserisce un nuovo nodo in coda alla lista
 * @param carte carte puntatore alla struttura di tipo Mazzo
 * @param info  struttura di tipo Informazione contenente i dati per inizializzare il nodo della lista
 * @return nuovoElemento puntatore contenente l'indirizzo di memoria del nuovo nodo
 */
Elemento* inserisciInCoda(Mazzo* carte,Informazione info) {
    Elemento *nuovoElemento = NULL;
    Elemento *it = NULL;
    if (carte->testa == NULL) { //Se la lista è vuota, l'inserimento in coda è uguale a quello in testa
        return inserisciInTesta(carte, info);
    }
    else {                      //Se la lista ha almeno un nodo  inserisce il nuovo nodo in coda
        nuovoElemento = allocaNuovoNodo();
        nuovoElemento->info = info;
        nuovoElemento->next = NULL;
        it = carte->testa;
        while (it->next != NULL) {
            it = it->next;
        }
        it->next = nuovoElemento;
        carte->contatore++;
        return nuovoElemento;
    }
}
/**
 * Funzione che in base all'id della facolta ricevuto in input restituisce il tipo di arma associato alla carta
 * @param id intero corrispondente all'id della facolta'
 * @return tipo intero corrispondente alla tipologia dell'arma
 */
int territoriTipologia(int id) {
    int tipo;
    switch(id){
        case PSICOLOGIA:
            tipo=VINO;
            return tipo;
        case FILOSOFIA:
            tipo=BIRRA;
            return tipo;
        case PEDAGOGIA:
            tipo=VINO;
            return tipo;
        case LETTERE:
            tipo=BIRRA;
            return tipo;
        case LINGUE:
            tipo=CAFFE;
            return tipo;
        case ECONOMIA:
            tipo=VINO;
            return tipo;
        case SCIENZEPOLITICHE:
            tipo=BIRRA;
            return tipo;
        case GIURISPRUDENZA:
            tipo=CAFFE;
            return tipo;
        case ODONTOIATRIA:
            tipo=VINO;
            return tipo;
        case INFERMIERISTICA:
            tipo=CAFFE;
            return tipo;
        case MEDICINA:
            tipo=CAFFE;
            return tipo;
        case SCIENZEMOTORIE:
            tipo=BIRRA;
            return tipo;
        case CTF:
            tipo=VINO;
            return tipo;
        case TOSSICOLOGIA:
            tipo=CAFFE;
            return tipo;
        case BIOLOGIA:
            tipo=BIRRA;
            return tipo;
        case SCIENZEDELLANATURA:
            tipo=CAFFE;
            return tipo;
        case FARMACIA:
            tipo=VINO;
            return tipo;
        case INGCHIMICA:
            tipo=CAFFE;
            return tipo;
        case INGMECCANICA:
            tipo=BIRRA;
            return tipo;
        case INGELETTRONICA:
            tipo=CAFFE;
            return tipo;
        case ARCHITETTURA:
            tipo=CAFFE;
            return tipo;
        case INGCIVILE:
            tipo=BIRRA;
            return tipo;
        case CHIMICA:
            tipo=CAFFE;
            return tipo;
        case FISICA:
            tipo=CAFFE;
            return tipo;
        case INFORMATICA:
            tipo=BIRRA;
            return tipo;
        case MATEMATICA:
            tipo=CAFFE;
            return tipo;
    }
}
/**
 * Procedura che riceve in input un nodo di tipo Elemento e ne stampa l'arma corrispondente
 * @param nodo dato di tipo Elemento contenente le informazioni del nodo della lista
 */
void stampaTipologia(Elemento* nodo){
    switch (nodo->info.tipologia){
        case BIRRA:
            printf("BIRRA");
            break;
        case CAFFE:
            printf("CAFFE\'");
            break;
        case VINO:
            printf("VINO");
            break;
    }
}
/**
 * Procedura che riceve in input un intero corrispondente all'id di un corso di laurea e ne stampa il nome
 * @param id intero corrispondente all'id della facolta'
 */
void stampaFacolta(int id){
    switch (id){
        case PSICOLOGIA:
            printf("PSICOLOGIA");
            break;
        case FILOSOFIA:
            printf("FILOSOFIA");
            break;
        case PEDAGOGIA:
            printf("PEDAGOGIA");
            break;
        case LETTERE:
            printf("LETTERE");
            break;
        case LINGUE:
            printf("LINGUE");
            break;
        case ECONOMIA:
            printf("ECONOMIA");
            break;
        case SCIENZEPOLITICHE:
            printf("SCIENZE POLITICHE");
            break;
        case GIURISPRUDENZA:
            printf("GIURISPRUDENZA");
            break;
        case ODONTOIATRIA:
            printf("ODONTOIATRIA");
            break;
        case INFERMIERISTICA:
            printf("INFERMIERISTICA");
            break;
        case MEDICINA:
            printf("MEDICINA");
            break;
        case SCIENZEMOTORIE:
            printf("SCIENZE MOTORIE");
            break;
        case CTF:
            printf("CTF");
            break;
        case TOSSICOLOGIA:
            printf("TOSSICOLOGIA");
            break;
        case BIOLOGIA:
            printf("BIOLOGIA");
            break;
        case SCIENZEDELLANATURA:
            printf("SCIENZE DELLA NATURA");
            break;
        case FARMACIA:
            printf("FARMACIA");
            break;
        case INGCHIMICA:
            printf("INGEGNERIA CHIMICA");
            break;
        case INGMECCANICA:
            printf("INGEGNERIA MECCANICA");
            break;
        case INGELETTRONICA:
            printf("INGEGNERIA ELETTRONICA");
            break;
        case ARCHITETTURA:
            printf("ARCHITTETURA");
            break;
        case INGCIVILE:
            printf("INGEGNERIA CIVILE");
            break;
        case CHIMICA:
            printf("CHIMICA");
            break;
        case FISICA:
            printf("FISICA");
            break;
        case INFORMATICA:
            printf("INFORMATICA");
            break;
        case MATEMATICA:
            printf("MATEMATICA");
            break;
    }
}
/**
 * Funzione che genera casualmente un numero in un range tra 0 e N_ COUNTRY
 * @return risultato intero contenente il numero generato casualmente
 */
int generazioneCasualePrima(void) {
    int risultato;
    risultato=rand()%N_COUNTRY;
    return risultato;
}
/**
 * Procedura che mischia il mazzo di carte precedente generato,
 * genera due numeri e scambia i nodi presenti in quelle posizioni
 * @param carte puntatore alla struttura di tipo Mazzo
 */
void mischiaMazzo(Mazzo* carte){
    Informazione save;
    Elemento *it=NULL;
    Elemento *iit=NULL;
    int i,id1,id2;
    for(i=0;i<N_SHUFFLE;i++) {             //Ciclo for che compie un numero di iterazioni pari a N_SHUFFLE
        do{
            id1 = generazioneCasualePrima();  //Genera un numero casuale
            id2 = generazioneCasualePrima();  //Genera un numero casuale
        }while(id1==id2);                  //Si assicura che i due numeri generati siano diversi tra loro
        it = cercaNodoPerID(carte, id1);   //Cerca il nodo nella posizione del primo numero casuale
        iit = cercaNodoPerID(carte, id2);  //Cerca il nodo nella posizione del secondo numero casuale
        /*Scambia i dati dei due nodi*/
        save = it->info;
        it->info = iit->info;
        iit->info=save;
    }
}
/**
 * Procedura che inizializza il contatore del vettore order
 * @param carte puntatore alla struttura di tipo Mazzo
 * @param order puntatore alla struttura di tipo Deck
 */
void numerocarte(Mazzo* carte,Deck* order){
    order->numeroCarte=carte->contatore;  //Associa a order->numeroCarte il numero di carte contenuto carte->contatore
}
/**
 * Funzione che cerca un nodo in base all'id del corso di laurea contenuto in esso e restituisce un puntatore al nodo
 * @param carte puntatore alla struttura di tipo Mazzo
 * @param id intero corrispondete all'id del corso di laurea ricercato
 * @return aux puntatore di tipo Elemento
 */
Elemento *cercaNodoPerID(Mazzo* carte,int id){
    Elemento *aux;
    aux=carte->testa;
    while(aux!=NULL){               //Scorre la lista fino alla fine
        if(id==aux->info.facolta){  //Controlla se id e' uguale all'id del corso nel nodo
            return aux;             //Se e' verificato il controllo restituisce aux
        }
        aux=aux->next;
    }
}
/**
 * Procedura che stampa il nodo rivevuto in input
 * @param nodo struttura di tipo elemento contenente le informazioni della lista
 */
void stampaNodo(Elemento* nodo) {
    printf("\n\nN* CARTA\nId: %d\nFACOLTA\': ", nodo->info.facolta);
    stampaFacolta(nodo->info.facolta);
    printf("\nTIPOLOGIA: ");
    stampaTipologia(nodo);
}
/**
 * Procedura che stampa la lista ricevuta in input
 * @param carte puntatore alla struttura di tipo Mazzo
 */
void stampaLista(Mazzo* carte){
    int i;
    Elemento *nodo;
    nodo=carte->testa;
    for(i=0;i<carte->contatore;i++){ //Ciclo for con iterazioni pari al numero di nodi della lista
        stampaNodo(nodo);
        nodo=nodo->next;
    }
}
/**
 * Pocedura che inizializza order, inserendo in  nel vettore deckOrder gli id dei corsi di laure dopo che la lista e'
 * stat mischiata
 * @param carte puntatore alla struttura di tipo Mazzo
 * @param order puntatore alla struttura di tipo Deck
 */
void inserisciInOrdine(Mazzo* carte,Deck* order){
    int i=0;
    Elemento *it=NULL;
    Informazione save;
    it=carte->testa;
    while(it!=NULL){
        save.facolta=it->info.facolta;
        order->deckOrder[i]=save.facolta;
        i++;
        it=it->next;
    }
}