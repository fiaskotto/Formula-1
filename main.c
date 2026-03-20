#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


typedef struct {            //struct che comprende tutte le informazioni del pilota
    char nomePilota[50];
    char nomeScuderia[30];
    int votoBravura;
    int puntiClassifica;
    int numero;
    bool ritiro;
}Pilota;


typedef struct {            //struct che comprende tutte le informazioni del team dei costruttori
    char nomeScuderia[50];
    int votoAffidabilita;
    int votoEfficienza;
    int puntiClassifica;
}Costruttore;


typedef struct {        //struct che comprende tutte le informazioni del Gran Premio
    char localita[30];
    int giorno;
    int mese;
}GranPremio;



Pilota piloti[20];
Costruttore costruttori[10];
GranPremio granPremi[20];
int granPremiSvolti = 0;
int classificaPiloti[20];
int classificaCostruttori[10];
int numeriGiri[20] = {78,53,52,44,70,62,53,58,56,71,50,70,66,57,50,38,72,57,71,56};


Pilota creaPiloti(){
    Pilota p;
    strcpy(p.nomePilota, "\0");
    strcpy(p.nomeScuderia, "\0");
    p.votoBravura = 0;
    p.puntiClassifica = 0;
    p.numero = 0;
    p.ritiro = false;
    return p;
}



void riempiInformazioni(){
    int i, j = 0, h = 0, k = 0;
    char riga[200];
    char nomefile[100] = "nomiPiloti.txt";
    FILE * fp = fopen(nomefile, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", nomefile);
    }

    while(!feof(fp)) {
        fgets(riga, 200, fp);
        i = 0;
        if (riga[i+1] != '\t') {
            piloti[j].numero = (int) (riga[i++] - '0') * 10;
        }
        piloti[j].numero += riga[i++] - '0';

        for (k = i+1; riga[k] != '\t'; k++) {
            piloti[j].nomePilota[h] = riga[k];
            h++;
        }
        piloti[j].nomePilota[h] = '\0';

        h = 0;
        k++;
        for (; riga[k] != ';'; k++) {
            piloti[j].nomeScuderia[h++] = riga[k];
        }
        piloti[j].nomeScuderia[h] = '\0';
        h = 0;
        j++;
    }

    fclose(fp);
}



void creaCostruttori(){
    int j = 0;
    for(int i = 0; i < 20; i+=2){
        strcpy(costruttori[j].nomeScuderia, piloti[i].nomeScuderia);
        costruttori[j].puntiClassifica = 0;
        j++;
    }
}


GranPremio creaGranPremio(){
    GranPremio g;
    g.giorno = 0;
    strcpy(g.localita, "\0");
    g.mese = 0;
    return g;
}


void inserisciDatiGranPremi(){
    char riga[1000];
    char nomefile[100] = "GranPremi.txt";
    int i;


    FILE * fp = fopen(nomefile, "r");

    if (fp == NULL) {
        printf("non riesco ad aprire il file");
    }

    for(int j = 0; j < 20; j++){

        fgets(riga, 1000, fp);
        for(i = 0; riga[i] != '\t'; i++){
            granPremi[j].localita[i] = riga[i];
        }
        granPremi[j].localita[i] = '\0';

        i++;

        if(riga[i+1] != ' '){
            granPremi[j].giorno = (int)(riga[i] - '0') * 10;
            i++;
        }
        granPremi[j].giorno += (int)(riga[i] - '0');
        i++;

        i++;
        if(riga[i+1] != ')'){
            granPremi[j].mese = (int)(riga[i] - '0') * 10;
            i++;
        }
        granPremi[j].mese += (int)(riga[i] - '0');
    }
    fclose(fp);
}


void stampaGranPremio(GranPremio g){
    printf("+------------------------------------------+\n");
    printf("|             GRAN PREMIO N. %d             |\n", granPremiSvolti+1);
    printf("+------------------------------------------+\n");
    printf("  Localita': %s\n", g.localita);
    printf("       Data:  %d ", g.giorno);
    switch(g.mese){
        case 1:
            printf("Gennaio");
            break;
        case 2:
            printf("Febbraio");
            break;
        case 3:
            printf("Marzo");
            break;
        case 4:
            printf("Aprile");
            break;
        case 5:
            printf("Maggio");
            break;
        case 6:
            printf("Giugno");
            break;
        case 7:
            printf("Luglio");
            break;
        case 8:
            printf("Agosto");
            break;
        case 9:
            printf("Settembre");
            break;
        case 10:
            printf("Ottobre");
            break;
        case 11:
            printf("Novembre");
            break;
        case 12:
            printf("Dicembre");
            break;
        default:
            printf("errore");
            break;
    }
    printf("\n");
}


void votiPiloti() {
    char riga[10];
    char nomefile[100] = "votiPiloti.txt";
    FILE * fp = fopen(nomefile, "r");
    for(int j = 0; j < 20; j++){
        fgets(riga, 10, fp);
        riga[strlen(riga) - 1] = '\0';
        piloti[j].votoBravura = atoi(riga);
    }
    fclose(fp);
}



void votiTeam(){
    int i;
    char riga[10];
    char nomefile[100] = "votiTeam.txt";
    FILE * fp = fopen(nomefile, "r");
    for(int j = 0; j < 10; j++){
        i = 0;
        fgets(riga, 10, fp);
        if(riga[i+1] != ' '){
            costruttori[j].votoAffidabilita = ((int)riga[i] - '0') * 10;
            i++;
        }
        costruttori[j].votoAffidabilita += ((int)riga[i] - '0');
        i += 2;
        if(riga[i+1] != ';'){
            costruttori[j].votoEfficienza = ((int)riga[i] - '0') * 10;
            i++;
        }
        costruttori[j].votoEfficienza += ((int)riga[i] - '0');
    }
    fclose(fp);
}



void stampaClassificaPiloti(){

    for (int i = 0; i < 20-1; i++) {
        int indice_min = i;
        for (int j = i+1; j < 20; j++) {
            if (piloti[j].puntiClassifica > piloti[indice_min].puntiClassifica) {
                indice_min = j;
            }
        }
        Pilota tmp = piloti[indice_min];
        for (int k = indice_min; k > i; k--) {
            piloti[k] = piloti[k-1];
        }
        piloti[i] = tmp;
    }

    printf("+-----------------------------------------------+\n");
    printf("|                   CLASSIFICA                  |\n");
    printf("+-----+-------------------------------+---------+\n");

    for(int i = 0; i < 20; i++){
        printf("| %2d. |     %-21s     |   %-3d   |\n", i+1, piloti[i].nomePilota, piloti[i].puntiClassifica);
    }
    printf("+-----+-------------------------------+---------+\n");}



void stampaClassificaCostruttori(){

    for (int i = 0; i < 10-1; i++) {
        int indice_min = i;
        for (int j = i+1; j < 10; j++) {
            if (costruttori[j].puntiClassifica > costruttori[indice_min].puntiClassifica) {
                indice_min = j;
            }
        }
        Costruttore tmp = costruttori[indice_min];
        for (int k = indice_min; k > i; k--) {
            costruttori[k] = costruttori[k-1];
        }
        costruttori[i] = tmp;
    }

    printf("+---------------------------------------+\n");
    printf("|               CLASSIFICA              |\n");
    printf("+-----+----------------------+----------+\n");

    for(int i = 0; i < 10; i++){
        printf("| %2d. |     %-12s     |   %-4d   |\n", i+1, costruttori[i].nomeScuderia, costruttori[i].puntiClassifica);
    }
    printf("+-----+----------------------+----------+\n");
}



void stampaDettagliPilota(Pilota p) {
    int i = 0;
    printf("Nome e Cognome: %s\n", p.nomePilota);
    printf("Scuderia: %s\n", p.nomeScuderia);
    printf("Punti in classifica attualmente: %d\n", p.puntiClassifica);
    while (strcmp(p.nomePilota, piloti[i].nomePilota) != 0) {
        i++;
    }
    printf("Posizione attuale in classifica: %d.\n", i+1);
}



void stampaDettagliCostruttore(Costruttore p) {
    int i = 0;
    printf("Scuderia: %s\n", p.nomeScuderia);
    printf("Punti in classifica attualmente: %d\n", p.puntiClassifica);
    while (strcmp(p.nomeScuderia, costruttori[i].nomeScuderia) != 0) {
        i++;
    }
    printf("Posizione attuale in classifica: %d.\n", i+1);
}



void ordinaClassificaCostruttori() {
    for (int i = 0; i < 10-1; i++) {
        int indice_min = i;
        for (int j = i+1; j < 10; j++) {
            if (costruttori[j].puntiClassifica > costruttori[indice_min].puntiClassifica) {
                indice_min = j;
            }
        }
        int min = costruttori[indice_min].puntiClassifica;
        for (int k = indice_min; k > i; k--) {
            costruttori[k].puntiClassifica = costruttori[k-1].puntiClassifica;
        }
        costruttori[i].puntiClassifica = min;
    }
}



int simulaGuasto(Pilota p){
    int i = 0;
    while (strcmp(p.nomeScuderia, costruttori[i].nomeScuderia) != 0) {
        i++;
    }
    int random = rand() % 1000; //
    float probabilita_guasto = 2;
    float riduzione = p.votoBravura * 0.15 + costruttori[i].votoAffidabilita * 0.25;
    probabilita_guasto -= riduzione;

    if (probabilita_guasto < 0.1) {
        probabilita_guasto = 0.1;
    }

    if (random < probabilita_guasto * 5) {
        return -1;
    }
    return 0;
}



float calcolaTempoaGiro(Pilota p){
    int i = 0;
    while (strcmp(p.nomeScuderia, costruttori[i].nomeScuderia) != 0) {
        i++;
    }
    int random = rand() % 21 - 10; // casuale tra -10 e +10
    float tempo_base = 85, tempo, modificatore = p.votoBravura * 0.15 + costruttori[i].votoEfficienza * 0.1;
    tempo = tempo_base - modificatore + random;
    return tempo;
}



void assegnaPunti() {
    int punti[10] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};

    //per i piloti

    for (int i = 0; i < 10; i++) {
        piloti[i].puntiClassifica += punti[i];
    }

    //per i team costruttori

    int scuderia;
    for(int i = 0; i < 10; i++){
        scuderia = 0;
        costruttori[i].puntiClassifica = 0;
        for(int j = 0; j < 20; j++) {
            if(strcmp(piloti[j].nomeScuderia, costruttori[i].nomeScuderia) == 0) {
                costruttori[i].puntiClassifica += piloti[j].puntiClassifica;
                scuderia++;
                if(scuderia == 2) {
                    break;
                }
            }
        }
    }
}



void stampaClassificaGara(float tempi[]){
    printf("+----------------------------------------------------+\n");
    printf("|                  CLASSIFICA GARA %-2d                |\n", granPremiSvolti);
    printf("+-----+-------------------------------+--------------+\n");

    for(int i = 0; i < 20; i++){
        printf("| %2d. |     %-21s     |", i+1, piloti[i].nomePilota);
        if (tempi[i] != 9999) {
            printf("   %7.3f   |\n", tempi[i]);
        }else {
            printf("   RITIRATO   |\n");
        }
    }
    printf("+-----+-------------------------------+--------------+\n");
}



void sistemaVoti(int backup_piloti[], int backup_costruttori[], int tempi[]) {
    int i, j;
    char scuderie[10][100] = {"McLaren","Red Bull","Mercedes","Ferrari","Williams","Haas","Aston Martin","Alpine","Sauber","Racing Bulls"};
    int utilizzo_scuderia[10] = {};
    int n;

    //per il voto efficienza

    for (i = 0; i < 20; i++) {
        // trova l'indice della scuderia
        int indice_scuderia = 0;
        while (indice_scuderia < 10 && strcmp(piloti[i].nomeScuderia, scuderie[indice_scuderia]) != 0) {
            indice_scuderia++;
        }

        if (utilizzo_scuderia[indice_scuderia] == 0) {
            // trova l'altro pilota della stessa scuderia
            int altro_pilota = -1;
            for (j = 0; j < 20; j++) {
                if (j != i && strcmp(piloti[i].nomeScuderia, piloti[j].nomeScuderia) == 0) {
                    altro_pilota = j;
                    break;
                }
            }

            if (altro_pilota != -1) {
                int indice_costruttore = 0;
                while (indice_costruttore < 10 && strcmp(piloti[i].nomeScuderia, costruttori[indice_costruttore].nomeScuderia) != 0) {
                    indice_costruttore++;
                }

                if (piloti[i].puntiClassifica != backup_piloti[i] && piloti[altro_pilota].puntiClassifica != backup_piloti[altro_pilota]) {
                    costruttori[indice_costruttore].votoEfficienza++;
                    if (costruttori[indice_costruttore].votoEfficienza > 10) {
                        costruttori[indice_costruttore].votoEfficienza = 10;
                    }
                } else if (piloti[i].puntiClassifica == backup_piloti[i] && piloti[altro_pilota].puntiClassifica == backup_piloti[altro_pilota]) {
                    costruttori[indice_costruttore].votoEfficienza--;
                    if (costruttori[indice_costruttore].votoEfficienza < 1) {
                        costruttori[indice_costruttore].votoEfficienza = 1;
                    }
                }
            }
            utilizzo_scuderia[indice_scuderia] = 1;
        }
    }

    //per il voto bravura

    for (i = 0; i < 3; i++) {
        piloti[i].votoBravura++;
        if (piloti[i].votoBravura > 10) {
            piloti[i].votoBravura = 10;
        }
    }

    n = 16;

    for (i = 19; i > n; i--) {
        if (piloti[i].ritiro == true) {
            n--;
        }else {
            piloti[i].votoBravura--;
            if (piloti[i].votoBravura < 1) {
                piloti[i].votoBravura = 1;
            }
        }
    }



    //per il voto affidabilità

    for (i = 0; i < 10; i++) {
        utilizzo_scuderia[i] = 0;
    }

    for (i = 0; i < 20; i++) {
        // trova l'indice della scuderia
        int indice_scuderia = 0;
        while (indice_scuderia < 10 && strcmp(piloti[i].nomeScuderia, scuderie[indice_scuderia]) != 0) {
            indice_scuderia++;
        }

        if (utilizzo_scuderia[indice_scuderia] == 0) {
            // trova l'altro pilota della stessa scuderia
            int altro_pilota = -1;
            for (j = 0; j < 20; j++) {
                if (j != i && strcmp(piloti[i].nomeScuderia, piloti[j].nomeScuderia) == 0) {
                    altro_pilota = j;
                    break;
                }
            }

            if (altro_pilota != -1) {
                int indice_costruttore = 0;
                while (indice_costruttore < 10 && strcmp(piloti[i].nomeScuderia, costruttori[indice_costruttore].nomeScuderia) != 0) {
                    indice_costruttore++;
                }

                if (piloti[i].ritiro != true && piloti[altro_pilota].ritiro != true) {
                    costruttori[indice_costruttore].votoAffidabilita++;
                    if (costruttori[indice_costruttore].votoAffidabilita > 10) {
                        costruttori[indice_costruttore].votoAffidabilita = 10;
                    }
                } else if(piloti[i].ritiro == true && piloti[altro_pilota].ritiro == true){
                    costruttori[indice_costruttore].votoAffidabilita--;
                    if (costruttori[indice_costruttore].votoAffidabilita < 1) {
                        costruttori[indice_costruttore].votoAffidabilita = 1;
                    }
                }
            }
            utilizzo_scuderia[indice_scuderia] = 1;
        }
    }
}



void simulaGara(int scelta){
    float tempi[20] = {};
    int incidenti = 0;
    for(int i = 0; i < 20; i++) {
        for (int j = 0; j < numeriGiri[granPremiSvolti]; j++) {
            if (simulaGuasto(piloti[i]) == -1 && incidenti < 2) {
                piloti[i].ritiro = true;
                tempi[i] = 9999;
                if (incidenti == 0) {
                    piloti[i].votoBravura--;
                }
                incidenti++;
                break;
            }
            tempi[i] += calcolaTempoaGiro(piloti[i]);
        }
    }
    granPremiSvolti++;

    //sistema la classifica piloti

    for (int i = 0; i < 20-1; i++) {
        int indice_min = i;
        for (int j = i+1; j < 20; j++) {
            if (tempi[j] < tempi[indice_min]) {
                indice_min = j;
            }
        }
        float min = tempi[indice_min];
        Pilota tmp = piloti[indice_min];
        for (int k = indice_min; k > i; k--) {
            tempi[k] = tempi[k-1];
            piloti[k] = piloti[k-1];
        }
        tempi[i] = min;
        piloti[i] = tmp;
    }

    //assegna punti per la classifica

    int backupPuntiPiloti[20];
    for (int i = 0; i < 20; i++) {
        backupPuntiPiloti[i] = piloti[i].puntiClassifica;
    }

    int backupPuntiCostruttori[20];
    for (int i = 0; i < 10; i++) {
        backupPuntiCostruttori[i] = costruttori[i].puntiClassifica;
    }

    ordinaClassificaCostruttori();
    assegnaPunti();
    sistemaVoti(backupPuntiPiloti,backupPuntiCostruttori, tempi);

    if (scelta == 1) {
        char carattere;

        printf("Vuoi visualizzare i tempi della gara?\n");
        printf("Inserire Y se si, N se no:");

        scanf(" %c", &carattere);
        printf("\n");
        if (carattere == 'Y' || carattere == 'y') {
            stampaClassificaGara(tempi);
            printf("\n");
            system("pause");
        }
    }
}


void pulisciTerminale() {
    system("cls");
}


int main() {
    srand((unsigned)time(NULL));

    for(int i = 0; i < 20; i++){
        piloti[i] = creaPiloti();
    }

    for(int i = 0; i < 20; i++){
        granPremi[i] = creaGranPremio();
    }

    inserisciDatiGranPremi();
    riempiInformazioni(); //per i piloti
    creaCostruttori();
    votiPiloti();
    votiTeam();

    int dettagli, scelta;
    printf("\tPROGETTO FORMULA 1 - RICCARDO FIASCHE'\n\n");
    printf("Benvenuto nel programma, da qui potrai simulare un intero anno di campionato di Formula 1\n\n");
    printf("0.  Sono pronto a iniziare\n");
    printf("1.  Come funziona?\n");
    printf("2.  Classifiche\n");
    printf("3.  Voti");
    do {
        printf("\n\nInserisci uno dei numeri per avere piu' dettagli riguardo quella categoria:");
        do {
            scanf("%d", &dettagli);
            if (dettagli < 0 || dettagli >= 4) {
                printf("Inserisci un numero valido:\n");
            }
        }while (dettagli < 0 || dettagli > 3);

        switch (dettagli) {
            case 1:
                printf("\nCome funziona?\n20 piloti si sfideranno in 20 gare in giro per il mondo (Gran Premi) e, in base alla loro posizione in classifica della gara, guadagneranno dei punti; chi, alla fine dell'anno, ha piu' punti vince il campionato.");
                break;
            case 2:
                printf("\nClassifiche:\nCi sono 2 classifiche in questa competizione, una per i piloti e una per i team costruttori.\n\nPiloti: 20 piloti parteciperanno a un Gran Premio per vincere piu' punti possibili.\nI punti verranno assegnati in questo modo:\n");
                printf("Primo: 25 punti\nSecondo: 18 punti\nTerzo: 15 punti\nQuarto: 12 punti\nQuinto: 10 punti\nSesto: 8 punti\nSettimo: 6 punti\nOttavo: 4 punti\nNono: 2 punti\nDecimo: 1 punto\n\nI restanti non guadagneranno punti.\n\n");
                printf("Costruttori:\n\nPer determinare la classifica costruttori, alla fine di ogni gara verra' effettuata la somma dei punti dei piloti della stessa scuderia.");
                break;
            case 3:
                printf("\nVoti:\nSia i piloti che i team hanno dei voti che vanno da 1 a 10; servono per determinare diversi valori (come per esempio il tempo di un giro in una gara).\n\n");
                printf("Piloti: loro hanno solo un voto, chiamato Bravura; determina la bravura del pilota in pista durante la gara.\n\n");
                printf("Team Costruttori: loro hanno 2 voti, Efficienza e Affidabiilta'; rispettivamente, determinano la bravura del team \nnel cambiare pezzi della macchina e quanto la macchina rischia un incidente (piu' basso e', piu' il rischio e' alto)");
                break;
        }
    }while (dettagli != 0);
    pulisciTerminale();
    printf("\nInserire modalita' di simulazione:\n\n");
    printf("1. Simulazione manuale\nSimula ogni singola gara; puoi controllare nel mentre le informazioni sulle classifiche e sui gran premi\n\n");
    printf("2. Simulazione automatica\nSimula tutti e 20 i gran premi per scoprire direttamente le classifiche finali\n\n");
    do {
        scanf("%d", &scelta);
        if (scelta < 1 || scelta > 2){
            printf("Errore, inserire un numero valido:");
        }
    }while (scelta < 1 || scelta > 2);
    pulisciTerminale();
    switch (scelta) {
        case 1:
            do {
                printf("1. Simula gara\n");
                printf("2. Visualizza classifica piloti\n");
                printf("3. Visualizza classifica costruttori\n");
                printf("4. Visualizza dettagli gran premio\n");
                printf("5. Visualizza dettagli di un Pilota\n");
                printf("6. Visualizza dettagli di un team costruttori\n\n");
                printf("Cosa si vuole fare? (inserire il numero) --->");
                do {
                    scanf("%d", &dettagli);
                    if (dettagli < 1 || dettagli > 6) {
                        printf("Errore, inserire un numero valido:");
                    }
                }while (dettagli < 1 || dettagli > 6);

                printf("\n");
                switch (dettagli) {
                    case 1:
                        simulaGara(scelta);
                        pulisciTerminale();
                        printf("Gara simulata! (%d/20)\n\n", granPremiSvolti);
                        break;
                    case 2:
                        stampaClassificaPiloti();
                        system("pause");
                        pulisciTerminale();
                        break;
                    case 3:
                        stampaClassificaCostruttori();
                        system("pause");
                        pulisciTerminale();
                        break;
                    case 4:
                        stampaGranPremio(granPremi[granPremiSvolti]);
                        system("pause");
                        pulisciTerminale();
                        break;
                    case 5:
                        printf("Di quale pilota si vogliono sapere i dettagli?\n\n");
                        for (int i = 0; i < 20; i++) {
                            printf("%2d.  %s\n", i+1, piloti[i].nomePilota);
                        }
                        printf("\nInserire il numero:");
                        do {
                            scanf("%d", &dettagli);
                            if (dettagli <= 0 || dettagli > 20) {
                                printf("Errore, inserire un numero valido:");
                            }
                        }while (dettagli <= 0 || dettagli > 20);
                        printf("\n");
                        stampaDettagliPilota(piloti[dettagli-1]);
                        system("pause");
                        pulisciTerminale();
                        break;
                    case 6:
                        printf("Di quale team costruttori si vogliono sapere i dettagli?\n\n");
                        for (int i = 0; i < 10; i++) {
                            printf("%2d.  %s\n", i+1, costruttori[i].nomeScuderia);
                        }
                        printf("\nInserire il numero:");
                        do {
                            scanf("%d", &dettagli);
                            if (dettagli <= 0 || dettagli > 10) {
                                printf("Errore, inserire un numero valido:");
                            }
                        }while (dettagli <= 0 || dettagli > 10);
                        printf("\n");
                        stampaDettagliCostruttore(costruttori[dettagli-1]);
                        system("pause");
                        pulisciTerminale();
                        break;
                }
            }while (granPremiSvolti != 20);
            printf("Fine simulazione! Tutti i gran premi sono stati simulati.\n\n");
            do {
                printf("1. Visualizza classifica piloti finale\n");
                printf("2. Visualizza classifica team costruttori finale\n");
                printf("0. Termina il programma\n\n");
                printf("Cosa si vuole fare? (inserire il numero) --->");
                scanf("%d", &dettagli);
                printf("\n");
                switch (dettagli) {
                    case 1:
                        stampaClassificaPiloti();
                        printf("\n");
                        system("pause");
                        pulisciTerminale();
                        break;
                    case 2:
                        stampaClassificaCostruttori();
                        printf("\n");
                        system("pause");
                        pulisciTerminale();
                        break;
                    case 0:
                        exit(0);
                }
            }while (dettagli != 0);
            break;
        case 2:
            for (int i = 0; i < 20; i++) {
                simulaGara(scelta);
            }
            printf("Gare simulate!\n\n");
            do {
                printf("1. Visualizza classifica piloti finale\n");
                printf("2. Visualizza classifica team costruttori finale\n");
                printf("0. Termina il programma\n\n");
                printf("Cosa si vuole fare? (inserire il numero) --->");
                do {
                    scanf("%d", &dettagli);
                    if (dettagli < 0 || dettagli > 2) {
                        printf("Errore, inserire un numero valido:");
                    }
                }while (dettagli < 0 || dettagli > 2);

                printf("\n");
                switch (dettagli) {
                    case 1:
                        stampaClassificaPiloti();
                        printf("\n");
                        system("pause");
                        pulisciTerminale();
                        break;
                    case 2:
                        stampaClassificaCostruttori();
                        printf("\n");
                        system("pause");
                        pulisciTerminale();
                        break;
                }
            }while(dettagli != 0);
            break;
    }
    return 0;
}