//
// Created by maxim on 14/03/2019.
//

#include "rinforzi.h"
/**
 * Procedura che distribuisce le armate bonus in base ai territori che possiede il giocatore
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param posizioneG intero contenente la posizione del giocatore nel vettore array
 */
void distribuzioneArmateRinforzi(DatiG array[],Territorio terre[],int posizioneG){
    int scelta,count,disposizione,i,armateTot,countAtmateIpotetico;
    stampaTerritoriGiocatore(terre,array[posizioneG].id);    //Stampa i territori del giocatore
    primaFaseRinforzi(array,terre,array[posizioneG].id);     //Incrementa le armate  del giocaotre in base ai territori
    secondaFaseRinforzi(array,terre,array[posizioneG].id);   //Controlla se il giocatore controlla una facolta
    armateTot=0;
    for(i=0;i<N_COUNTRY;i++){ //Ciclo for usato per scorrere i territori
        if(terre[i].idProprietario==array[posizioneG].id){ //Controlla se il proprietario e' del giocatore in turno
            armateTot+=terre[i].nArmate;
        }
    }
    countAtmateIpotetico=armateTot+array[posizioneG].nArmate;
    if(countAtmateIpotetico>MAX_ARMATETOT){   //Controlla che la somma delle armate bonus e le armate dei territori non superi 100
        array[posizioneG].nArmate=MAX_ARMATETOT-armateTot;
    }
    if(array[posizioneG].nArmate>NIENTE){                    //Controlla se il numero di armate e' aggiore di 0
        printf("\n\n\n\n\n%s ha ricevuto %d armate aggiuntive..",array[posizioneG].nome,array[posizioneG].nArmate);
        count=array[posizioneG].nArmate;
        printf("\nScegli dove metterle..\n");
        stampaTerritoriGiocatore(terre,array[posizioneG].id); //Stampa i territori del giocatore
        do {
            printf("\nTi restano %d armate", count);
            printf("\nInserire l'id del territori in cui si desidera posizionare le proprie armate.\n-->");
            do {
                scanf("%d", &scelta);
                getchar();
            } while (giocatoreHaTerritorio(terre,array[posizioneG].id , scelta)); //Controlla se il giocatore ha il territorio
            printf("\nHai %d quante armate vuoi posizionare?",count);
            disposizione=sceltaNArmate(count,NIENTE);
            count-=disposizione;
            array[posizioneG].nArmate-=count;
            terre[scelta].nArmate+=disposizione;
        }while(count!=NIENTE);    //Cicla fino a che non ha posizionato tutte le armate
    }
}
/**
 * Procedura che incrementa le armate del giocatore in base ai territori posseduti
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocaotore in turno
 */
void primaFaseRinforzi(DatiG arrray[],Territorio terre[],int idGiocatore){
    int i,armateAgg,nTerritori=0;
    for(i=0;i<N_COUNTRY;i++){                     //Ciclo for usato per contare i territori del giocatore
        if(terre[i].idProprietario==idGiocatore){ //controlla se il territorio e' del giocatore
            nTerritori++;
        }
    }
    armateAgg=nTerritori/COST_ARMATEAGG;
    arrray[idGiocatore].nArmate=armateAgg;
}
/**
 * Procedura che incrementa il numero di armate se il giocatore possiede una determinata facolta'
 * @param array array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocaotore in turno
 */
void secondaFaseRinforzi(DatiG array[],Territorio terre[],int idGiocatore){
    array[idGiocatore].nArmate+=controlloFacolta(terre,idGiocatore);
}
/**
 * Funzione che controlla se il giocatore controlla una facolta e restituisce le armate bonus che gli spettano
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param idGiocatore intero contenente l'id del giocaotore in turno
 * @return
 */
int controlloFacolta(Territorio terre[],int idGiocatore){
    int armateAgg=0;
    /*Controllo Studi Umanistici*/
    if(terre[PSICOLOGIA].idProprietario==idGiocatore){
        if(terre[FILOSOFIA].idProprietario==idGiocatore){
            if(terre[PEDAGOGIA].idProprietario==idGiocatore){
                if(terre[LETTERE].idProprietario==idGiocatore){
                    if(terre[LINGUE].idProprietario==idGiocatore){
                        printf("\nWow,controlli tutti i corsi di laurea di Studi Umanistici..");
                        armateAgg+=B_STUM;
                    }
                }
            }
        }
    }
    /*Controllo Scienze Economiche,Giuridiche e Politiche*/
    if(terre[ECONOMIA].idProprietario==idGiocatore){
        if(terre[SCIENZEPOLITICHE].idProprietario==idGiocatore){
            if(terre[GIURISPRUDENZA].idProprietario==idGiocatore){
                printf("\nWow,controlli tutti i corsi di laurea di Scienze Economiche,Giuridiche e Politiche..");
                armateAgg+=B_SEG;
            }
        }
    }
    /*Controllo Medicina e Chirurgia*/
    if(terre[ODONTOIATRIA].idProprietario==idGiocatore){
        if(terre[INFERMIERISTICA].idProprietario==idGiocatore){
            if(terre[MEDICINA].idProprietario==idGiocatore){
                if(terre[SCIENZEMOTORIE].idProprietario==idGiocatore) {
                    printf("\nWow,controlli tutti i corsi di laurea di Medicina e Chirurgia..");
                    armateAgg+=B_MC;
                }
            }
        }
    }
    /*Controllo Biologia e Farmacia*/
    if(terre[CTF].idProprietario==idGiocatore){
        if(terre[TOSSICOLOGIA].idProprietario==idGiocatore){
            if(terre[BIOLOGIA].idProprietario==idGiocatore){
                if(terre[SCIENZEDELLANATURA].idProprietario==idGiocatore){
                    if(terre[FARMACIA].idProprietario==idGiocatore){
                        printf("\nWow,controlli tutta i corsi di laurea di Biologia e Farmacia..");
                        armateAgg+=B_BF;
                    }
                }
            }
        }
    }
    /*Controllo Ingegneria e Architettura*/
    if(terre[INGCHIMICA].idProprietario==idGiocatore){
        if(terre[INGMECCANICA].idProprietario==idGiocatore){
            if(terre[INGELETTRONICA].idProprietario==idGiocatore){
                if(terre[ARCHITETTURA].idProprietario==idGiocatore){
                    if(terre[INGCIVILE].idProprietario==idGiocatore){
                        printf("\nWow,controlli tutti i corsi di laurea di Ingegneria e Architettura..");
                        armateAgg+=B_IA;
                    }
                }
            }
        }
    }
    /*Controllo Scienze*/
    if(terre[CHIMICA].idProprietario==idGiocatore){
        if(terre[FISICA].idProprietario==idGiocatore){
            if(terre[INFORMATICA].idProprietario==idGiocatore){
                if(terre[MATEMATICA].idProprietario==idGiocatore){
                    printf("\nWow,controlli tutti i corsi di laurea di Scienze..");
                    armateAgg+=B_S;
                }
            }
        }
    }
    return armateAgg;
}