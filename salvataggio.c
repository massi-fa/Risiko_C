//
// Created by maxim on 14/03/2019.
//

#include "salvataggio.h"
/**
 * Procedura che inizializza gli id dei giocatori appena salvati
 * @param array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param info_game struttura di tipo Gioco_info contenente il numero di giocaotori e l'id del giocatore iniziale
 */
void inizializzaId(DatiG array[],Gioco_info *info_game){
    int i;
    for(i=0;i<info_game->nGiocatori;i++){
        array[i].id=i;
    }
}
/**
 * Procedura che inizializza i il giocatore in posizione 'poszione' in array, con i dati di save
 * @param array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param save struttura di tipo DatiG usata per salvare i dti dei giocatori
 * @param posizione intero indicante la posizone del giocatore in array
 */
void inizializzaG(DatiG array[],DatiG save,int posizione){
    strcpy(array[posizione].nome,save.nome);
    array[posizione].nArmate=0;
    array[posizione].id=posizione;
    array[posizione].cArmate=save.cArmate;
    array[posizione].nCarte=0;

};
/**
 * Procedura che consente di caricare una partita da un file binario
 * @param array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param carte puntatore alla struttura di tipo Mazzo
 * @param struttura di tipo Gioco_info contenente il numero di giocaotori e l'id del giocatore iniziale
 */
void caricaPartita(DatiG array[],Territorio terre[],Mazzo *carte,Gioco_info *info_game){
    int i,c,*cartG,counter;
    DatiG save;
    Elemento *it=NULL;
    it=carte->testa;
    FILE *fp;
    fp=fopen("Salvataggio.rsk","rb");
    if(fp==NULL){   //Controlla l'apertura del file sia avvenuta correttamente
        printf("\nQualcosa non va nell\'apri file.");
    }else {
        fread(&info_game->nGiocatori, sizeof(int),1,fp);
        if(info_game->nGiocatori<MIN_GIOCATORI||info_game->nGiocatori>MAX_GIOCATORI){
            printf("\nErrore numero giocatori");
        } else{
            printf("\nNumero giocatori=%d",info_game->nGiocatori);
        }
        fread(&info_game->GIniz, sizeof(int),1,fp);
        if(info_game->GIniz==0){
            printf("\nTutto ok");
        }
        counter=info_game->nGiocatori;
        /*Leggo i dati dei giocatori contenuti nel file binario e inizializza array*/
        for(i=0;i<counter;i++){
            inizializzaId(array,info_game);
            fread(&save.nome, sizeof(char),DIM_NOME+1,fp);
            printf("\nID=%d\n%s",array[i].id,save.nome);
            fread(&save.cArmate, sizeof(int),1,fp);
            printf("\nnArmate,colore:");
            stampaColore(save.cArmate);
            fread(&save.nCarte, sizeof(int),1,fp);
            printf("\nnCarte=%d",save.nCarte);
            cartG=(int*)malloc(save.nCarte* sizeof(int));
            printf("\nElenco carte:");
            for(c=0;c<save.nCarte;c++){
                fread(&cartG[c], sizeof(int),1,fp);
                printf(" %d ",cartG[c]);
            }
            inizializzaG(array,save,i);

        }

        /*Leggo e salvo nel vettore terre i dati dei territori contenuti nel file binario*/
        printf("\nTerre:");
        //inizializzaId(array,info_game);
        for(i=0;i<N_COUNTRY;i++){
            fread(&terre[i].idTerritori, sizeof(int),1,fp);
            printf("\n");stampaFacolta(terre[i].idTerritori); printf(" ");
            fread(&terre[i].idProprietario, sizeof(int),1,fp);
            printf("%d id",terre[i].idProprietario);
            fread(&terre[i].nArmate, sizeof(int),1,fp);
            printf(" %d armate",terre[i].nArmate);
        }
        /*Leggo e inizializzo i dati delle carte presenti nel file binario*/
        fread(&carte->contatore, sizeof(int),1,fp);
        while(it != NULL){
            fread(&it->info.tipologia, sizeof(int),1,fp);
            it=it->next;
        }

    }
    fclose(fp);

}
/**
 * Procedura che consente di salvare una partita in un file binario
 * @param carte puntatore alla struttura di tipo Mazzo
 * @param array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param terre vettore di tipo Territorio contenente le informazioni dei territori di risika
 * @param struttura di tipo Gioco_info contenente il numero di giocaotori e l'id del giocatore iniziale
 */
void salvaPartita(Mazzo *carte,DatiG array[],Territorio terre[],Gioco_info *info_game){
    int i,c,terrProprietario;
    Elemento *it=NULL;
    it=carte->testa;
    FILE *save=NULL;
    save=fopen("Salvataggio.rsk","wb");
    if(save==NULL){  //Controlla che l'apertura del file sia avvenuta correttamente
        printf("\nQualcosa non va nell\'apri file,scrittura.");
    }
    fwrite(&info_game->nGiocatori, sizeof(int),1,save);
    fwrite(&info_game->GIniz, sizeof(int),1,save);
    /*Salvo i dati dei giocatori contenuti nel vettore array*/
    for(i=0;i<info_game->nGiocatori;i++){
        fwrite(array[i].nome, sizeof(char),DIM_NOME+1,save);
        fwrite(&array[i].cArmate,sizeof(cArmate),1,save);
        fwrite(&array[i].nCarte, sizeof(int),1,save);
        for(c=0;c<array[i].nCarte;c++){
        fwrite(&array[i].cartePossedute[c], sizeof(int),(size_t)array[i].nCarte,save);
        }
    }
    /*Salvo i dati dei territori contenuti nel vettore terre*/
    for(i=0;i<N_COUNTRY;i++){
        fwrite(&terre[i].idTerritori, sizeof(int),1,save);
        terrProprietario=posizioneGiocatore(array,terre[i].idProprietario,info_game->nGiocatori);
        fwrite(&terrProprietario, sizeof(int),1,save);
        fwrite(&terre[i].nArmate, sizeof(int),1,save);
    }
    /*Salvo i dati delle carte contenuti nella lista carte*/
    fwrite(&carte->contatore, sizeof(int),1,save);
    while(it!=NULL){
        fwrite(&it->info.facolta, sizeof(int),1,save);
        it=it->next;
    }
    fclose(save);
}
/**
 * Fuznione che inserito l'id di un giocatore ne restituisce la posizione in array
 * @param array vettore di tipo DatiG in cui sono presenti i dati dei giocatori
 * @param idGiocatore intero contenente l'id del giocatore in turno
 * @param nGiocatori intero contenente il numero dei giocatori in gioco
 * @return i intero contenente la posizione del giocatore in array
 */
int posizioneGiocatore(DatiG array[],int idGiocatore,int nGiocatori){
    int i;
    for(i=0;i<nGiocatori;i++){
        if(array[i].id==idGiocatore){
            return i;
        }
    }
}
