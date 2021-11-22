/*
Sviluppare una applicazione desktop in ANSI C che permetta di calcolare la classifica in un
torneo di Briscola.
Ogni partita coinvolge 2 giocatori, il punteggio di ogni partita viene sommato per
calcolare la classifica finale dei singoli giocatori.
I dati delle partite sono memorizzati in modo persistente in un file ditesto e gestiti
in memoria centrale.
Ogni partita contiene i nickname dei due giocatori ed il punteggio del primo (il secondo si ottiene
per differenza in considerazione che nel gioco della briscola il punteggio totale � 120).
Lo studente deve implementare le seguenti funzioni:
1.	carica_dati: caricamento dei dati dal file in due liste, la prima contine le partite la seconda contiene
	l'elenco dei giocatori con i relativi punteggi (media punti per partita) ordinata dal
	punteggio migliore a quello peggiore. Nota che in fase di caricamento, qualora il giocatore
	e' gi� presente, il punteggio deve esse aggiornato.
2.	carica_partita: Caricamento di una nuova partita da console e stampa della classifica aggiornata
3.	stampa_classifica: stampa la classifica (elenco giocatori ordinato)
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define DIMENSIONE_STRINGA	64
// Definizioni relative alla partita
typedef struct {
	char	giocatore_a[DIMENSIONE_STRINGA];
	char	giocatore_b[DIMENSIONE_STRINGA];
	int		punteggio_a;
} t_partita;
typedef struct s_nodo_partita {
	t_partita partita;
	struct s_nodo_partita* successivo;
}t_nodo_partita, * t_lista_partite;

// La funzione aggiunge un elemento alla lista
//	parametri in ingresso:
//		lista da modificare
//		partita da aggiungere
//	valore restituito
//		lista modificata
t_lista_partite partita_aggiungi(t_lista_partite lista, t_partita partita) {
	t_lista_partite aux = (t_lista_partite)malloc(sizeof(t_nodo_partita));
	if (aux == NULL)
		return lista;
	aux->partita = partita;
	aux->successivo = lista;
	return aux;
}

// Definizioni relative al giocatore
typedef struct {
	char	giocatore[DIMENSIONE_STRINGA];
	int		punteggio_totale;
	int		numero_partite_giocate;
} t_giocatore;
typedef struct s_nodo_giocatore {
	t_giocatore giocatore;
	struct s_nodo_giocatore* successivo;
}t_nodo_giocatore, * t_lista_giocatori;

// La funzione calcola il punteggio medio del giocatore 
//	parametri in ingresso:
//		giocatore da valutare
//	valore restituito
//		punteggio medio
double giocatore_punteggio_medio(t_giocatore giocatore) {
	// da implementare
	double result;
	return  result = (double)giocatore.punteggio_totale / giocatore.numero_partite_giocate;
}
// La funzione aggiunge un elemento alla lista
//	parametri in ingresso:
//		lista da modificare
//		giocatore da aggiungere
//	valore restituito
//		lista modificata
t_lista_giocatori giocatore_aggiungi(t_lista_giocatori lista, t_giocatore giocatore) {
	t_lista_giocatori aux = (t_lista_giocatori)malloc(sizeof(t_nodo_giocatore));
	if (aux == NULL)
		return lista;
	aux->giocatore = giocatore;
	aux->successivo = lista;
	return aux;
}
// La funzione aggiunge un elemento alla lista in modo ordinato rispeto al punteggio
// medio del giocatore
//	parametri in ingresso:
//		lista da modificare
//		giocatore da aggiungere
//	valore restituito
//		lista modificata
t_lista_giocatori giocatore_aggiungi_ordinato(t_lista_giocatori lista, t_giocatore giocatore) {
	// RICORSIONE INSERISCI ORDINATO **************************************************************
	if (lista == NULL)
		return giocatore_aggiungi(lista, giocatore);
	if (giocatore_punteggio_medio(giocatore) > giocatore_punteggio_medio(lista->giocatore))
		return giocatore_aggiungi(lista, giocatore);
	lista->successivo = giocatore_aggiungi_ordinato(lista->successivo, giocatore);
	return lista;
}

// La funzione cerca un elemento nella lista in base al nickname
// parametri in ingresso:
//		lista in cui cercare l'elemento 
//	valore restituito
//		puntatore all'elemento trovato o NULL in caso non esista
t_giocatore* giocatore_cerca(t_lista_giocatori lista, char nickname[]) {
	// da implementare
	
	while (lista != NULL) {
		if (strcmp(lista->giocatore.giocatore, nickname) == 0) {
			return &(lista->giocatore.giocatore); //puntatore al giocatore (ho giocatore, vuole gioc*, passo quindi &gioc
		}
		lista = lista->successivo;
	}
	return NULL; //non esiste
}

void giocatore_stampa(t_lista_giocatori lista) {
	while (lista != NULL) {
		printf("%s %f\n", lista->giocatore.giocatore, giocatore_punteggio_medio(lista->giocatore));
		lista = lista->successivo;
	}
}

// Funzione di caricamento dei dati. Nota che un giocatore non deve essere caricato
// pi� volte, se � presente deve essere aggiornato il punteggio ed il numero di partite
// parametri:
//		lista delle partite
//		lista dei giocatori
//		partita da caricare
//	valore restituito
//		nessuno
// Lo studente implementi la funzione e decida il meccanismo da usare per il passaggio
// dei parametri
void carica_partita(t_lista_partite* pt_partite, t_lista_giocatori* pt_giocatori,t_partita p) {
	// da implementare (ho messo gli stessi pt di carica dati e in più partita di appoggio x file
	t_giocatore g; //variabile di appoggio 
	t_giocatore* pt_g; //variabile puntatore di ritorno per la funzione cerca

	*pt_partite = partita_aggiungi(*pt_partite, p); //chiama lista, non *lista. 
	//Se chiamava *lista gli passavo pt_partite senza * in quanto sono già dichiarate con *pt_partite!
	// a sx *pt_partite perchè mi serve t_lista (tipo dato di ritorno) non t_lista*

	pt_g = giocatore_cerca(*pt_giocatori,p.giocatore_a);
	
	//giocatore A
	if (pt_g == NULL) {
		strcpy(g.giocatore,p.giocatore_a);
		g.numero_partite_giocate = 1;
		g.punteggio_totale = p.punteggio_a;
		*pt_giocatori = giocatore_aggiungi_ordinato(*pt_giocatori, g); 
		//come partita aggiungi, la funzione mi torna t_lista (quindi *(t_lista*)=lista)
		// e idem nella call passo *pt perchè mi chiede lista, quindi *(lista*)=lista
	}
	else {
		(pt_g->numero_partite_giocate)++; //senza * perchè già lo è definito così
		pt_g->punteggio_totale = pt_g->punteggio_totale + p.punteggio_a;
	}
	//giocatore B
	if (pt_g == NULL) {
		strcpy(g.giocatore, p.giocatore_b);
		g.numero_partite_giocate = 1;
		g.punteggio_totale = 120-p.punteggio_a;
		*pt_giocatori = giocatore_aggiungi(*pt_giocatori, g);
		//come partita aggiungi, la funzione mi torna t_lista (quindi *(t_lista*)=lista)
		// e idem nella call passo *pt perchè mi chiede lista, quindi *(lista*)=lista
	}
	else {
		(pt_g->numero_partite_giocate)++; //senza * perchè già lo è definito così
		pt_g->punteggio_totale = pt_g->punteggio_totale + (120-p.punteggio_a);
	}
}

// Funzione di caricamento dei dati dal file. NOta che un giocatore non deve essere caricato
// pi� volte ma solo aggiornato il punteggio ed il numero di partite
// NOTA: � possiile usare la funzione carica_partita
// parametri:
//		nome del file da cui caricare i dati
//		lista delle partite
//		lista dei giocatori
//	valore restituito
//		nessuno
void carica_dati(const char* nome_file, t_lista_partite* pt_partite, t_lista_giocatori* pt_giocatori) {
	// da implementare
	FILE* f;
	t_partita p;
	int i = 0;

	f = fopen(nome_file, "r");
	if (f == NULL)
		printf("Errore file");
	while (fscanf(f, "%s%s%d", p.giocatore_a, p.giocatore_b, &p.punteggio_a) == 3) {
		carica_partita(pt_partite,pt_giocatori,p);
		i++;
	}
	printf("Sono state caricate %d partite. \n",i);
}

void stampa_partite(t_lista_partite partite) {
	while (partite != NULL) {
		printf("%s %d %s %d\n",
			partite->partita.giocatore_a, partite->partita.punteggio_a, partite->partita.giocatore_b, 120 - partite->partita.punteggio_a);
		partite = partite->successivo;
	}
}

int main(void) {
	int selezione;
	t_lista_partite elenco_partite = NULL;
	t_lista_giocatori elenco_giocatori = NULL;
	t_partita partita;
	char buffer[DIMENSIONE_STRINGA];

	do {
		printf("\n1. carica dati da file\n");
		printf("2. carica dati da console\n");
		printf("3. stampa la classifica\n");
		printf("4. stampa le partite disputate\n");
		printf("0. fine\n");
		printf(">>> ");
		scanf("%d", &selezione);
		switch (selezione) {
		case 0:
			printf("fine programma\n");
			break;
		case 1:
			// Lo studente implementi quanto necessario a svolgere le seguenti operazioni
			// 1. richiesta del nome del file da cui caricare i dati
			printf("File : ");
			scanf("%s", buffer);
			// 2. chiamata della funzione carica_dati
			carica_dati(buffer, &elenco_partite, &elenco_giocatori);

			break;
		case 2:
			// Lo studente implementi quanto necessario a caricare una partita da console
			// 1. richiesta dei dati 
			printf("Inserire nome giocatore A : ");
			scanf("%s", partita.giocatore_a);
			printf("Inserire nome giocatore B : ");
			scanf("%s", partita.giocatore_b);
			printf("Inserire punteggio A : ");
			scanf("%d", &partita.punteggio_a);
			// 2. chiamata della funzione carica_partita
			carica_partita(&elenco_partite, &elenco_giocatori, partita);
			break;
		case 3:
			// Lo studente implementi quanto necessario a stampare l'attuale classifica
			// usando le funzioni date
			giocatore_stampa(elenco_giocatori);
			break;
		case 4:
			stampa_partite(elenco_partite);
		}
	} while (selezione != 0);
}
