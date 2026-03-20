# Simulatore Stagione Formula 1

Questo progetto è un programma in C che simula una stagione di Formula 1, gestendo piloti, team e risultati delle gare.

## Descrizione

Il programma si basa sui piloti della stagione **2024/2025**, quindi le scuderie potrebbero non essere completamente aggiornate rispetto alla situazione reale attuale.

Durante la simulazione, i piloti partecipano alle gare e i loro voti vengono modificati dinamicamente in base alle prestazioni ottenute in pista.

## Funzionalità

* Simulazione completa di una stagione di Formula 1
* Aggiornamento dei voti dei piloti in base ai risultati delle gare
* Possibilità di eseguire la simulazione:

  * automaticamente (risultati alla fine diretti)
  * manualmente (gara per gara)
* Gestione dati tramite file `.txt`

## Struttura dei file

* `main.c` → logica principale del programma
* `nomiPiloti.txt` → elenco dei piloti
* `votiPiloti.txt` → voti iniziali dei piloti
* `votiTeam.txt` → voti dei team
* `GranPremi.txt` → elenco delle gare

## Come eseguire il programma

1. Compilare il codice:

```bash
gcc main.c -o simulatore
```

2. Avviare il programma:

```bash
./simulatore
```

## Note

* Assicurarsi che tutti i file `.txt` siano presenti nella stessa cartella del programma
* Il formato dei file deve essere coerente per garantire il corretto funzionamento

## Possibili miglioramenti futuri

* Interfaccia grafica
* Aggiornamento automatico dei dati dei piloti
* Statistiche avanzate (classifiche, storico gare, ecc.)

---

Progetto realizzato a scopo didattico.
